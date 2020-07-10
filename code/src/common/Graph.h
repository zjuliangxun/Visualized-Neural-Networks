#pragma once

#ifndef GRAPH_H
#define GRAPH_H

#include <QVector>
#include "neurons.h"
#include "weights.h"
#include<map>


class Graph {
private:
    int _neuron_id;
    int _weight_id;
public:
	QVector<Neuron> _neurons;
	QVector<Weight> _weights;
    std::map<int ,int> neumap;
    bool add_neuron(Neuron&&);
    bool add_link(Weight && wigh);
private:
    // return whether there exists loop
    bool topo_sort();
    bool backprop();
    double sigmod(double v);
    double dsigmod(double v);
    double tanh(double x);
    double dtanh(double outx);
    double relu(double x);
    double drelu(double x);
};

#endif // !GRAPH_H

