#include <iostream>
#include "NeuralNetwork.h"
#include "Neuron.h"
#include "InputLayer.h"
#include "HiddenLayer.h"
#include "OutputLayer.h"
 
using namespace std;
 
NeuralNetwork::NeuralNetwork(vector<int>& architecture, vector<vector<double>>& trainingData, vector<vector<double>>& labelData, double lr, int nti)
{
    numberOfTrainingIterations = nti;
 
    Layer::setLearningRate(lr);
 
    Layer* currentLayer = new InputLayer(architecture[0]);
    firstLayer = currentLayer;
 
    for (int i = 1; i < architecture.size() - 1; i++)
    {
        Layer* nextLayer = new HiddenLayer(architecture[i - 1], architecture[i]);
        currentLayer->setNextLayer(nextLayer);
        currentLayer = nextLayer;
    }
 
    currentLayer->setNextLayer(new OutputLayer(architecture[architecture.size() - 2], architecture[architecture.size() - 1]));
 
    train(trainingData, labelData);
}
//--
NeuralNetwork::~NeuralNetwork()
{
    Layer* currentLayer = firstLayer;
 
    while (currentLayer != NULL)
    {
        Layer* deletePointer = currentLayer;
        currentLayer = currentLayer->getNextLayer();
        delete deletePointer;
    }
}
//--
void NeuralNetwork::train(vector<vector<double>>& trainingData, vector<vector<double>>& labelData)
{
    for (int iterNum = 0; iterNum < numberOfTrainingIterations; iterNum++)
    {
        for (int i = 0; i < trainingData.size(); i++)
        {
            firstLayer->feedForward(trainingData[i], labelData[i]);
        }
    }
}
//--
vector<double> NeuralNetwork::predict(vector<double>& input)
{
    vector<double> results;
    firstLayer->getNextLayer()->moveForward(input, results);
    return results;
}

//#include "NeuralNetwork.h"
//#include "Neuron.h"
//#include "InputLayer.h"
//#include "HiddenLayer.h"
//#include "OutputLayer.h"
//#include <iostream>
//
//using namespace std;
//
//NeuralNetwork::NeuralNetwork(vector<int> architecture, vector<vector<double>>& trainingData, vector<vector<double>>& labelData, double lr, int nti)
//{
//	numberOfTrainingIterations = nti;
//
//	Layer::setLearningRate(lr);
//	Neuron::setNumberOfErrorCalculations(0);
//
//	Layer* currentLayer = new InputLayer(architecture[0]);
//	firstLayer = currentLayer;
//
//	for (int i = 1; i < architecture.size() - 1; i++)
//	{
//		Layer* nextLayer = new HiddenLayer(architecture[i - 1], architecture[i]);
//		currentLayer->setNextLayer(nextLayer);
//		currentLayer = nextLayer;
//	}
//
//	currentLayer->setNextLayer(new OutputLayer(architecture[architecture.size() - 2], architecture[architecture.size() - 1]));
//
//	train(trainingData, labelData);
//}
////--
//NeuralNetwork::~NeuralNetwork()
//{
//	Layer* currentLayer = firstLayer;
//
//	while (currentLayer != NULL)
//	{
//		Layer* deletePointer = currentLayer;
//		currentLayer = currentLayer->getNextLayer();
//		delete deletePointer;
//	}
//}
////--
//void NeuralNetwork::train(vector<vector<double>>& trainingData, vector<vector<double>>& labelData)
//{
//	cout << "Iteration: ";
//
//	for (int iterNum = 0; iterNum < numberOfTrainingIterations; iterNum++)
//	{
//		for (int i = 0; i < trainingData.size(); i++)
//		{
//			firstLayer->feedForward(trainingData[i], labelData[i]);
//		}
//
//		cout << iterNum << " ";
//	}
//}
////--
//NeuralNetwork::NeuralNetwork(Layer* inputLayer, vector<vector<double>>& trainingData, vector<vector<double>>& labelData)
//{
//	firstLayer = inputLayer;
//
//	cout << "Creating a NN" << endl;
//
//	train(trainingData, labelData);
//
//	/*for (int iterNum = 0; iterNum < 1000; iterNum++)
//	{
//		for (int i = 0; i < trainingData.size(); i++)
//		{
//			inputLayer->feedForward(trainingData[i], labelData[i]);
//		}
//	}*/
//}
////--
//vector<double> NeuralNetwork::predict(vector<double>& input)
//{
//	vector<double> results;
//	firstLayer->getNextLayer()->moveForward(input, results);
//	return results;
//}
