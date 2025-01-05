#pragma once
#include <eigen3/Eigen/Dense>
#include "./lib/mmath.hh"
#include <vector>

typedef struct trainset{
    int                     id;
    Eigen::MatrixXf         image;
}trainset;

typedef struct _layers{
    Eigen::MatrixXf         (*convolve)(Eigen::MatrixXf& base, Eigen::MatrixXf& kernel, int padd, int stride);
    Eigen::MatrixXf         (*pool)(Eigen::MatrixXf& input);
}_layers;

typedef struct _arch{
    int                     kernel_size;
    int                     out_param_size;
    double                  (*activation)(double x);
    const char*             _testset;
    const char*             _trainset;
    std::vector<_layers>    layer;
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
    Eigen::MatrixXf         image;
    std::vector<Eigen::MatrixXf> filters;
    _arch                   net;
    int                     rows;
    void                    frwd_p(trainset & curr);
    void                    _train(trainset &curr);

public:
    cnn(_arch& cnn_arch);  
    ~cnn();
    void                    train();  
};