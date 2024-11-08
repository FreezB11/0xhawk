#include <eigen3/Eigen/Dense>
#include <cmath>
#include <iostream>

using namespace Eigen;

// Helper function for Xavier Initialization
MatrixXf xavierInit(int rows, int cols) {
    return MatrixXf::Random(rows, cols) * sqrt(2.0 / (rows + cols));
}

// Positional Encoding
MatrixXf positionalEncoding(int seq_len, int d_model) {
    MatrixXf pos_encoding(seq_len, d_model);
    for (int pos = 0; pos < seq_len; ++pos) {
        for (int i = 0; i < d_model; ++i) {
            if (i % 2 == 0) {
                pos_encoding(pos, i) = sin(pos / pow(10000, 2.0 * i / d_model));
            } else {
                pos_encoding(pos, i) = cos(pos / pow(10000, 2.0 * (i - 1) / d_model));
            }
        }
    }
    return pos_encoding;
}

// Self-Attention Mechanism
MatrixXf selfAttention(const MatrixXf &Q, const MatrixXf &K, const MatrixXf &V) {
    MatrixXf scores = (Q * K.transpose()) / sqrt(Q.cols());
    MatrixXf attention_weights = scores.array().exp();
    attention_weights = attention_weights.array().colwise() / attention_weights.rowwise().sum().array();
    return attention_weights * V;
}

// Feed-Forward Layer
MatrixXf feedForward(const MatrixXf &input, int d_ff) {
    int d_model = input.cols();
    MatrixXf W1 = xavierInit(d_model, d_ff);
    RowVectorXf b1 = RowVectorXf::Zero(d_ff);
    MatrixXf W2 = xavierInit(d_ff, d_model);
    RowVectorXf b2 = RowVectorXf::Zero(d_model);

    MatrixXf hidden = input * W1;
    hidden.rowwise() += b1;
    hidden = hidden.array().max(0); // ReLU activation

    MatrixXf output = hidden * W2;
    output.rowwise() += b2;

    return output;
}

// Transformer Encoder
MatrixXf transformerEncoder(const MatrixXf &input, int d_ff) {
    int d_model = input.cols();

    // Step 1: Self-Attention
    MatrixXf Wq = xavierInit(d_model, d_model);
    MatrixXf Wk = xavierInit(d_model, d_model);
    MatrixXf Wv = xavierInit(d_model, d_model);
    MatrixXf Q = input * Wq;
    MatrixXf K = input * Wk;
    MatrixXf V = input * Wv;
    MatrixXf attention_output = selfAttention(Q, K, V);

    // Step 2: Add & Norm
    MatrixXf norm1_output = input + attention_output;

    // Step 3: Feed-Forward
    MatrixXf ff_output = feedForward(norm1_output, d_ff);

    // Step 4: Add & Norm
    MatrixXf encoder_output = norm1_output + ff_output;

    return encoder_output;
}

int main() {
    // Parameters
    int seq_len = 10;
    int d_model = 64;
    int d_ff = 128;

    // Input and positional encoding
    MatrixXf input = MatrixXf::Random(seq_len, d_model); // Example input
    MatrixXf pos_encoding = positionalEncoding(seq_len, d_model);
    input += pos_encoding;

    // Transformer Encoder
    MatrixXf encoded_sequence = transformerEncoder(input, d_ff);

    // Print the encoded sequence
    std::cout << "Encoded Sequence:\n" << encoded_sequence << std::endl;

    return 0;
}
