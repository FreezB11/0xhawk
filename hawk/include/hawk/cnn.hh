#pragma once
#include <eigen3/Eigen/Dense>
#include <hawk/lib/mmath.h>
#include <vector>
#include <hawk/conv.h>
#include <hawk/matrix.h>

#define IMAGED 28 // taking the image to be square
namespace HAWK{
    namespace CNN{
typedef struct trainset{
    int                                         id;
    Eigen::MatrixXd                             image;
}trainset;

typedef struct _layer{
    const char*                                 _type; //i.e convolution or pool
    // int                                         test;
    int                                         filters = 1;
    int                                         kernel_s;
    int                                         stride = 1;
    int                                         padding = 0;
    // Eigen::MatrixXf         (*convolve)(Eigen::MatrixXf& base, Eigen::MatrixXf& kernel, int padd, int stride);
    Eigen::MatrixXd                             (*pool)(matrix& input, int pool_size, int stride, int padding) = nullptr;
}_layer;

typedef struct model{
    int                                         out_param_size;
    std::vector<int>                            hidden_lyrs; // this is for the neural network
    double                                      (*activation)(double x);
    const char*                                 _testset;
    const char*                                 _trainset;
    std::vector<_layer>                         layers;
}model;


class csv{
private:
    int rows = 0;
public:
    csv(const char* filename);
    ~csv();
    trainset                                    read_data(const char* filename, int n);
    int                                         getrow();
};

class cnn{
private:
    int max_fc =                                0;
    std::vector<std::vector<Eigen::MatrixXd>>   buff_data;
    std::vector<std::vector<Eigen::MatrixXd>>   filters;
    std::vector<double>                         out_n;
    model                                       net;
    int                                         rows;
    void                                        frwd_p(trainset & curr);
    void                                        _train(trainset &curr);
    std::vector<double>                         flatten(Eigen::MatrixXd& input);


public:
    cnn(model& cnnmodel);  
    ~cnn();
    void                                        train();  
};
    }// namespace CNN
}// namespace HAWK