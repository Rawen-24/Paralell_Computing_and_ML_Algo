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

    // Input->Hidden
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

            // Hidden -> Output 
            double out1[OUTPUT_NEURONS]; 
            double out[OUTPUT_NEURONS];

            for (int j = 0; j < OUTPUT_NEURONS; j++)
            {
                out1[j] = 0.0;
                for (int k = 0; k < HIDDEN_NEURONS; k++)
                {
                    out1[j] += hidden[k] * w_hidden_output[k][j];
                }
                out[j] = sigmoid(out1[j]);
            }

            // here Out[i] is the result produced by my  network and it's a number either 0 or 1  (the prediction).
            // i corrected The Backprpagation , i was not iterating over the number of Samples which is very crucial 
            /*  After the forward pass, we perform backpropagation to compute how much each weight and bias contributed to the total error.
                This involves taking partial derivatives of the loss function using the chain rule of calculus:
                ∂L/∂w, ∂L/∂b
                w_new = w_old - learning rate *  ∂L/∂w-> this how we update the weight same rule for the bias !! 
                Then, using gradient descent, we update these parameters.
                The learning rate (α) defines the step size — a small α helps the model converge slowly but steadily, 
                while a large one may overshoot the optimal values. 
            */
             
            // ===== Backpropagation =====

            // Output layer errors and deltas
            double out_error[OUTPUT_NEURONS];
            double out_delta[OUTPUT_NEURONS];
            for (int j = 0; j < OUTPUT_NEURONS; j++) {
                out_error[j] = output[i][j] - out[j];
                out_delta[j] = out_error[j] * sigmoid_derivative(out[j]);
            }

            // Hidden layer deltas
            double hidden_delta[HIDDEN_NEURONS];
            for (int j = 0; j < HIDDEN_NEURONS; j++) {
                double error = 0.0;
                for (int k = 0; k < OUTPUT_NEURONS; k++) {
                    error += out_delta[k] * w_hidden_output[j][k];
                }
                hidden_delta[j] = error * sigmoid_derivative(hidden[j]);
            }

            // Update weights (Hidden -> Output)
            for (int j = 0; j < HIDDEN_NEURONS; j++) {
                for (int k = 0; k < OUTPUT_NEURONS; k++) {
                    w_hidden_output[j][k] += LEARNING_RATE * out_delta[k] * hidden[j];
                }
            }

            // Update weights (Input -> Hidden)
            for (int j = 0; j < INPUT_NEURONS; j++) {
                for (int k = 0; k < HIDDEN_NEURONS; k++) {
                    w_input_hidden[j][k] += LEARNING_RATE * hidden_delta[k] * input[i][j];
                }
            }
        }
    }

    // Testing
    printf("\nFinal results:\n");
    for (int i = 0; i < TRAINING_SAMPLES; i++) {
        double hidden[HIDDEN_NEURONS];
        for (int j = 0; j < HIDDEN_NEURONS; j++) {
            hidden[j] = 0.0;
            for (int k = 0; k < INPUT_NEURONS; k++) {
                hidden[j] += input[i][k] * w_input_hidden[k][j];
            }
            hidden[j] = sigmoid(hidden[j]);
        }

        double out = 0.0;
        for (int j = 0; j < HIDDEN_NEURONS; j++) {
            out += hidden[j] * w_hidden_output[j][0];
        }
        out = sigmoid(out);

        printf("Input: %.0f %.0f => Output: %.3f\n", input[i][0], input[i][1], out);
    }

    return 0;
}
