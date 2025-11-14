#pragma once
#include "Layer.h"
#include "Neuron.h"
#include <vector>

using namespace std;

class Layer
{
public:
	Layer();
	Layer(int numInputs, int numOutputs);
	Layer(vector<Neuron>& ns);

	void setNextLayer(Layer* nl);
	Layer* getNextLayer();
	Layer* getPreviousLayer();

	void setLayerInputs(vector<double>& inputs);
	vector<double> getLayerInputs();
	void setLayerOutputs(vector<double>& outputs);
	vector<double> getLayerOutputs(); 
	
	virtual void feedForward(vector<double>& inputs, vector<double>& outputs);
	void moveForward(vector<double>& inputs, vector<double>& predictedOutputs);

	static double getLearningRate();
	static void setLearningRate(double lr);

protected:
	vector<Neuron> neurons;
	vector<double> layerInputs;
	vector<double> layerOutputs;

	virtual void backPropagate(vector<double>& errors);

private:	
	Layer* nextLayer;
	Layer* previousLayer;

	static double learningRate;

	void setPreviousLayer(Layer* pl);
};

