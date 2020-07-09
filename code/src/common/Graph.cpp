#include "Graph.h"

bool Graph::add_neuron(Neuron &&nuro)
{
    nuro.id = ++_neuron_id;
    this->_neurons.append(std::move(nuro));
    return true;
}
