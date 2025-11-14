#pragma once
#include "Layer.h"
#include "Neuron.h"
#include <vector>

using namespace std;

class HiddenLayer : public Layer
{
public:
	HiddenLayer(int numInputs, int numOutputs);
	HiddenLayer(vector<Neuron>& ns);
	
	void feedForward(vector<double>& inputs, vector<double>& outputs);
};

