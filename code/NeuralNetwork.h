#pragma once
#include <vector>
#include "Layer.h"
 
using namespace std;
 
class NeuralNetwork
{
public:
    NeuralNetwork(vector<int>& architecture, vector<vector<double>>& trainingData, vector<vector<double>>& labelData, double lr, int nti);
    ~NeuralNetwork();
    vector<double> predict(vector<double>& input);
 
private:
    Layer* firstLayer;
    double learningRate;
    int numberOfTrainingIterations;
 
    void train(vector<vector<double>>& trainingData, vector<vector<double>>& labelData);
};

//#pragma once
//#include <vector>
//#include "Layer.h"
//
//using namespace std;
//
//class NeuralNetwork
//{
//public:
//	NeuralNetwork(Layer* inputLayer, vector<vector<double>>& trainingData, vector<vector<double>>& labelData);
//	NeuralNetwork(vector<int> architecture, vector<vector<double>>& trainingData, vector<vector<double>>& labelData, double lr, int nti);
//	~NeuralNetwork();
//	vector<double> predict(vector<double>& input);
//
//private:
//	Layer* firstLayer;
//	double learningRate;
//	int numberOfTrainingIterations;
//
//	void train(vector<vector<double>>& trainingData, vector<vector<double>>& labelData);
//};
//
////forward prop
////Input Layer:
//// - forward all inputs onto the next layer
////Hidden Layer:
//// - go through all of the neurons in the layer
//// - pass in the layer inputs to each one with a call to activate
//// - collect the outputs of each neuron after it has been activated in a vector
//// - pass the outputs from the previous step to the next layer in a call to forward prop
////Output Layer:
//// - same as hidden layer except at the end call back prop
//
////backward propagation
////Input Layer
//// - ignore
////Hidden Layer:
////Output Layer:
//// - go through every neuron in the layer
//// - calculate the error each neuron
//// - the error is the difference from the expected data from the label and the output from the layer neuron times the sigmoid derivative
//// - update the weights of the current neuron
//// wi = wi + (learning-rate * error * activation value)
//// - send the layer's neuron's error
