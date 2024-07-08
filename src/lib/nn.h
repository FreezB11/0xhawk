#ifndef _NN_H
#define _NN_H

#include <stdlib.h>
#include "math/calculas.h"

#define LEARNING_RATE 0.07 // Example learning rate
#define NUM_EPOCHS 100*1000 // Example number of training epochs

typedef struct {
    double input;
    double bias;
    double output;
    double delta;
} neuron;

typedef struct {
    int num_neurons;
    neuron *neurons;
} layer;

typedef struct {
    int num_layers;
    layer *layers;
}network;

network* create_network(int num_layers, int* num_neurons_per_layer);
void link_layers(network* net);
void feed_forward(network* net, double* input);
void backpropagation(network* net, double* target);
void update_weights(network* net);
void train_network(network* net, double** inputs, double** targets, int num_training_sets);

#endif // !