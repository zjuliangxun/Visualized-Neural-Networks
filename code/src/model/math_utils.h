#pragma once

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

enum LossFunc {     // error (loss function type)
    lossL1, lossL2  // L1-norm, L2-norm
};

double sigmod(double v);
double dsigmod(double v);
//double tanh(double v);
double dtanh(double outx);
double relu(double x);
double drelu(double x);
double dloss(double predict, double target, LossFunc lossfunc=lossL2);

#endif // MATH_UTILS_H
