#include "nn.h"
#include <stdlib.h>
#include <stdio.h>
#include "math/calculas.h"
#include <math.h>

network* create_network(int num_layers, int* num_neurons_per_layer) {
    network* net = (network*)malloc(sizeof(network));
    net->num_layers = num_layers;
    net->layers = (layer*)malloc(num_layers * sizeof(layer));
    neuron t;
    for (int i = 0; i < num_layers; i++) {
        net->layers[i].num_neurons = num_neurons_per_layer[i];
        net->layers[i].neurons = (neuron*)malloc(num_neurons_per_layer[i] * sizeof(neuron));
        //printf("layer[%d] = %p\n",i,&(net->layers[i]));
    }
    
    return net;
}

void link_layers(network* net) {
    for (int i = 0; i < net->num_layers - 1; i++) {
        for (int j = 0; j < net->layers[i].num_neurons; j++) {
            net->layers[i].neurons[j].output = 0.0;
            net->layers[i].neurons[j].bias = 0.0;   
            for (int k = 0; k < net->layers[i + 1].num_neurons; k++) {
                // Establish connections between neurons in adjacent layers
                // Set the output of neurons in the current layer as the input of neurons in the next layer
                // For simplicity, let's assume each neuron in the next layer receives input from all neurons in the current layer
                net->layers[i + 1].neurons[k].input += net->layers[i].neurons[j].output;
            }
        }
    }
}

void feed_forward(network* net, double* input) {
    // Set input values for the input layer
    for (int i = 0; i < net->layers[0].num_neurons; i++) {
        net->layers[0].neurons[i].output = input[i];
    }

    // Forward propagation through the network
    for (int i = 1; i < net->num_layers; i++) {
        for (int j = 0; j < net->layers[i].num_neurons; j++) {
            double sum = 0.0;
            // Calculate the weighted sum of inputs
            for (int k = 0; k < net->layers[i - 1].num_neurons; k++) {
                sum += net->layers[i - 1].neurons[k].output; // Input from the previous layer's neurons
            }
            sum += net->layers[i].neurons[j].bias; // Add bias
            // Apply activation function (sigmoid in this case)
            net->layers[i].neurons[j].output = sigmoid(sum);
        }
    }
}

void backpropagation(network* net, double* target) {
    // Backpropagate the error from the output layer to the previous layers
    for (int i = net->num_layers - 1; i > 0; i--) {
        for (int j = 0; j < net->layers[i].num_neurons; j++) {
            neuron* neuron = &net->layers[i].neurons[j];
            // Calculate the error for the output layer
            if (i == net->num_layers - 1) {
                neuron->delta = (target[j] - neuron->output) * sigmoid_derivative(neuron->output);
            } else {
                // Calculate the error for hidden layers
                neuron->delta = 0.0;
                for (int k = 0; k < net->layers[i + 1].num_neurons; k++) {
                    neuron->delta += net->layers[i + 1].neurons[k].delta * 1.0; // Assuming all neurons are connected
                }
                neuron->delta *= sigmoid_derivative(neuron->output);
            }
        }
    }
}

void update_weights(network* net) {
    // Update weights and biases using the calculated deltas
    for (int i = 1; i < net->num_layers; i++) {
        for (int j = 0; j < net->layers[i].num_neurons; j++) {
            neuron* neuron = &net->layers[i].neurons[j];
            for (int k = 0; k < net->layers[i - 1].num_neurons; k++) {
                // Update weights
                // Example of weight update using gradient descent
                // Adjust the weight by adding the product of the input, delta, and learning rate
                neuron->input += net->layers[i - 1].neurons[k].output * neuron->delta * LEARNING_RATE;
            }
            // Update bias
            neuron->bias += neuron->delta * LEARNING_RATE;
        }
    }
}

void train_network(network* net, double** inputs, double** targets, int num_training_sets) {
    for (int epoch = 0; epoch < NUM_EPOCHS; epoch++) {
        for (int set = 0; set < num_training_sets; set++) {
            // Forward propagation
            feed_forward(net, inputs[set]);
            // Backpropagation
            backpropagation(net, targets[set]);
            // Update weights and biases
            update_weights(net);
        }
    }
}