#pragma once
#ifndef WEIGHTS_H
#define WEIGHTS_H

#include "neurons.h"

class Weight {
public:
    int id;
	int _from, _to;	// edge (from, to), IDs of vertices (Neurons)
	double _weight, _gradient;	// weight and gradient with respect of
};

#endif // !WEIGHTS_H
