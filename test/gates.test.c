#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


float sigmoidf(float x){
    return 1.f/(1.f + expf(-x));
}

#define RAND_MAX 2147483647
float eps = 1.61012e-3;

#define train_count (sizeof(train)/sizeof(train[0]))

int train[][3] ={
  //{x,y}
    {0,0,0},
    {1,0,1},
    {0,1,1},
    {1,1,1}
};

float rand_float(void){
    return (float)rand()/(float)RAND_MAX;
}

float cost(float w1,float w2,float b){
    float result = 0.0f;
    for(size_t i =0;i<train_count;++i){
        float y = sigmoidf((train[i][0])*w1+(train[i][1])*w2+b);
        float d = y - train[i][2];
        result += d*d; 
    }
    result /= train_count;
    return result;
}
int main(){

    printf("%ld\n",train_count); //4
    srand(time(0));
    float w1 = rand_float();
    float w2 = rand_float();
    float b = rand_float();

    float rate = 0.01f;

    printf("w1= %f,w2 = %f, bias = %f\n",w1,w2,b);
    printf("cost = %f\n",cost(w1,w2,b));

    for(size_t i =0;i<1000*1000;++i){
        float dw1 = (cost(w1+eps,w2,b)-cost(w1-eps,w2,b))/(2*eps);
        float dw2 = (cost(w1,w2+eps,b)-cost(w1,w2-eps,b))/(2*eps);
        float dbias = (cost(w1,w2,b+eps)-cost(w1,w2,b-eps))/(2*eps);
        w1 -= rate*dw1;
        w2 -= rate*dw2;
        b  -= rate*dbias;
        // printf("w1= %f,w2 = %f,b = %f || ERR = %f\n",w1,w2,b,cost(w1,w2,b));
    }

    for(size_t i=0;i<2;++i){
        for(size_t j=0;j<2;++j){
            printf("%zu | %zu == %f\n",i,j,sigmoidf(i*w1+j*w2+b));
        }
    }

    return 0;
}
