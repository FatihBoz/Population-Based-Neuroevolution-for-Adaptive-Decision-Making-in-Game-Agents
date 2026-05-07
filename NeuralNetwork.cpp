#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(int inputNodes, int hiddenNodes, int outputNodes)
	: inputNodes(inputNodes), hiddenNodes(hiddenNodes), outputNodes(outputNodes) {
	std::random_device rd;
	rng = std::mt19937(rd());
	// random real number
	std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

	weights_ih.resize(hiddenNodes, std::vector<float>(inputNodes));
	weights_ho.resize(outputNodes, std::vector<float>(hiddenNodes));
	bias_h.resize(hiddenNodes);
	bias_o.resize(outputNodes);

	// ---Initialize weights and biases with random values---

	//Input -> Hidden
	for (int i = 0; i < hiddenNodes; ++i)
		for (int j = 0; j < inputNodes; ++j)
			weights_ih[i][j] = dist(rng);

	//Hidden -> Output
	for (int i = 0; i < outputNodes; ++i)
		for (int j = 0; j < hiddenNodes; ++j)
			weights_ho[i][j] = dist(rng);

	//Biases
	for (int i = 0; i < hiddenNodes; ++i)
		bias_h[i] = dist(rng);

	for (int i = 0; i < outputNodes; ++i)
		bias_o[i] = dist(rng);
}

std::vector<float> NeuralNetwork::feedForward(const std::vector<float>& inputs) {
	std::vector<float> hidden(hiddenNodes);
	std::vector<float> output(outputNodes);

	// Input -> Hidden
	for (int i = 0; i < hiddenNodes; ++i) {
		float sum = 0.0f;
		for (int j = 0; j < inputNodes; ++j)
			sum += weights_ih[i][j] * inputs[j];
		sum += bias_h[i]; // Add bias
		hidden[i] = sigmoid(sum);
	}
	// Hidden -> Output
	for (int i = 0; i < outputNodes; ++i) {
		float sum = 0.0f;
		for (int j = 0; j < hiddenNodes; ++j)
			sum += weights_ho[i][j] * hidden[j];
		sum += bias_o[i]; // Add bias	

		if (i == 0) {
			output[i] = tanh(sum);
		}
		else {
			output[i] = sigmoid(sum);
		}
	}
	return output;
}


void NeuralNetwork::mutate(float mutationRate) {
	// Changes between -0.5 and 0.5
	std::uniform_real_distribution<float> changeDist(-1.0f, 1.0f);
	std::uniform_real_distribution<float> probDist(0.0f, 1.0f);

	// mutate weights (Input -> Hidden)
	for (int i = 0; i < hiddenNodes; ++i) {
		for (int j = 0; j < inputNodes; ++j) {
			if (probDist(rng) < mutationRate) {
				weights_ih[i][j] += changeDist(rng);
			}
		}
	}

	// mutate weights (Hidden -> Output)
	for (int i = 0; i < outputNodes; ++i) {
		for (int j = 0; j < hiddenNodes; ++j) {
			if (probDist(rng) < mutationRate) {
				weights_ho[i][j] += changeDist(rng);
			}
		}
	}

	// mutate biases
	for (int i = 0; i < hiddenNodes; ++i) {
		if (probDist(rng) < mutationRate) bias_h[i] += changeDist(rng);
	}
	for (int i = 0; i < outputNodes; ++i) {
		if (probDist(rng) < mutationRate) bias_o[i] += changeDist(rng);
	}
}

void NeuralNetwork::reseed() {
	std::random_device rd;
	rng.seed(rd());
}