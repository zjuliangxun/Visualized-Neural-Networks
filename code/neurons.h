#pragma once

#ifndef NEURONS_H
#define NEURONS_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>

enum NeuronType {
	nNone, nSigmoid, nRelu, nTanh, nTarget
};

class Neuron {
public:
	QRect _shape;
	double _value;
	NeuronType type;		// {none, sigmoid, relu, tanh, target}
	int isleaf;		// {input, output, hidden}
	static int _radius;

	bool conflict(const Neuron&);
};

#endif // !NEURONS_H
