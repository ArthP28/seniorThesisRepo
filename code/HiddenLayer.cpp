#include "HiddenLayer.h"
#include <iostream>

using namespace std;

HiddenLayer::HiddenLayer(int numInputs, int numOutputs)
	: Layer(numInputs, numOutputs)
{
	//do nothing
}
//--
HiddenLayer::HiddenLayer(vector<Neuron>& ns)
	: Layer(ns)
{
	//do nothing
}
//--
void HiddenLayer::feedForward(vector<double>& inputs, vector<double>& outputs)
{
	//cout << "Hidden Layer: feedForward()" << endl;

	//perform the standard feed forward algorithm
	Layer::feedForward(inputs, outputs);

	//this layer's output will be the next layer's inputs
	vector<double> nextLayerInputs = getLayerOutputs();

	//hidden layers always have a next layer
	//feed the calculated neuron values into the next layer 
	getNextLayer()->feedForward(nextLayerInputs, outputs);
}
