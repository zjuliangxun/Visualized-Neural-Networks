#include "Graph.h"


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
