#include "NetModel.h"
#include <stack>

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
