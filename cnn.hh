#pragma once
#include <eigen3/Eigen/Dense>
#include "./lib/mmath.h"
#include <vector>

#define IMAGED 28 // taking the image to be square

typedef struct trainset{
    int                     id;
    Eigen::MatrixXd         image;
}trainset;

typedef struct _layer{
    const char*             _type; //i.e convolution or pool
    int                     test;
    int                     filters = 1;
    int                     kernel_s;
    int                     stride = 1;
    int                     padding = 0;
    // Eigen::MatrixXf         (*convolve)(Eigen::MatrixXf& base, Eigen::MatrixXf& kernel, int padd, int stride);
    Eigen::MatrixXd         (*pool)(Eigen::MatrixXd& input) = nullptr;
}_layer;

typedef struct _arch{
    int                     out_param_size;
    std::vector<int>        hidden_lyrs; // this is for the neural network
    double                  (*activation)(double x);
    const char*             _testset;
    const char*             _trainset;
    std::vector<_layer>    layers;
}_arch;


class csv{
private:
    int rows = 0;
public:
    csv(const char* filename);
    ~csv();
    trainset                read_data(const char* filename, int n);
    int                     getrow();
};


class cnn{
private:
    int max_fc = 0;
    std::vector<std::vector<int>> nlayers;
    std::vector<std::vector<int>> nlweights;
    std::vector<Eigen::MatrixXd>  buff_data;
    std::vector<std::vector<Eigen::MatrixXd>> filters;
    std::vector<Eigen::MatrixXd> kernels;
    std::vector<double>     out_n;
    _arch                   net;
    int                     rows;
    void                    frwd_p(trainset & curr);
    void                    _train(trainset &curr);
    std::vector<double>     flatten(Eigen::MatrixXd& input);


public:
    cnn(_arch& cnn_arch);  
    ~cnn();
    void                    train();  
};