#include <stack>
#include <queue>
#include <map>
#include "NetModel.h"
#include "math_utils.h"

NetModel::NetModel(){
    this->FNN=make_shared<Graph>();
    this->loss_func = lossL2;
    this->learning_rate = 0.01;
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
    for (int i = 0; i != FNN->_weights.size(); ++i) {
        int toID = FNN->_weights.at(i)._to;
        int fromID = FNN->_weights.at(i)._from;
        NeuronType t = FNN->atNeuronID(toID).type;
        double gradient = 1.0;
        switch (t) {
        case nSigmoid:
            gradient = dsigmod(FNN->atNeuronID(toID)._value);
            break;
        case nRelu:
            gradient = drelu(FNN->atNeuronID(toID)._value);
            break;
        case nTanh:
            gradient = dtanh(FNN->atNeuronID(toID)._value);
            break;
        case nTarget:
            gradient = dloss(FNN->atNeuronID(toID)._value,
                             FNN->atNeuronID(toID)._targetvalue,
                             loss_func);
            break;
        default:
            break;
        }
        gradient *= FNN->atNeuronID(fromID)._value;
        FNN->_weights[i]._gradient = gradient;
    }
    return true;
}

bool NetModel::backprop(){
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
    return true;
}

