#include "nn.h"
#include <stdio.h>


int main(){

    //float input[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    float output[4] = {0,0,0,1};

    int nns[5]={3,1,0,5,9};

    // printf("%ld\n",sizeof(neuron));
    // printf("%ld\n",sizeof(nlayer));
    // printf("%ld\n",sizeof(Nnetwrk));

    //Matrix inp = create_matrix(4,2);

    Nnetwrk *testnet = createNetwork(5,0,nns);
    

    free(testnet);

    // neuron *n = createNeuron(5,input);
    // printf("%f\n",n->input[4]);

    return 0;
}