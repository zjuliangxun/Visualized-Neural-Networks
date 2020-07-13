#include <stack>
#include <cmath>
#include "NetModel.h"
#include "math_utils.h"

NetModel::NetModel(){
    this->FNN=make_shared<Graph>();
    this->loss_func = lossL2;
    this->learning_rate = 0.1;
}

std::shared_ptr<Graph> NetModel::get_FNN()
{
    return std::shared_ptr<Graph>(this->FNN);
}

void NetModel::set_update_display_data_notification(Notification&& notification)
{
    AddNotification(std::move(notification));
}


bool NetModel::add_neuron(Neuron&& x)
{
    bool success = this->FNN->add_neuron(std::move(x));
    if (success) {
        this->Fire(NOTIF_CHANGE);
    }
    return success;
}

bool NetModel::add_link(int src,int dst){
    if(estimate_circle(src,dst)) return false;
    else{
        Weight w;
        w._from=src;
        w._to=dst;
        bool success = this->FNN->add_link(std::move(w));
        if (success) {
            this->Fire(NOTIF_CHANGE);
        }
        return success;
    }
}

bool NetModel::estimate_circle(int src, int dst){
    std::stack<int> node;
    node.push(dst);
    Neuron nuro;
    while(!node.empty()){
        int no=node.top();
        if(node.top()==src) return true;
        nuro=this->FNN->atNeuronID(no);
        node.pop();
        for (auto itor=nuro.adjedge.begin();
             itor != nuro.adjedge.end(); ++itor){
            if(this->FNN->atWeightID(*itor)._to==dst
                    && this->FNN->atWeightID(*itor)._from==src) return true;
            node.push(this->FNN->atWeightID(*itor)._to);
        }
    }
    return false;
}

bool NetModel::change_neruo(int id, double value){
    if(this->FNN->atNeuronID(id).isleaf==nHidden) return false;
    else if (this->FNN->atNeuronID(id).type==nTarget)
        this->FNN->atNeuronID(id)._targetvalue=value;
    else this->FNN->atNeuronID(id)._value=value;
    this->Fire(NOTIF_DRAW);
    return true;
}
bool NetModel::change_neruo_type(int id, NeuronType tp) {
    if (tp != nTarget && this->FNN->atNeuronID(id).type != nTarget) {
        this->FNN->atNeuronID(id).type = tp;
        return true;
    }
    return false;
}

bool NetModel::change_weight(int id, double value){
    this->FNN->atWeightID(id)._weight=value;
    this->Fire(NOTIF_DRAW);
    return true;
}

bool NetModel::calculate_forward() {
    QVector<int> calculated_in(FNN->_neurons.size());
    QVector<bool> calculated(FNN->_neurons.size());
    for (int i = 0; i != FNN->_neurons.size(); ++i) {
        if (FNN->_neurons[i].isleaf != nInput)
            FNN->_neurons[i]._value = FNN->_neurons[i]._b;
        calculated[i] = false;
        calculated_in[i] = 0;
    }
    int cnt = 0;
    while (cnt != FNN->_neurons.size()) {
        for (int i = 0; i != FNN->_neurons.size(); ++i) {
            if (calculated_in[i] == FNN->_neurons.at(i).indeg
                    && !calculated[i]) {
                double value = FNN->_neurons.at(i)._value;
                switch (FNN->_neurons.at(i).type) {
                case nSigmoid:
                    value = sigmod(value);
                    break;
                case nRelu:
                    value = relu(value);
                    break;
                case nTanh:
                    value = tanh(value);
                    break;
                default:
                    break;
                }
                FNN->_neurons[i]._value = value;
                calculated[i] = true;
                ++cnt;
                for (auto e: FNN->_neurons[i].adjedge) {
                    int toID = FNN->atWeightID(e)._to;
                    for (int j = 0; j != FNN->_neurons.size(); ++j) {
                        if (FNN->_neurons[j].id == toID) {
                            calculated_in[j]++;
                            break;
                        }
                    }
                    FNN->atNeuronID(toID)._value +=
                            FNN->atWeightID(e)._weight * value;
                }
            }
        }
    }
    this->Fire(NOTIF_DRAW);
    return true;
}

bool NetModel::calculate_gradient()
{
    for (int i = 0; i != FNN->_neurons.size(); ++i) {
        NeuronType t = FNN->_neurons.at(i).type;
        double gradient = 1.0;
        switch (t) {
        case nSigmoid:
            gradient = dsigmod(FNN->_neurons.at(i)._value);
            break;
        case nRelu:
            gradient = drelu(FNN->_neurons.at(i)._value);
            break;
        case nTanh:
            gradient = dtanh(FNN->_neurons.at(i)._value);
            break;
        case nTarget:
            gradient = dloss(FNN->_neurons.at(i)._value,
                             FNN->_neurons.at(i)._targetvalue,
                             loss_func);
            break;
        default:
            break;
        }
        FNN->_neurons[i]._grad = gradient;
    }
    for (int i = 0; i != FNN->_weights.size(); ++i) {
        int fromID = FNN->_weights.at(i)._from;
        double gradient = 1.0;
        gradient = FNN->atNeuronID(fromID)._value;
        FNN->_weights[i]._gradient = gradient;
    }
    this->Fire(NOTIF_DRAW);
    return true;
}

bool NetModel::propagate_gradient()
{
    QVector<double> accumulate_grad(FNN->_neurons.size());
    QVector<int> calculated_out(FNN->_neurons.size());
    QVector<bool> calculated(FNN->_neurons.size());
    int cnt = 0;
    for (int i = 0; i != FNN->_neurons.size(); ++i) {
        if (FNN->_neurons[i].isleaf == nInput)
            ++cnt;
        calculated[i] = false;
        calculated_out[i] = 0;
        accumulate_grad[i] = 0;
    }
    while (cnt != FNN->_neurons.size()) {
        for (int i = 0; i != FNN->_neurons.size(); ++i) {
            if (FNN->_neurons.at(i).isleaf == nInput)
                continue;
            if (calculated_out[i] == FNN->_neurons.at(i).outdeg
                    && !calculated[i]) {
                if (FNN->_neurons.at(i).isleaf != nOutput)
                    FNN->_neurons[i]._grad *= accumulate_grad[i];
                calculated[i] = true;
                ++cnt;
                for (auto e: FNN->_neurons[i].rev_adjedge) {
                    int fromID = FNN->atWeightID(e)._from;
                    for (int j = 0; j != FNN->_neurons.size(); ++j) {
                        if (FNN->_neurons[j].id == fromID) {
                            FNN->atWeightID(e)._gradient
                                    *= FNN->_neurons[i]._grad;
                            calculated_out[j]++;
                            accumulate_grad[j]
                                    += (FNN->_neurons[i]._grad
                                    * FNN->atWeightID(e)._weight);
                            break;
                        }
                    }
                }
            }
        }
    }
    this->Fire(NOTIF_DRAW);
    return true;
}

bool NetModel::update_weights()
{
    for (int i = 0; i != FNN->_weights.size(); ++i) {
        FNN->_weights[i]._weight -=
                learning_rate * FNN->_weights.at(i)._gradient;
        FNN->_weights[i]._gradient = 0;
    }
    for (int i = 0; i != FNN->_neurons.size(); ++i) {
        FNN->_neurons[i]._grad = 0;
        // FNN->_neurons[i]._b
        // neuron update: if b is used, then need to update it
    }
    this->Fire(NOTIF_DRAW);
    return true;
}

bool NetModel::backprop(int *step){
    if (!calculate_gradient()) {
        *step = 1;
        return false;
    }
    if (!propagate_gradient()) {
        *step = 2;
        return false;
    }
    if (!update_weights()) {
        *step = 3;
        return false;
    }
    *step = 0;
    this->Fire(NOTIF_DRAW);
    return true;
}

bool NetModel::delete_weight(int id){
    Weight w = this->FNN->atWeightID(id);
    Neuron &src = this->FNN->atNeuronID(w._from);
    Neuron &dst = this->FNN->atNeuronID(w._to);
    auto itor = this->FNN->_weights.begin();
    while (itor != this->FNN->_weights.end()){
        if(itor->id==id){
          for(auto its=src.adjedge.begin();
              its != src.adjedge.end();++its){
              if(*its==id) {
                  src.adjedge.erase(its);
                  src.outdeg--;
                  break;
              }
          }
          for(auto its=dst.rev_adjedge.begin();
              its != dst.rev_adjedge.end();++its){
              if(*its==id) {
                  dst.rev_adjedge.erase(its);
                  dst.indeg--;
                  break;
              }
          }
          if (dst.rev_adjedge.empty())
              dst.isleaf = nInput;
          itor = this->FNN->_weights.erase(itor);
          this->Fire(NOTIF_CHANGE);

          return true;
        }
        else
            ++itor;
    }
    return false;
}

bool NetModel::delete_neuron(int id){
    Neuron &nro=this->FNN->atNeuronID(id);
    while (!nro.adjedge.empty()) {
        delete_weight(*(nro.adjedge.begin()));
    }
    while (!nro.rev_adjedge.empty()) {
        delete_weight(*(nro.rev_adjedge.begin()));
    }
    for (auto it = this->FNN->_neurons.begin();
         it != this->FNN->_neurons.end(); ++it){
        if(it->id==id) {
            this->FNN->_neurons.erase(it);
            break;
        }
    }
    this->Fire(NOTIF_CHANGE);
    return true;
}

bool NetModel::change_learning_rate(double x)
{
    this->learning_rate = x;
    return true;
}
bool NetModel::change_loss(LossFunc func)
{
    this->loss_func = func;
    return true;
}
double NetModel::get_learning_rate(){
    return this->learning_rate;
}

QString NetModel::get_loss_func(){
    if(this->loss_func==lossL1) return "L1";
    else return "L2";
}

