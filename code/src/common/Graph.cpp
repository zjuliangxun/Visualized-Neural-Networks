#include "Graph.h"
#include<queue>
#include<cmath>
bool Graph::add_neuron(Neuron &&nuro)
{
    nuro.isleaf=nInput;
    nuro.id = ++_neuron_id;
    nuro.indeg=0;
    this->_neurons.append(std::move(nuro));
    return true;
}
Neuron& Graph::atNeuronID(int idx)
{
    for (int i = 0; i != _neurons.size(); ++i) {
        if (_neurons.at(i).id == idx)
            return _neurons[i];
    }
    throw "Neuron ID not found!";
}
Weight& Graph::atWeightID(int idx)
{
    for (int i = 0; i != _weights.size(); ++i) {
        if (_weights.at(i).id == idx)
            return _weights[i];
    }
    throw "Weight ID not found!";
}

bool Graph::add_link(Weight && wigh){
    if (this->atNeuronID(wigh._from).type == nTarget)
        return false;
    wigh.id=++this->_weight_id;
    this->atNeuronID(wigh._to).indeg++;
    if(this->atNeuronID(wigh._to).type==nTarget)
        this->atNeuronID(wigh._from).isleaf=nOutput;
    else if(this->atNeuronID(wigh._to).isleaf==nInput)
        this->atNeuronID(wigh._to).isleaf=nHidden;
    this->atNeuronID(wigh._to).rev_adjedge.push_back(wigh.id);
    this->atNeuronID(wigh._from).adjedge.push_back(wigh.id);
    this->_weights.append(std::move(wigh));
    return true;
}
