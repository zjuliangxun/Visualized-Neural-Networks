#pragma once

#ifndef GRAPH_H
#define GRAPH_H

#include <QVector>
#include "neurons.h"
#include "weights.h"


class Graph {
private:
    int _neuron_id;
    int _weight_id;

public:
	QVector<Neuron> _neurons;
	QVector<Weight> _weights;
    bool add_neuron(Neuron&&);
    bool add_link(Weight && wigh);
    // return whether there exists loop
    Neuron& atNeuronID(int);
    Weight& atWeightID(int);
};

#endif // !GRAPH_H

