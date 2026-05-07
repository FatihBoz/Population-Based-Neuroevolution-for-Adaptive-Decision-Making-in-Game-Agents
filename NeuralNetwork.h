#pragma once

#include <vector>
#include <cmath>
#include <random>

class NeuralNetwork {
private:
    int inputNodes;
    int hiddenNodes;
    int outputNodes;

    // Weights
    std::vector<std::vector<float>> weights_ih; // Input --> Hidden
    std::vector<std::vector<float>> weights_ho; // Hidden --> Output

    // Biases
    std::vector<float> bias_h; // Hidden
    std::vector<float> bias_o; // Output

    // RNG
    std::mt19937 rng;


    float sigmoid(float x) {
        return 1.0f / (1.0f + std::exp(-x));
    }

    float tanh(float x) {
        return std::tanh(x);
    }


public:

    NeuralNetwork(int inputNodes, int hiddenNodes, int outputNodes);
    std::vector<float> feedForward(const std::vector<float>& inputs);
    void mutate(float mutationRate);
    void reseed();
};