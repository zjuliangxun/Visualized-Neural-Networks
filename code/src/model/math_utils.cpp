#include <cmath>
#include "math_utils.h"

double sigmod(double v){
    return 1.0/(1+exp(-v));
}
double dsigmod(double v){
    v=sigmod(v);
    return v*(1-v);
}

double tanh(double x){
        return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}
double dtanh(double outx){
        double tanh = (exp(outx) - exp(-outx)) / (exp(outx) + exp(-outx));
        return 1 - pow(tanh, 2);
}

double relu(double x){
    return x>=0?x:0;
}
double drelu(double x){
    return x<=0?0:1;
}
