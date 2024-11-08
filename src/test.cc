#include <eigen3/Eigen/Dense>
#include <cmath>
#include <iostream>
#include <vector>

using namespace Eigen;

MatrixXf xavierInit(int rows, int cols){
    // Xavier Initialization: keep values within bounds for stability
    return MatrixXf::Random(rows, cols) * sqrt(2.0 / (rows + cols));
}

// Self-Attention Mechanism
MatrixXf SAM(const MatrixXf &Q, const MatrixXf &K, const MatrixXf &V){
    int d_k = Q.cols();

    MatrixXf QK = Q * K.transpose();

    QK = QK / std::sqrt(d_k);

    // Softmax with numerical stability (subtracting max per row)
    for(int i = 0; i < QK.rows(); i++){
        // Subtract max for numerical stability
        float maxCoeff = QK.row(i).maxCoeff();
        QK.row(i) = (QK.row(i).array() - maxCoeff).exp();
        QK.row(i) /= QK.row(i).sum();
    }

    MatrixXf output = QK * V;
    return output;
}

// Number of attention heads
const int NUM_HEADS = 8;

MatrixXf MHA(const MatrixXf &Q, const MatrixXf &K, const MatrixXf &V){
    int d_model = Q.cols();
    int d_k = d_model / NUM_HEADS;

    // Split Q, K, V into multiple heads
    std::vector<MatrixXf> heads_output(NUM_HEADS);
    for(int i = 0; i < NUM_HEADS; i++){
        MatrixXf Q_i = Q.block(0, i * d_k, Q.rows(), d_k);
        MatrixXf K_i = K.block(0, i * d_k, K.rows(), d_k);
        MatrixXf V_i = V.block(0, i * d_k, V.rows(), d_k);

        heads_output[i] = SAM(Q_i, K_i, V_i);
    }

    MatrixXf output(Q.rows(), d_model);
    for(int i = 0; i < NUM_HEADS; ++i){
        output.block(0, i * d_k, Q.rows(), d_k) = heads_output[i];
    }

    return output;
}

MatrixXf feedForward(const MatrixXf &input, int d_ff){
    int d_model = input.cols();
    
    MatrixXf W1 = xavierInit(d_model, d_ff);
    RowVectorXf b1 = RowVectorXf::Random(d_ff);
    MatrixXf W2 = xavierInit(d_ff, d_model);
    RowVectorXf b2 = RowVectorXf::Random(d_model);

    MatrixXf hidden = input * W1;
    hidden.rowwise() += b1;
    hidden = hidden.array().max(0); // ReLU activation

    MatrixXf output = hidden * W2;
    output.rowwise() += b2;

    return output;
}

// Transformer block
MatrixXf transformerBlock(const MatrixXf &input, int d_ff){
    // MHA
    MatrixXf attn_output = MHA(input, input, input);
    // ADD AND NORM
    MatrixXf add_norm1 = attn_output + input;
    // FEEDFORWARD
    MatrixXf ff_output = feedForward(add_norm1, d_ff);
    // ADD AND NORM
    MatrixXf add_norm2 = ff_output + add_norm1;

    return add_norm2;
}

// Sinusoidal Positional Encoding (for numerical stability)
MatrixXf positionalEncoding(int sequence_length, int d_model){
    MatrixXf pos_encoding(sequence_length, d_model);
    for(int pos = 0; pos < sequence_length; ++pos){
        for(int i = 0; i < d_model; ++i){
            float div_term = std::pow(10000.0f, (2.0f * (i / 2)) / d_model);
            if(i % 2 == 0){
                pos_encoding(pos, i) = std::sin(pos / div_term);
            } else {
                pos_encoding(pos, i) = std::cos(pos / div_term);
            }
        }
    }
    return pos_encoding;
}

// Transformer Encoder function
MatrixXf transformerEncoder(const MatrixXf &input, int num_layers, int d_ff){
    // Add positional encoding to input
    MatrixXf pos_encoding = positionalEncoding(input.rows(), input.cols());
    MatrixXf encoder_input = input + pos_encoding;

    // Pass through each transformer block
    MatrixXf output = encoder_input;
    for(int i = 0; i < num_layers; ++i){
        output = transformerBlock(output, d_ff);
    }
    return output;
}

int main(){
    // Define model parameters
    int sequence_length = 10;  // Example sequence length
    int d_model = 64;          // Dimensions of embeddings
    int d_ff = 128;            // Dimension of feedforward network
    int num_layers = 6;        // Number of transformer blocks

    // Initialize a random input sequence
    MatrixXf input_sequence = MatrixXf::Random(sequence_length, d_model);

    // Encode the sequence using the transformer encoder
    MatrixXf encoded_sequence = transformerEncoder(input_sequence, num_layers, d_ff);

    // Print the result
    std::cout << "Encoded Sequence:\n" << encoded_sequence << std::endl;

    return 0;
}
