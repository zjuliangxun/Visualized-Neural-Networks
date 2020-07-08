#pragma once
#ifndef WEIGHTS_H
#define WEIGHTS_H

#include <QSharedPointer>
#include "neurons.h"

class Weight {
public:
	QSharedPointer<Neuron> _from, _to;
	double _weight;
};

#endif // !WEIGHTS_H
