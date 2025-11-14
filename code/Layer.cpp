#include "Layer.h"
#include <cstddef>


double Layer::learningRate = 0.5;

Layer::Layer()
{
	//set the next and previous layers to null
	nextLayer = NULL;
	previousLayer = NULL;
}
//--
Layer::Layer(int numInputs, int numOutputs)
{
	for (int i = 0; i < numOutputs; i++)
	{
		Neuron newNeuron(numInputs);
		neurons.push_back(newNeuron);
	}

	//set the next and previous layers to null
	nextLayer = NULL;
	previousLayer = NULL;
}
//--
Layer::Layer(vector<Neuron>& ns)
{
	//copy the neurons passed in to this ctor to the instance member
	neurons.insert(neurons.begin(), ns.begin(), ns.end());

	//set the next and previous layers to null
	nextLayer = NULL;
	previousLayer = NULL;
}
//--
void Layer::feedForward(vector<double>& inputs, vector<double>& outputs)
{
	//stores the outputs of each neuron in this layer
	vector<double> neuronOutputs;

	//store the inputs to this layer
	setLayerInputs(inputs);

	//for each of this hidden layer's neurons
	for (int neuronIndex = 0; neuronIndex < neurons.size(); neuronIndex++)
	{
		//activate the neuron with the inputs 
		neurons[neuronIndex].activate(inputs);

		//store the activation value as inputs into the next layer
		neuronOutputs.push_back(neurons[neuronIndex].getActivationValue());
	}

	//store each neuron in this layer's output
	setLayerOutputs(neuronOutputs);
}
//--
void Layer::moveForward(vector<double>& inputs, vector<double>& predictedOutputs)
{
	//stores the outputs of each neuron in this layer
	vector<double> neuronOutputs;

	//for each of this hidden layer's neurons
	for (int neuronIndex = 0; neuronIndex < neurons.size(); neuronIndex++)
	{
		//activate the neuron with the inputs 
		neurons[neuronIndex].activate(inputs);

		//store the activation value as inputs into the next layer
		neuronOutputs.push_back(neurons[neuronIndex].getActivationValue());
	}

	//if there is a next layer
	if (getNextLayer() != NULL)
	{
		//pass the outputs to the next layer
		getNextLayer()->moveForward(neuronOutputs, predictedOutputs);
	}
	else //this is the last layer
	{
		//store this last layer's outputs in the reference parameter as a return value
		predictedOutputs = neuronOutputs;
	}
}
//--
void Layer::backPropagate(vector<double>& errors)
{
	//this is used to calculate the errors to pass back to the previous layer
	//there will be an error value passed back for every input into this layer
	//each neuron in this layer will add a little to the overall error for each input
	
	//create a vector that will hold the error value for each input and zero it out
	vector<double> newErrors(getLayerInputs().size());
	for (int i = 0; i < getLayerInputs().size(); i++)
	{
		newErrors[i] = 0.0;
	}

	//get the inputs to this layer
	vector<double> inputs = getLayerInputs();

	//add a 1.0 to the beginning to multiply by the bias weight
	inputs.insert(inputs.begin(), 1.0);

	//go through all of the neurons in this hidden layer
	for (int neuronIndex = 0; neuronIndex < neurons.size(); neuronIndex++)
	{
		//use the previous layer's errors to calculate the error for the neurons in this layer
		neurons[neuronIndex].calculateError(errors[neuronIndex]);

		//get the weights for the current neuron
		vector<double> weights = neurons[neuronIndex].getWeights();

		//calculate the errors to send back to the previous layer
		//go through all of the weights (except the bias weight)
		for (int weightIndex = 1; weightIndex < weights.size(); weightIndex++)
		{
			//calculate the new errors to be passed into the previous layer
			//get this neuron's error and multiply it by each weight
			//each neuron will contribute to each error value (they are added to a running sum for each weight in all of the neurons in this layer)
			newErrors[weightIndex - 1] += (neurons[neuronIndex].getError() * weights[weightIndex]);
		}

		//update the weights for the current neuron
		for (int weightIndex = 0; weightIndex < weights.size(); weightIndex++)
		{
			weights[weightIndex] = weights[weightIndex] + (getLearningRate() * neurons[neuronIndex].getError() * inputs[weightIndex]);
		}

		neurons[neuronIndex].setWeights(weights);
	}

	//send all of the errors back to the previous layer
	getPreviousLayer()->backPropagate(newErrors);

}
//--
void Layer::setLayerInputs(vector<double>& inputs)
{
	//clear out any previous inputs
	layerInputs.clear();

	//copy the new inputs 
	layerInputs.insert(layerInputs.end(), inputs.begin(), inputs.end());
}
//--
vector<double> Layer::getLayerInputs()
{
	return layerInputs;
}
//--
void Layer::setLayerOutputs(vector<double>& outputs)
{
	//clear out any previous outputs
	layerOutputs.clear();

	//copy the new outputs 
	layerOutputs.insert(layerOutputs.end(), outputs.begin(), outputs.end());
}
//--
vector<double> Layer::getLayerOutputs()
{
	return layerOutputs;
}
//--
void Layer::setNextLayer(Layer* nl)
{
	nextLayer = nl;
	nextLayer->setPreviousLayer(this);
}
//--
void Layer::setPreviousLayer(Layer* pl)
{
	previousLayer = pl;
}
//--
Layer* Layer::getNextLayer()
{
	return nextLayer;
}
//--
Layer* Layer::getPreviousLayer()
{
	return previousLayer;
}
//--
double Layer::getLearningRate()
{
	return learningRate;
}
//--
void Layer::setLearningRate(double lr)
{
	learningRate = lr;
}
