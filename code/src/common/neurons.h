#pragma once

#ifndef NEURONS_H
#define NEURONS_H

enum NeuronType {
	nNone, nSigmoid, nRelu, nTanh, nTarget
};

class Neuron {
public:
	double _value;
	NeuronType type;		// {none, sigmoid, relu, tanh, target}
	int isleaf;		// {input, output, hidden}
    int id;         // id in Graph: QVector<Neuron>

	//QRect _shape;
	//static int _radius;
	//bool conflict(const Neuron&);
};

#endif // !NEURONS_H
