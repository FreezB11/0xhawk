#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/calculas.h"
#include "../lib/color.h"

#define RAND_MAX 2147483647
// float eps = 1.61012e-4;

#define train_count (sizeof(train)/sizeof(train[0]))

int train[][2] ={
  //{x,y}
    {0,0},
    {1,2},
    {2,4},
    {3,6},
    {4,8},
    {5,10}
}; 

// float layer1_weight[];

// float Z(float weight[],int data[]){
//     int sum;
//     for(size_t i=0;i<train_count;i++){
//         sum += weight[i]*data[i];
//     }
//     return sum;
// }

void test(void *test_inp){

}

float rand_float(void){
    return (float)rand()/(float)RAND_MAX;
}

float cost(float w){
    float result = 0.0f;
    for(size_t i =0;i<train_count;++i){
        float x = train[i][0];
        float y = x*w;
        float d = y - train[i][1];
        result += d*d; 
        // printf("actual :: %f, expected :: %d\n",y,train[i][1]);
    }

    result /= train_count;
    return result;
}

int main (){
    srand(69); // aslo tim(0) can be used
    //y=w*x
    float w = rand_float()*10;
    float rate = 0.001f;

    printf("%f\n",cost(w));
    for(size_t i =0;i<2000;++i){
        float dcost = df(cost,w);
        w -= rate*dcost;
        printf("%f\n",cost(w));
    }
    printf(RED);
    printf("%f\n",w);
    printf(reset);
    
    return 0;
}