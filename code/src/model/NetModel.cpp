#include <stack>
#include <queue>
#include <map>
#include "NetModel.h"
#include "math_utils.h"

NetModel::NetModel(){
    this->FNN=make_shared<Graph>();
    this->loss_func = lossL2;
    this->learning_rate = 0.1;
}

std::function<bool(Neuron&&)> NetModel::get_add_neuron_command() {
    return [this](Neuron&& x)->bool {
        return this->add_neuron(std::move(x));
    };
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
    return this->FNN->add_neuron(std::move(x));
}

std::function<bool(int,int)>  NetModel::get_connect_command(){
    return [this](int a,int b)->bool{
        return add_link(a,b);
    };
}

bool NetModel::add_link(int src,int dst){
    if(estimate_circle(src,dst)) return false;
    else{
        Weight w;
        w._from=src;
        w._to=dst;
        return this->FNN->add_link(std::move(w));
    }
}

bool NetModel::estimate_circle(int src, int dst){
    std::stack<int> node;
    node.push(dst);
    Neuron nuro;
    while(!node.empty()){
        int no=node.top()-1;
        if(node.top()==src) return true;
        nuro=this->FNN->_neurons[no];
        int i;
        node.pop();
        auto itor=nuro.adjedge.begin();
        for(i=0;i<nuro.adjedge.size();i++){
            if(this->FNN->_weights[*itor-1]._to==dst&&this->FNN->_weights[*itor-1]._from==src) return true;
            node.push(this->FNN->_weights[*itor-1]._to);
            itor++;
        }
    }
    return false;
}

bool NetModel::change_neruo(int id, double value){
    if(this->FNN->atNeuronID(id).isleaf==nHidden) return false;
    else if (this->FNN->atNeuronID(id).type==nTarget)
        this->FNN->atNeuronID(id)._targetvalue=value;
    else this->FNN->atNeuronID(id)._value=value;
    return true;
}

bool NetModel::change_weight(int id, double value){
    this->FNN->atWeightID(id)._weight=value;
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
    return true;
//    //应该在model中写出来
//    std::vector<double> tag;//默认按照添加output的顺序去赋值
//    double pace=0.05;//learn rate
//    //另外，图和neuron和weight最好都加个构造函数
//    //
//    for(auto i:_neurons){i.indeg=i.grad=0;}
//    std::queue<Neuron*> mq;

//    for(auto i:this->_neurons){
//        for(auto e:i.rev_adjedge){
//            _neurons[neumap[_weights[e]._to]].indeg++;
//        }
//    }
//    for(auto i:_neurons){
//        if(i.indeg==0){
//            static int j=0;
//            mq.push(&i);
//            if(i.type==nSigmoid )i.grad=(tag[j++]-i._value)*dsigmod(i._value);//后半截是导数
//            else if(i.type== nRelu )i.grad=(tag[j++]-i._value)*drelu(i._value);//后半截是导数
//            else if(i.type== nTanh)i.grad=(tag[j++]-i._value)*dtanh(i._value);//后半截是导数
//        }
//    }
//    while(!mq.empty()){
//        Neuron* t=mq.front();
//        mq.pop();
//        if(t->indeg==0)return false;
//        if(t->isleaf!=nOutput){
//            t->grad*=dsigmod(t->_value);
//        }
//        for(auto e:t->rev_adjedge){
//            _neurons[neumap[_weights[e]._from]].grad+=(_weights[e]._weight)*t->grad;
//            if(!(--_neurons[neumap[_weights[e]._from]].indeg))mq.push(&_neurons[neumap[_weights[e]._from]]);
//        }
//    }
//    for(auto w:_weights){
//        w._weight+=pace*(_neurons[neumap[w._to]].grad)*(_neurons[neumap[w._from]]._value);
//    }
}

bool NetModel::delete_weight(int id){
    //this->FNN->_weights.clear();
    Weight w = this->FNN->atWeightID(id);
    Neuron src = this->FNN->atNeuronID(w._from);
    Neuron dst = this->FNN->atNeuronID(w._to);
    auto itor=this->FNN->_weights.begin();
    int i,j;
    for(i=0;i<this->FNN->_weights.size();i++){
        if(itor->id==w.id){
          auto its=src.adjedge.begin();
          for(j=0;j<src.adjedge.size();j++){
              if(*its==id) src.adjedge.erase(its);
              its++;
          }
          auto itd=dst.rev_adjedge.begin();
          for(j=0;j<dst.rev_adjedge.size();j++){
              if(*itd==id) dst.rev_adjedge.erase(itd);
              itd++;
          }
          this->FNN->_weights.erase(itor);
          return true;
        }
    }
    return true;
}


