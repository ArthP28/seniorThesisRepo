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
        void Test(); // Examines the accuracy of the NN model
        private:
        NeuralNetwork* decide_nn;
        NeuralNetwork* block_nn;
        NeuralNetwork* move_nn;
        vector<int> hiddenLayers = {5, 3}; // Optimal Values for 7x6: 20, 15
        int moveOrBlock = 2;
        double lr = 0.7; // Optimal LR for 7x6: 0.6
        double numTrainingCycles = 100; // Optimal epochs for 7x6: 5000
        
        vector<pair<string, string>> _labelledMoveData;
        vector<pair<string, string>> _labelledBlockingData;
        vector<pair<string, string>> _labelledBehaviorData;
        vector<pair<vector<double>, vector<double>>> _vectorizedMoveData;
        vector<pair<vector<double>, vector<double>>> _vectorizedBlockingData;
        vector<pair<vector<double>, vector<double>>> _vectorizedBehaviorData;
        vector<vector<double>> _trainingFeatures;
        vector<vector<double>> _trainingLabels;
        pair<vector<vector<double>>, vector<vector<double>>> _trainingMovementData; // First = Features, Second = Labels
        pair<vector<vector<double>>, vector<vector<double>>> _testingMovementData; // First = Features, Second = Labels
        vector<vector<double>> _testingFeatures;
        vector<vector<double>> _testingLabels;
        
        // // Helper Functions
        void PrepareData(vector<pair<string, string>> _labelledData, pair<vector<vector<double>>, vector<vector<double>>>& _trainingData, pair<vector<vector<double>>, vector<vector<double>>>& _testingData);
        void Shuffle(vector<pair<vector<double>, vector<double>>>& _vectorizedData);
        void Partition(double threshold,
            vector<pair<vector<double>, vector<double>>>& _vectorizedData,
            pair<vector<vector<double>>, vector<vector<double>>>& _trainingData,
            pair<vector<vector<double>>, vector<vector<double>>>& _testingData);
        vector<pair<vector<double>, vector<double>>> ConvertData(vector<pair<string, string>> _labelledData);
        vector<double> BoardToFeatureVector(string b_string);
        vector<double> LabelToVector(string b_label);
        int SelectMove(vector<double> result);
};


NeuralNetworkAI::NeuralNetworkAI(string _name, char _symbol) : Player(_name, _symbol){
    Player::_playerName = _name;
}

NeuralNetworkAI::NeuralNetworkAI(char _symbol) : Player(_symbol){
    Player::_playerName = "Ares";
}

NeuralNetworkAI::~NeuralNetworkAI(){
    delete move_nn;
    move_nn = NULL;
    delete block_nn;
    block_nn = NULL;
    delete decide_nn;
    decide_nn = NULL;
}

void NeuralNetworkAI::SetPlayersBoard(Board* _board){
    Player::SetPlayersBoard(_board);
}

void NeuralNetworkAI::dropChecker(){
    vector<double> CurrentBoardFeatures = BoardToFeatureVector(Player::GetBoard()->boardToString());
    vector<double> results = move_nn->predict(CurrentBoardFeatures);
    int moveIndex = SelectMove(results);
    while(Player::GetBoard()->isFull(moveIndex)){ // Stuck in infinite loop, prediction results do not change
        results = move_nn->predict(CurrentBoardFeatures);
        moveIndex = SelectMove(results);
    }
    cout << GetName() << " drops a checker into column " << moveIndex << "." << endl << endl; // This message primarily conveys that the action went through
    GetBoard()->placeChecker(moveIndex, GetSymbol());
}

void NeuralNetworkAI::SetPlayersBoard(Board* _board, int numGames){
    Player::SetPlayersBoard(_board);

    NNDecisionTree _tree(_board->GetWidth(), _board->GetHeight());
    _tree.buildFullTree(numGames);
    unordered_map<string, string> _allMoves = _tree.getAllMoves();
    unordered_map<string, string> _allBlockingMoves = _tree.getAllBlockingMoves();
    unordered_map<string, string> _allBehaviors = _tree.getAllBehaviors();
    for(auto& move : _allMoves){
        _labelledMoveData.push_back(move);
    }
    for(auto& block : _allBlockingMoves){
        _labelledBlockingData.push_back(block);
    }
    for(auto& behavior : _allBehaviors){
        _labelledBehaviorData.push_back(behavior);
    }

    int inputNeurons = _board->GetHeight() * _board->GetWidth();
    int movementOutput = _board->GetWidth();
    int behaviorOutput = 2;

    vector<int> movementNNarchitecture;
    vector<int> blockNNarchitecture;
    vector<int> behaviorNNarchitecture;

    movementNNarchitecture.push_back(inputNeurons);
    for(int layerNeurons : hiddenLayers){
        movementNNarchitecture.push_back(layerNeurons);
    }
    movementNNarchitecture.push_back(movementOutput);

    PrepareData(_labelledMoveData, _trainingMovementData, _testingMovementData);

    move_nn = new NeuralNetwork(movementNNarchitecture, _trainingMovementData.first, _trainingMovementData.second, lr, numTrainingCycles);
}

void NeuralNetworkAI::Test(){
    int numMovesCorrect = 0;
    for(int i = 0; i < _testingMovementData.first.size(); i++){
        vector<double> result = move_nn->predict(_testingMovementData.first.at(i));
        int bestMove = SelectMove(result);
        
        for(int j = 0; j < _testingMovementData.second.size(); j++){
            if(bestMove == j && _testingMovementData.second.at(i).at(j) == 1.0) // Check if position of Max corresponds with j and the neuron of value j is illuminated
            { 
                numMovesCorrect++;
                break;
            } 
        }
    }

    double correctRatio = numMovesCorrect/(double)_testingMovementData.first.size();

    cout << "Number of correct predictions: " << numMovesCorrect << "/" << _testingMovementData.first.size() << " (" << correctRatio << ")" << endl;
}

void NeuralNetworkAI::PrepareData(vector<pair<string, string>> _labelledData, pair<vector<vector<double>>, vector<vector<double>>>& _trainingData, pair<vector<vector<double>>, vector<vector<double>>>& _testingData) {
    auto _v = ConvertData(_labelledData);
    Shuffle(_v);
    Partition(0.75, _v, _trainingData, _testingData);
};

void NeuralNetworkAI::Shuffle(vector<pair<vector<double>, vector<double>>>& _vectorizedData){
    // Use Fisher-Yates shuffle algorithm to be as efficient as possible
    for(int i = _vectorizedData.size() - 1; i > 1; i--){
        int rand_i = (rand() % i) + 1;
        auto temp = _vectorizedData.at(rand_i);
        _vectorizedData.at(rand_i) = _vectorizedData.at(i);
        _vectorizedData.at(i) = temp;
    }
}

void NeuralNetworkAI::Partition(double threshold,
    vector<pair<vector<double>, vector<double>>>& _vectorizedData,
    pair<vector<vector<double>>, vector<vector<double>>>& _trainingData,
    pair<vector<vector<double>>, vector<vector<double>>>& _testingData){

    vector<vector<double>> _trainingFeatures;
    vector<vector<double>> _trainingLabels;

    vector<vector<double>> _testingFeatures;
    vector<vector<double>> _testingLabels;

    if(threshold > 1.0){ threshold = 1.0; };

    int trainingIndex = (_vectorizedData.size() - 1) * threshold;
    for(int i = 0; i < trainingIndex; i++){
        _trainingFeatures.push_back(_vectorizedData.at(i).first);
        _trainingLabels.push_back(_vectorizedData.at(i).second);
    }

    _trainingData = make_pair(_trainingFeatures, _trainingLabels);

    for(int i = trainingIndex; i < _vectorizedData.size(); i++){
        _testingFeatures.push_back(_vectorizedData.at(i).first);
        _testingLabels.push_back(_vectorizedData.at(i).second);
    }

    _testingData = make_pair(_testingFeatures, _testingLabels);
}

vector<pair<vector<double>, vector<double>>> NeuralNetworkAI::ConvertData(vector<pair<string, string>> _labelledData){
    vector<pair<vector<double>, vector<double>>> _vectorizedData;
    for(auto& data : _labelledData){
        string _boardString = data.first;
        string _label = data.second;

        // Feature Data
        vector<double> featureVector = BoardToFeatureVector(_boardString);

        // Labelled Data
        vector<double> labelVector = LabelToVector(_label);

        pair<vector<double>, vector<double>> _vectorizedPair(featureVector, labelVector);

        _vectorizedData.push_back(_vectorizedPair);
    }
    return _vectorizedData;
}

vector<double> NeuralNetworkAI::BoardToFeatureVector(string b_string){
    vector<double> featureVector;
    int numCheckersInCol = 0;
    for(char space : b_string){
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
    return featureVector;
}

vector<double> NeuralNetworkAI::LabelToVector(string b_label){
    vector<double> labelFeature(Player::GetBoard()->GetWidth());
    int labelIndex = stoi(b_label);
    labelFeature.at(labelIndex) = 1.0;
    return labelFeature;
}

int NeuralNetworkAI::SelectMove(vector<double> result){
    double max = result[0]; 
    int posOfMax = 0; 
    for(int k = 1;k < result.size();k++) 
    { 
        if(!GetBoard()->isFull(k)){
            if(result[k] > max) 
            { 
                max = result[k]; 
                posOfMax = k; 
            }
        }
    } 

    return posOfMax;
}