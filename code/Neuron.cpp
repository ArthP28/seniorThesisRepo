#include "Neuron.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int Neuron::numberOfErrorCalculations = 0;

Neuron::Neuron(int numOfInputs)
{
	//initial value for the bias and all of the inputs 
	for (int i = 0; i < numOfInputs + 1; i++)
	{
		//random value between -1 and +1
		double randWeight = getRandomWeight();

		//add the weight to the neuron
		weights.push_back(randWeight);
	}
}
//--
Neuron::Neuron(vector<double>& initialWeights, double lr)
{
	setWeights(initialWeights);
}
//--
void Neuron::activate(vector<double>& in)
{
	//clear out the inputs from any previous activation
	vector<double> inputs; 
	
	//add the bias input of 1
	inputs.push_back(1.0);

	//store the passed in inputs
	inputs.insert(inputs.end(), in.begin(), in.end());

	//holds the product of inputs and weights
	vector<double> resultOfMultiplying;
	multiplyVectors(inputs, weights, resultOfMultiplying);
	
	//the sum of all the inputs times the weights
	double sumOfProducts = sumVector(resultOfMultiplying);
	
	//apply the sigmoid function to the sum of products and store it in the instance variable
	activationValue = sigmoid(sumOfProducts);

	//DEBUG print out the activation value
	//cout << activationValue << endl;
}
//--
double Neuron::getActivationValue()
{
	return activationValue;
}
//--
vector<double> Neuron::getWeights()
{
	return weights;
}
//--
void Neuron::setWeights(vector<double>& newWeights)
{
	//clear any old weights
	weights.clear();

	//copy all of the passed in weights to the private data member
	weights.insert(weights.begin(), newWeights.begin(), newWeights.end());
}
//--
void Neuron::calculateError(double val)
{
	//
	error = val * sigmoidDerivative();
	
	numberOfErrorCalculations++;
}
//--
double Neuron::getError()
{
	return error;
}
//--
void Neuron::multiplyVectors(vector<double>& vec1, vector<double>& vec2, vector<double>& results)
{
	//verify that the two vectors are the same size and the result vector is empty
	if (vec1.size() == vec2.size() && results.size() == 0)
	{
		//go through each element in the two vectors
		for (int i = 0; i < vec1.size(); i++)
		{
			//DEBUG print out the values being multiplied
			/*cout << "("<<vec1[i] << "*" << vec2[i] <<")";
			if (i < vec1.size() - 1)
			{
				cout << " + ";
			}
			else
			{
				cout << " = ";
			}*/

			//store the product of the corresponding values in the vectors
			results.push_back(vec1[i] * vec2[i]);
		}
	}
	else //vectors are different sizes of the result vector is not empty
	{
		string ex = "multiplyVectors(): vectors not the same size OR results not empty";
		cout << ex << endl;
		throw ex;
	}
}
//--
double Neuron::sumVector(vector<double>& vec)
{
	double sum = 0.0;

	for (int i = 0; i < vec.size(); i++)
	{
		sum += vec[i];
	}

	return sum;
}
//--
double Neuron::sigmoid(double value)
{
	return 1.0 / (1.0 + exp(-value));
}
//--
double Neuron::sigmoidDerivative()
{
	double value = getActivationValue();
	return value * (1.0 - value);
}
//--
double Neuron::getRandomWeight(/*double lowEnd, double highEnd*/)
{
	double randDouble = double(rand()) / double(RAND_MAX);
	return -1.0 + (2 * randDouble);

	//double difference = highEnd - lowEnd;
	//return lowEnd + double(rand() % int(difference) * 10000) / 10000.0;
}
//--
int Neuron::getNumberOfErrorCalculations()
{
	return numberOfErrorCalculations;
}
//--
void Neuron::setNumberOfErrorCalculations(int num)
{
	numberOfErrorCalculations = num;
}