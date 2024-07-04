#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define INPUT_SIZE 128
#define HIDDEN_SIZE 128
#define OUTPUT_SIZE 128
#define LEARNING_RATE 0.01
#define MAX_TEXT_LENGTH 100000

typedef struct {
    double ih_weights[INPUT_SIZE][HIDDEN_SIZE];
    double ho_weights[HIDDEN_SIZE][OUTPUT_SIZE];
    double hidden[HIDDEN_SIZE];
    double output[OUTPUT_SIZE];
} NeuralNetwork;

void initialize_weights(double weights[][HIDDEN_SIZE], int input_size, int hidden_size) {
    for (int i = 0; i < input_size; i++) {
        for (int j = 0; j < hidden_size; j++) {
            weights[i][j] = ((double)rand() / RAND_MAX) * 2 - 1;
        }
    }
}

void forward(NeuralNetwork *nn, char input[], int input_size) {
    // Forward pass from input to hidden layer
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        double sum = 0;
        for (int j = 0; j < input_size; j++) {
            sum += input[j] * nn->ih_weights[j][i];
        }
        nn->hidden[i] = tanh(sum);
    }
    
    // Forward pass from hidden layer to output
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        double sum = 0;
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            sum += nn->hidden[j] * nn->ho_weights[j][i];
        }
        nn->output[i] = exp(sum);
    }
    
    // Softmax activation
    double total = 0;
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        total += nn->output[i];
    }
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        nn->output[i] /= total;
    }
}

void train(NeuralNetwork *nn, char input[], char target[], int input_size) {
    forward(nn, input, input_size);
    
    // Backpropagation
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        nn->output[i] -= (i == target[0]) ? 1 : 0;
    }
    
    for (int i = 0; i < HIDDEN_SIZE; i++) {
        double sum = 0;
        for (int j = 0; j < OUTPUT_SIZE; j++) {
            sum += nn->output[j] * nn->ho_weights[i][j];
        }
        for (int j = 0; j < INPUT_SIZE; j++) {
            double delta_ih = sum * (1 - nn->hidden[i] * nn->hidden[i]) * input[j];
            nn->ih_weights[j][i] -= LEARNING_RATE * delta_ih;
        }
    }
    
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            nn->ho_weights[j][i] -= LEARNING_RATE * nn->output[i] * nn->hidden[j];
        }
    }
}

int main() {
    srand(time(NULL));
    
    FILE *file = fopen("text.txt", "r"); // Replace "text.txt" with your text file path
    if (!file) {
        printf("Failed to open file\n");
        return 1;
    }

    char text[MAX_TEXT_LENGTH];
    fgets(text, MAX_TEXT_LENGTH, file);
    fclose(file);
    
    int text_length = strlen(text);
    
    NeuralNetwork nn;
    initialize_weights(nn.ih_weights, INPUT_SIZE, HIDDEN_SIZE);
    initialize_weights(nn.ho_weights, HIDDEN_SIZE, OUTPUT_SIZE);

    int input_start = 0;
    int input_end = INPUT_SIZE;
    int target_index = input_end;
    
    for (int i = 0; i < text_length; i++) {
        char input[INPUT_SIZE];
        char target[1];
        
        strncpy(input, text + input_start, INPUT_SIZE);
        input[INPUT_SIZE] = '\0';
        
        target[0] = text[target_index];
        
        train(&nn, input, target, INPUT_SIZE);
        
        input_start++;
        input_end++;
        target_index++;
        if (input_end >= text_length) {
            input_start = 0;
            input_end = INPUT_SIZE;
            target_index = input_end;
        }
    }
    
    // Test the trained network
    printf("Enter a sequence of %d characters: ", INPUT_SIZE);
    char input[INPUT_SIZE];
    fgets(input, INPUT_SIZE + 1, stdin);
    input[INPUT_SIZE] = '\0';
    
    forward(&nn, input, INPUT_SIZE);
    
    // Print the predicted next character
    double max_prob = 0;
    char predicted_char;
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        if (nn.output[i] > max_prob) {
            max_prob = nn.output[i];
            predicted_char = i;
        }
    }
    
    printf("Predicted next character: %c\n", predicted_char);
    
    return 0;
}
