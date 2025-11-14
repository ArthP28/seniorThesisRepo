#pragma once
#include "Layer.h"

class InputLayer : public Layer
{
public: 
	InputLayer(int numInputs);
	void feedForward(vector<double>& inputs, vector<double>& outputs);
	void backPropagate(vector<double>& errors);
private:
	int numberOfLayers;
};

