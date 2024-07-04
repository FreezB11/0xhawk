#include "nn.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define RAND_MAX 2147483647
#define rate 0.01f
float eps = 1.61012e-3;

float rand_float(void){
    return (float)rand()/(float)RAND_MAX;
}

double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

float cost(int NOS,int NOI,float inputs[NOS][NOI],float output[],float weights[],float bias){
    float result = 0.0f;
     for (int i=0;i<NOS;i++){
        float summ = 0.0f;
        for(int j=0;j<NOI;j++){
            summ += (inputs[i][j])*(weights[j]);
        }
        float y = sigmoid(summ+bias);
        //float y = summ +bias;
        float d = y-output[i];
        result += d*d;
    }
    result /= NOS;
    return result;
}

// float forward(){

// }

void LinearREG(int NOS,int NOI,float inputs[NOS][NOI],float output[NOS],float weights[NOI],float *bias){
    // defining weights array based on the size of the input array..
    float summ = 0.0f;
    float dw[NOI];
    srand(time(0));
    *bias = rand_float();
    printf(BRED);
    printf("bais == %f\n",*bias);
    printf(reset);
    for(int i=0;i<NOI;i++){
        weights[i] = rand_float()*10.0f;
        printf(BYEL);
        printf("weight[%d]==%f\n",i,weights[i]);
        printf(reset);
    }
    
    float costt = cost(NOS,NOI,inputs,output,weights,*bias);
    printf("initial cost==%f\n",costt);
 
    //float var = 0.0f;
    float t =0.0f;
    float dtb;
    for(int itr=0;itr<100*100;itr++)
        for(int j=0;j<NOI;j++){
            // float var = 0.0f;
            for(int i=0;i<NOS;i++){
                float var = 0.0f;
                for(int j=0;j<NOI;j++){
                    var += (inputs[i][j]*weights[j]);
                    //printf("%f\n",var);
                }
                var+=*bias;
                t += (output[i]-sigmoid(var))*(sigmoid(var))*(1-sigmoid(var))*inputs[i][j];
                dtb += (output[i]-sigmoid(var))*(sigmoid(var))*(1-sigmoid(var));
            }
            dw[j]=t;
            weights[j] = weights[j] + rate*dw[j];
            *bias = *bias +rate*dtb ;
        }

    printf("updated bias is %f\n",*bias);
    printf("w1=%f,,w2=%f\n",weights[0],weights[1]);

    float cost2 = cost(NOS,NOI,inputs,output,weights,*bias);
    printf("updated cost==%f\n",cost2);








    //dw[j] += ((output[i]/NOI)-var)

}