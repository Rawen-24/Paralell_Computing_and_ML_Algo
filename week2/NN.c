#include <mpi.h>
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

// example of an activation function 

double sigmoid (double x ){
    return 1.0 / (1.0 + exp (-x));
}
double sigmoid_derivative(double x){
    return exp(-x)/pow(1.0+exp(-x),2);
}

// initialize the weights randomly 
// here we have 2 Inout neurons (each neuron represent usually a feature )
// we need to assign random weights to each neuron in  The hidden Layer to calculate the weighted sum Z_i = w_i * x_i+b_i


// we need to use rand()
void initialize_weights(double*weights,int size){
    for (int i = 0 ; i < size ; i++){
        // RAND_MAX is a constant in the #include <stdlib.h> hearder and by deduction 0.5 we make sure 
        // that the weights range is beween -0.5 and 0.5 and since the weight affected the weighted sum , it will be benificial to not choose a big value 

        weights[i]= ((double )rand() / RAND_MAX )-0.5 ; 

    }


}
//MPI
int main(int argc , char ** argv){

    // initialize the Env
    MPI_Init(&argc , &argv); 
    int rank, size ; 
    // rank: rank of the poricessor 
    // size number of Processes 
    MPI_Comm_rank(MPI_COMM_WORLD,&rank); 
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    srand(time(NULL) + rank);

    // Training data (XOR problem)
    double input[TRAINING_SAMPLES][INPUT_NEURONS] = {
        {0, 0}, {0, 1}, {1, 0}, {1, 1}};
    double output[TRAINING_SAMPLES][OUTPUT_NEURONS] = {
        {0}, {1}, {1}, {0}};

    MPI_Finalize();
    return 0;
}
