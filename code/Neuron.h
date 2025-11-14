#pragma once
#include <vector>

using namespace std;

class Neuron
{
public:
	Neuron(int numOfInputs);
	Neuron(vector<double>& initialWeights, double lr);

	void activate(vector<double>& in);
	double getActivationValue();

	vector<double> getWeights();
	void setWeights(vector<double>& newWeights);
	
	void calculateError(double val);
	double getError();

	static int getNumberOfErrorCalculations();
	static void setNumberOfErrorCalculations(int num);

private:
	vector<double> weights;
	
	double activationValue;
	double error;

	static int numberOfErrorCalculations;

	double getRandomWeight(/*double lowEnd, double highEnd*/);
	void multiplyVectors(vector<double>& vec1, vector<double>& vec2, vector<double>& results);
	double sumVector(vector<double>& vec);
	double sigmoid(double value);
	double sigmoidDerivative();
};

