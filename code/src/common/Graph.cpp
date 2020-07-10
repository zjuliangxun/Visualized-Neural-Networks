#include "Graph.h"
#include<queue>
#include<cmath>
bool Graph::add_neuron(Neuron &&nuro)
{
    nuro.id = ++_neuron_id;
    this->_neurons.append(std::move(nuro));
    return true;
}

bool Graph::add_link(Weight && wigh){
    this->_weight_id++;
    this->_weights.append(std::move(wigh));
    return true;
}

double Graph::sigmod(double v){
    return 1.0/(1+exp(-v));
}
double Graph::dsigmod(double v){
    v=sigmod(v);
    return v*(1-v);
}


double Graph::tanh(double x){
        return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}
double Graph::dtanh(double outx){
        double tanh = (exp(outx) - exp(-outx)) / (exp(outx) + exp(-outx));
        return 1 - pow(tanh, 2);
}

double Graph::relu(double x){
    return x>=0?x:0;
}
double Graph::drelu(double x){
    return x<=0?0:1;
}

bool Graph::topo_sort(){
    for(auto i:_neurons){i.indeg=i._value=0;}
    std::queue<Neuron*> mq;
    for(auto i:this->_neurons){
        for(auto e:i.adjedge){
            _neurons[neumap[_weights[e]._to]].indeg++;
        }
    }
    for(auto i:_neurons){
        if(i.indeg==0)mq.push(&i);
    }
    while(!mq.empty()){
        Neuron* t=mq.front();
        mq.pop();
        if(t->indeg==0)return false;
        if(t->isleaf!=nInput){
            t->_value+=t->_b;
            if(t->type==nSigmoid )t->_value=sigmod(t->_value);
            else if(t->type== nRelu )t->_value=relu(t->_value);
            else if(t->type== nTanh)t->_value=tanh(t->_value);
        }
        for(auto e:t->adjedge){
            _neurons[neumap[_weights[e]._to]]._value+=(_weights[e]._weight)*t->_value;
            if(!(--_neurons[neumap[_weights[e]._to]].indeg))mq.push(&_neurons[neumap[_weights[e]._to]]);
        }
    }
    return true;
}


bool Graph::backprop(){
    //应该在model中写出来
    std::vector<double> tag;//默认按照添加output的顺序去赋值
    double pace=0.05;//learn rate
    //另外，图和neuron和weight最好都加个构造函数
    //
    for(auto i:_neurons){i.indeg=i.grad=0;}
    std::queue<Neuron*> mq;

    for(auto i:this->_neurons){
        for(auto e:i.rev_adjedge){
            _neurons[neumap[_weights[e]._to]].indeg++;
        }
    }
    for(auto i:_neurons){
        if(i.indeg==0){
            static int j=0;
            mq.push(&i);
            if(i.type==nSigmoid )i.grad=(tag[j++]-i._value)*dsigmod(i._value);//后半截是导数
            else if(i.type== nRelu )i.grad=(tag[j++]-i._value)*drelu(i._value);//后半截是导数
            else if(i.type== nTanh)i.grad=(tag[j++]-i._value)*dtanh(i._value);//后半截是导数
        }
    }
    while(!mq.empty()){
        Neuron* t=mq.front();
        mq.pop();
        if(t->indeg==0)return false;
        if(t->isleaf!=nOutput){
            t->grad*=dsigmod(t->_value);
        }
        for(auto e:t->rev_adjedge){
            _neurons[neumap[_weights[e]._from]].grad+=(_weights[e]._weight)*t->grad;
            if(!(--_neurons[neumap[_weights[e]._from]].indeg))mq.push(&_neurons[neumap[_weights[e]._from]]);
        }
    }
    for(auto w:_weights){
        w._weight+=pace*(_neurons[neumap[w._to]].grad)*(_neurons[neumap[w._from]]._value);
    }
    return true;
}
