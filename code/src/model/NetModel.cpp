#include <stack>
#include <queue>
#include "NetModel.h"
#include "math_utils.h"

NetModel::NetModel(){
    this->FNN=make_shared<Graph>();
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
    if(this->FNN->_neurons[id-1].isleaf==nHidden) return false;
    else this->FNN->_neurons[id-1]._value=value;
    return true;
}

bool NetModel::change_weight(int id, double value){
    this->FNN->_weights[id-1]._weight=value;
    return true;
}



bool NetModel::calculate_forward() {
//    for(auto i:FNN->_neurons){i.indeg=i._value=0;}
//    std::queue<Neuron*> mq;
//    for(auto i:this->FNN->_neurons){
//        for(auto e:i.adjedge){
//            FNN->_neurons[neumap[_weights[e]._to]].indeg++;
//        }
//    }
//    for(auto i:FNN->_neurons){
//        if(i.indeg==0)mq.push(&i);
//    }
//    while(!mq.empty()){
//        Neuron* t=mq.front();
//        mq.pop();
//        if(t->indeg==0)return false;
//        if(t->isleaf!=nInput){
//            t->_value+=t->_b;
//            if(t->type==nSigmoid )t->_value=sigmod(t->_value);
//            else if(t->type== nRelu )t->_value=relu(t->_value);
//            else if(t->type== nTanh)t->_value=tanh(t->_value);
//        }
//        for(auto e:t->adjedge){
//            FNN->_neurons[neumap[_weights[e]._to]]._value+=(_weights[e]._weight)*t->_value;
//            if(!(--FNN->_neurons[neumap[_weights[e]._to]].indeg))mq.push(&_neurons[neumap[_weights[e]._to]]);
//        }
//    }
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

