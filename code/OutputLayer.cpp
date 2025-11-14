#include "OutputLayer.h"
#include <iostream>

using namespace std;

OutputLayer::OutputLayer(int numInputs, int numOutputs)
	: Layer(numInputs, numOutputs)
{
	//do nothing
}
//--
OutputLayer::OutputLayer(vector<Neuron>& ns)
	: Layer(ns)
{
	//do nothing
}
//--
void OutputLayer::feedForward(vector<double>& inputs, vector<double>& outputs)
{
	//cout << "Output Layer: feedForward()" << endl;

	//perform a standard feed forward
	Layer::feedForward(inputs, outputs);

	//get the outputs of feed forward
	vector<double> neuronOutputs = getLayerOutputs();

	//the errors for the output layer are the differences between 
	//the expected values and the neuron values 
	vector<double> errors;

	//go through each neuron's output in the layer
	for (int i = 0; i < neuronOutputs.size(); i++)
	{
		//take the difference from the expected output and the layer's outputs
		errors.push_back(outputs[i] - neuronOutputs[i]);
	}

	//now propagate the errors back into the previous layers
	backPropagate(errors);
}
