#include <vector>
#include <cmath>
#include <random>
#include <algorithm>

class NeuralNetwork {
    struct Layer {
        std::vector<std::vector<float>> weights;
        std::vector<float> biases;
        std::vector<float> outputs;
    };

    std::vector<Layer> layers;
    float learningRate;

public:
    NeuralNetwork(std::vector<int> topology, float lr = 0.01f) : learningRate(lr) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<float> dist(0.0f, 0.1f);

        for (size_t i = 1; i < topology.size(); ++i) {
            Layer layer;
            layer.weights.resize(topology[i], 
                std::vector<float>(topology[i-1]));
            layer.biases.resize(topology[i]);
            layer.outputs.resize(topology[i]);

            for (auto& w : layer.weights)
                for (auto& val : w)
                    val = dist(gen);
            for (auto& b : layer.biases)
                b = dist(gen);

            layers.push_back(layer);
        }
    }

    float sigmoid(float x) { return 1.0f / (1.0f + exp(-x)); }

    std::vector<float> forward(const std::vector<float>& input) {
        for (size_t i = 0; i < layers.size(); ++i) {
            const auto& prevOutputs = i == 0 ? input : layers[i-1].outputs;
            for (size_t n = 0; n < layers[i].outputs.size(); ++n) {
                float sum = layers[i].biases[n];
                for (size_t w = 0; w < prevOutputs.size(); ++w)
                    sum += layers[i].weights[n][w] * prevOutputs[w];
                layers[i].outputs[n] = sigmoid(sum);
            }
        }
        return layers.back().outputs;
    }

    void backpropagate(const std::vector<float>& input, 
                      const std::vector<float>& target) {
        // Implement backpropagation...
    }
};
