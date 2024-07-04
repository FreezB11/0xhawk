#ifndef _NN 
#define _NN 

// includes....
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "utils/color.h"

#define nn float
#define nn_initialize float
#define LENS(arr) ((int) (sizeof (arr) / sizeof (arr)[0])) // no of sample sets

double sigmoid(double x);
nn rand_float(void);
double sigmoid(double x);

void LinearREG(int NOS,int NOI,float inputs[NOS][NOI],float output[],float weights[],float *bias);

#endif