#include "Graph.h"

bool Graph::add_neuron(Neuron &&nuro)
{
    nuro.id = this->_neurons.size();
    this->_neurons.append(std::move(nuro));
    return true;
}
