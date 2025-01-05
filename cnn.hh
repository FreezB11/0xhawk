#pragma once
#include <eigen3/Eigen/Dense>
#include "./lib/mmath.hh"
#include <vector>

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
    Eigen::MatrixXd         buff_data;
    std::vector<std::pair <Eigen::MatrixXd,int>> filters;
    std::vector<Eigen::MatrixXd> kernels;
    _arch                   net;
    int                     rows;
    void                    frwd_p(trainset & curr);
    void                    _train(trainset &curr);

public:
    cnn(_arch& cnn_arch);  
    ~cnn();
    void                    train();  
};