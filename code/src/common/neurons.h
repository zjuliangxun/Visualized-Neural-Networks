#pragma once

#ifndef NEURONS_H
#define NEURONS_H
#include <list>
enum NeuronType {
	nNone, nSigmoid, nRelu, nTanh, nTarget
};

enum NodeType {
    nInput, nOutput, nHidden
};

class Neuron {
public:

	NeuronType type;		// {none, sigmoid, relu, tanh, target}
    NodeType isleaf;		// {input, output, hidden}
    int id;         // id in Graph: QVector<Neuron>

	std::list<int> adjedge;
    std::list<int> rev_adjedge;
    int indeg;
    int outdeg;
    double _b;
    double _value;
    double _targetvalue;
    double _grad;
};

#endif // !NEURONS_H
