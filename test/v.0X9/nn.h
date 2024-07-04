#ifndef _NN_H_
#define _NN_H_

#include <stdlib.h>
#include "matrix.h"

#define LENS(arr) ((int) (sizeof (arr) / sizeof (arr)[0])) // no of sample sets


// non => no of neuron
//noi => no of input
//nos => no of samples
//nol => no of layers

typedef struct{
    int noi;
    float *input;
    float bias;
    float output;
}neuron;

typedef struct nlayer{
    int non;
    neuron **neurons;
    struct nlayer *prev_layer;
}nlayer;



typedef struct{
    int NOS;
    //Matrix ntwrk;
    Matrix input;
    int *ntwrk_struct;
    nlayer **layers;
}Nnetwrk;

neuron *createNeuron(int noi,float inputs[]);
nlayer *createLayer(int non,int non_prevLayer);
Nnetwrk *createNetwork(int nol,int noi,int nstruct[]);

Nnetwrk forward(Nnetwrk neural);


 
#endif