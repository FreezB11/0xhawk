#pragma once
/**
   @file: transformer.h
   @breif: we shall make a transformer
*/
/*
    -->> key components of transformer
        .selfattention mechanism(to understand relationships between words)
        .multi-head attention(multiple SAM in parallel
        .feedforward neural network(simple dense layer in each transformer block
        .positional encoding(adds sequence indo to token embedding)
*/

/*  
    self-attention mechanism(SAM)
    -> calculates the relationship between each token in a sequence and every other token.
    .each word/token in a sentence is converted in three vectors
        :Query(Q) -> what this word is looking for.
        :Key(K)   -> what information this word has.
        :Value(V) -> the information itself.
    .for each pair of tokens, the model computes
                ATTENTION(Q,K,V) = softmax(q.k^t / sqrt(d_k) ) . V
            d_k is the dimension of the keys
*/
#include <eigen3/Eigen/Dense>
#include <cmath>
#include <iostream>
#include <vector>

using namespace Eigen;

MatrixXf xavierInit(int rows, int cols);
RowVectorXf xavierInit(int cols);

class LayerNorm{
private:
    VectorXf                    gamma;
    VectorXf                    beta;
    float                       eps = 1e-5;
    int                         d_model;

public:
                                LayerNorm(int d_model);
    MatrixXf                    forward(const MatrixXf& x);

};

MatrixXf scaled_dot_product_attention(const MatrixXf& Q, const MatrixXf& K, const MatrixXf& V);

class MultiHeadAttention{
private:
    int                         num_heads;
    int                         d_model;
    int                         d_k;
    int                         d_v;
    std::vector<MatrixXf>       WQs;
    std::vector<MatrixXf>       WQk;
    std::vector<MatrixXf>       WQs;
    MatrixXf                    WO;

public:
                                MultiHeadAttention(int num_heads, int d_model);
    MatrixXf                    forward(const MatrixXf& Q, const MatrixXf& K, const MatrixXf& V);
};

// position wise Feed Forward Network
class FeedForward{
private:
    MatrixXf                    W1;
    RowVectorXf                 b1;
    MatrixXf                    W2;
    RowVectorXf                 b2;
    int                         d_model;
    int                         d_ff;

public:
                                FeedForward(int d_model, int d_ff);
    MatrixXf                    forward(const MatrixXf& x);
};

class TransformerEncoderLayer{
private:
    MultiHeadAttention          mha;
    FeedForward                 ff;
    LayerNorm                   ln1;
    LayerNorm                   ln2;
    int                         d_model;

public:
                                TransformerEncoderLayer(int num_heads, int d_model, int d_ff);
    MatrixXf                    forward(const MatrixXf& x);
};

MatrixXf positionalEncoding(int max_seq_len, int d_model);

class TransformerEncoder{
private:
    std::vector<TransformerEncoderLayer>    layers;
    int                                     d_model;
    int                                     num_layers;
    MatrixXf                                pe;

public:
                                            TransformerEncoder(int num_layers, int num_heads, int d_model, int d_ff, int max_seq_len);
    MatrixXf                                forward(const MatrixXf& x);
};