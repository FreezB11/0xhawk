#ifndef _CALC
#define _CALC

#define eps 1.61012e-4

float df(float (*func)(float),float x);
double sigmoid(double x);
double sigmoid_derivative(double x);
double relu(double x);
int Binary(double x);
double mtanh(double x);

#endif