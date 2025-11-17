#pragma once
#include <iomanip>
#include <iostream>
#include "Player.h"
#include <vector>
#include "NNDecisionTree.h"
#include "NeuralNetwork.h"

using namespace std;

// Note: Consider using an unordered-set: Only stores unique states
// Use valid board state as key, vector of actions is the value
// Write a for loop to calculate the largest Q-Value

class NeuralNetworkAI : public Player{
    public:
        NeuralNetworkAI(string _name, char _symbol);
        NeuralNetworkAI(char _symbol);
        ~NeuralNetworkAI();
        void dropChecker() override;
        void SetPlayersBoard(Board* _board) override;
        void SetPlayersBoard(Board* _board, int numGames);
        void PrepareData() { ConvertData(); Shuffle(); Partition(0.75); };
    private:
        NeuralNetwork* nn;
        vector<int> architecture;
        vector<int> hiddenLayers = {3, 3};

        vector<pair<string, string>> _labelledNNData;
        vector<pair<vector<double>, vector<double>>> _vectorizedNNData;
        vector<vector<double>> _trainingFeatures;
        vector<vector<double>> _trainingLabels;
        vector<vector<double>> _testingFeatures;
        vector<vector<double>> _testingLabels;

        // // Helper Functions
        void Shuffle();
        void Partition(double threshold);
        void ConvertData();
};


NeuralNetworkAI::NeuralNetworkAI(string _name, char _symbol) : Player(_name, _symbol){
    Player::_playerName = _name;
}

NeuralNetworkAI::NeuralNetworkAI(char _symbol) : Player(_symbol){
    Player::_playerName = "Ares";
}

NeuralNetworkAI::~NeuralNetworkAI(){
    delete nn;
    nn = NULL;
}

void NeuralNetworkAI::SetPlayersBoard(Board* _board){
    Player::SetPlayersBoard(_board);
}

void NeuralNetworkAI::dropChecker(){

}

void NeuralNetworkAI::SetPlayersBoard(Board* _board, int numGames){
    Player::SetPlayersBoard(_board);

    NNDecisionTree _tree(_board->GetHeight(), _board->GetWidth());
    _tree.buildFullTree(numGames);
    unordered_map<string, string> _allMoves = _tree.getAllMoves();
    for(auto& move : _allMoves){
        _labelledNNData.push_back(move);
    }

    int inputNeurons = _board->GetHeight() * _board->GetWidth();
    int outputNeurons = _board->GetWidth();

    architecture.push_back(inputNeurons);
    for(int layerNeurons : hiddenLayers){
        architecture.push_back(layerNeurons);
    }
    architecture.push_back(outputNeurons);
}

void NeuralNetworkAI::Shuffle(){
    // Use Fisher-Yates shuffle algorithm to be as efficient as possible
    for(int i = _vectorizedNNData.size() - 1; i > 1; i--){
        int rand_i = (rand() % i) + 1;
        auto temp = _vectorizedNNData.at(rand_i);
        _vectorizedNNData.at(rand_i) = _vectorizedNNData.at(i);
        _vectorizedNNData.at(i) = temp;
    }
}

void NeuralNetworkAI::Partition(double threshold){
    if(threshold > 1.0){ threshold = 1.0; };

    int trainingIndex = (_vectorizedNNData.size() - 1) * threshold;
    for(int i = 0; i < trainingIndex; i++){
        _trainingFeatures.push_back(_vectorizedNNData.at(i).first);
        _trainingLabels.push_back(_vectorizedNNData.at(i).second);
    }

    for(int i = trainingIndex; i < _vectorizedNNData.size(); i++){
        _testingFeatures.push_back(_vectorizedNNData.at(i).first);
        _testingLabels.push_back(_vectorizedNNData.at(i).second);
    }
}

void NeuralNetworkAI::ConvertData(){
    for(auto& data : _labelledNNData){
        string _boardString = data.first;
        string _label = data.second;

        // Feature Data
        vector<double> featureVector;
        int numCheckersInCol = 0;
        for(char space : _boardString){
            if(space == 'R'){
                featureVector.push_back(-1.0);
                numCheckersInCol++;
            } else if (space == 'B'){
                featureVector.push_back(1.0);
                numCheckersInCol++;
            } else if (space == '|'){
                int r = Player::GetBoard()->GetHeight() - numCheckersInCol;
                for(int i = 0; i < r; i++){
                    featureVector.push_back(0.0);
                }
                numCheckersInCol = 0;
            }
        }

        // Labelled Data
        vector<double> labelFeature(Player::GetBoard()->GetWidth());
        int labelIndex = stoi(_label);
        labelFeature.at(labelIndex) = 1.0;

        pair<vector<double>, vector<double>> _vectorizedPair(featureVector, labelFeature);

        _vectorizedNNData.push_back(_vectorizedPair);
    }
}