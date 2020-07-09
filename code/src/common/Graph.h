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
};

#endif // !GRAPH_H

