#pragma once
#include "Layer.h"
#include "Neuron.h"
#include <vector>

using namespace std;

class OutputLayer : public Layer
{
public:
	OutputLayer(int numInputs, int numOutputs);
	OutputLayer(vector<Neuron>& ns);
	
	void feedForward(vector<double>& inputs, vector<double>& outputs);
};

