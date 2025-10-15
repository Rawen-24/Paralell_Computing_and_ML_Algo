#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define INPUT_NEURONS 2
#define HIDDEN_NEURONS 2
#define OUTPUT_NEURONS 1
#define TRAINING_SAMPLES 4
#define LEARNING_RATE 0.5
#define EPOCHS 10000

// Sigmoid activation function
double sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

double sigmoid_derivative(double x)
{
    return x * (1.0 - x);
}

// Initialize weights randomly
void initialize_weights(double *weights, int size)
{
    for (int i = 0; i < size; i++)
    {
        weights[i] = ((double)rand() / RAND_MAX) - 0.5;
    }
}

int main()
{
    srand(time(NULL));

    // Training data (XOR problem)
    double input[TRAINING_SAMPLES][INPUT_NEURONS] = {
        {0, 0}, {0, 1}, {1, 0}, {1, 1}};
    double output[TRAINING_SAMPLES][OUTPUT_NEURONS] = {
        {0}, {1}, {1}, {0}};

    // Weights
    double w_input_hidden[INPUT_NEURONS][HIDDEN_NEURONS];
    double w_hidden_output[HIDDEN_NEURONS][OUTPUT_NEURONS];
    initialize_weights(&w_input_hidden[0][0], INPUT_NEURONS * HIDDEN_NEURONS);
    initialize_weights(&w_hidden_output[0][0], HIDDEN_NEURONS * OUTPUT_NEURONS);

    // Training loop

    //Input->Hidden
    for (int epoch = 0; epoch < EPOCHS; epoch++)
    {
        for (int i = 0; i < TRAINING_SAMPLES; i++)
        {
            // Forward pass
            double hidden[HIDDEN_NEURONS];
            for (int j = 0; j < HIDDEN_NEURONS; j++)
            {
                hidden[j] = 0;
                for (int k = 0; k < INPUT_NEURONS; k++)
                    hidden[j] += input[i][k] * w_input_hidden[k][j];
                hidden[j] = sigmoid(hidden[j]);
            }
        }
    }

    // Hidden -> Output 
    double out1[HIDDEN_NEURONS]; 
    double out[HIDDEN_NEURONS];

    for(int i = 0; i< OUTPUT_NEURONS;i++){
        out1[i]= 0.0;
        for(int j = 0 ; j< HIDDEN_NEURONS; j++){
            out1[i] += hidden[j]*w_hidden_output[j][i]
        }
        out[i]=sigmoid(out1[i])
    }


    // ===== Backpropagation =====

    // Output layer errors and deltas
    double out_error[OUTPUT_NEURONS];
    double out_delta[OUTPUT_NEURONS];
        for (int j = 0; j < OUTPUT_NEURONS; j++) {
            out_error[j] = output[i][j] - out[j];
            out_delta[j] = out_error[j] * sigmoid_derivative(out[j]);
        }
}
