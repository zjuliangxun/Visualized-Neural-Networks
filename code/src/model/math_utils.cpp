#include <cmath>
#include "math_utils.h"

double sigmod(double v){
    return 1.0/(1+exp(-v));
}
double dsigmod(double v){
//    v=sigmod(v);
    return v*(1-v);
}

double tanh(double x){
        return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}
double dtanh(double outx){
//        double tanh = (exp(outx) - exp(-outx)) / (exp(outx) + exp(-outx));
        return 1 - pow(outx, 2);
}

double relu(double x){
    return x>=0?x:0;
}
double drelu(double x){
    return x<=0?0:1;
}
double dloss(double predict, double target, LossFunc lossfunc)
{
    double d = 0;
    switch (lossfunc) {
    case lossL1:
        d = (predict > target ? 1 : -1);
        break;
    case lossL2:
        d = 2 * (predict - target);
        break;
    }
    return d;
}
