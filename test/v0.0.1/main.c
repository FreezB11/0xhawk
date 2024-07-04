#include <stdio.h>
#include "lib/nn.h"

#define inp_size 2

int main(){
    
    float inp[][inp_size] ={{0,0},
                    {0,1},
                    {1,0},
                    {1,1}}; 

    float output[4]={0,0,0,1};
    float bias;
    float weight[inp_size];

    LinearREG(LENS(inp),inp_size,inp,output,weight,&bias);

    printf("0 || 0 == %f actual == %f\n",sigmoid(0*weight[0]+0*weight[1]+bias),output[0]);
    printf("0 || 1 == %f actual == %f\n",sigmoid(0*weight[0]+1*weight[1]+bias),output[1]);
    printf("1 || 0 == %f actual == %f\n",sigmoid(1*weight[0]+0*weight[1]+bias),output[2]);
    printf("1 || 1 == %f actual == %f\n",sigmoid(1*weight[0]+1*weight[1]+bias),output[3]);

    return 0;
}