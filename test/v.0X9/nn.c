#include "nn.h"
#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>



neuron *createNeuron(int noi,float inputs[]){

    neuron *n = (neuron*)malloc(sizeof(neuron));
    n->input = (float*)malloc(noi*sizeof(float));
    n->noi = noi;
    for (size_t i = 0; i < noi; i++){
        n->input[i] = inputs[i];
    }

    n->bias = rand();
    return n;
}

nlayer *createLayer(int non,int non_prevLayer){
    nlayer *layer = (nlayer*)malloc(sizeof(nlayer));
    layer->neurons = (neuron**)malloc(non*sizeof(neuron*));

    for (size_t i = 0; i < non; i++){
        layer->neurons[i] = createNeuron(non_prevLayer,0); // here i have to put smtg else in place of 0(ZERO)
    }

    //printf("%p\n",&(layer->neurons));

    return layer;
}

Nnetwrk *createNetwork(int nol,int noi,int* nstruct){
    Nnetwrk *network = (Nnetwrk*)malloc(sizeof(Nnetwrk));
    printf("%ld\n",sizeof(network));
    network->layers = (nlayer**)malloc(nol*sizeof(nlayer*));

    for (int i = 0; i < nol; i++)
    {

        //printf("%d\n",nstruct[i]);
        nlayer *inp_layer = createLayer(nstruct[i],0);
        network->layers[i] = inp_layer;//= createLayer(nstruct[i],0);
        //printf("addr of layer[%d] = %p\n",i,&(network->layers[i]));
        //printf("%ld\n",sizeof(&(network->layers[i])));
    }

    return network; 
    free(network);
}