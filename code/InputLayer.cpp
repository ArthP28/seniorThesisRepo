#include "InputLayer.h"
#include <iostream>

using namespace std;

//--
InputLayer::InputLayer(int numInputs)
	:Layer()
{
	numberOfLayers = numInputs;
	//do nothing more than the Layer's default ctor
}
//--
void InputLayer::feedForward(vector<double>& inputs, vector<double>& outputs)
{
	/*cout << "Input Layer: feedForward()" << endl;
	for (int i = 0; i < inputs.size(); i++)
	{
		cout << inputs[i] << " ";
	}
	cout << endl <<endl;
	*/

	if (numberOfLayers == inputs.size())
	{
		//store the inputs
		setLayerInputs(inputs);

		//input layers have no effect on the inputs, store them as the output too
		setLayerOutputs(inputs);

		//input layers pass the inputs on to the next layers
		getNextLayer()->feedForward(inputs, outputs);
	}
	else
	{
		string ex = "Incorrect number of input layers";
		throw ex;
	}
}
//--
void InputLayer::backPropagate(vector<double>& errors)
{
	//do nothing for back prop on input layer
}