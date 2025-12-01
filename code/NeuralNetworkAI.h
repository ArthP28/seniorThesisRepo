#pragma once
#include <iomanip>
#include <iostream>
#include "Player.h"
#include <vector>
#include <fstream>
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
        void SetPlayersBoard(Board* _board, int games);
        void Test(); // Examines the accuracy of the NN model
    private:
        NeuralNetwork* decide_nn;
        NeuralNetwork* block_nn;
        NeuralNetwork* move_nn;
        vector<int> hiddenLayers = {5, 3}; // Optimal Values for 7x6: 20, 15
        int moveOrBlock = 2;
        double lr = 0.7; // Optimal LR for 7x6: 0.6
        double numTrainingCycles = 100; // Optimal epochs for 7x6: 5000
        int numGames;
        string movement_data_path = "NeuralNetworkData/NNMovementData.txt";
        string block_data_path = "NeuralNetworkData/NNBlockMovementData.txt";
        string decision_data_path = "NeuralNetworkData/NNDecisionData.txt";
        
        vector<pair<string, string>> _labelledMoveData;
        vector<pair<string, string>> _labelledBlockingData;
        vector<pair<string, string>> _labelledBehaviorData;
        pair<vector<vector<double>>, vector<vector<double>>> _trainingMovementData; // First = Features, Second = Labels
        pair<vector<vector<double>>, vector<vector<double>>> _testingMovementData;
        pair<vector<vector<double>>, vector<vector<double>>> _trainingBlockingData;
        pair<vector<vector<double>>, vector<vector<double>>> _testingBlockingData;
        pair<vector<vector<double>>, vector<vector<double>>> _trainingBehaviorData;
        pair<vector<vector<double>>, vector<vector<double>>> _testingBehaviorData;
        
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
        int MakeChoice(vector<double> result);
        bool FileExists(string fileName);
        bool CheckDimensionsFromFile(string fileName);
        void CreateNewData();
        vector<pair<string, string>> ReadDataFromFile(string fileName);
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
    vector<double> decision = decide_nn->predict(CurrentBoardFeatures);
    int decisionIndex = MakeChoice(decision);
    int moveIndex;
    if(decisionIndex == 0){ // Place Checker
        cout << GetName() << " chooses to move!" << endl;
        vector<double> resultsOfMove = move_nn->predict(CurrentBoardFeatures);
        moveIndex = SelectMove(resultsOfMove);
        while(Player::GetBoard()->isFull(moveIndex)){ // Stuck in infinite loop, prediction results do not change
            resultsOfMove = move_nn->predict(CurrentBoardFeatures);
            moveIndex = SelectMove(resultsOfMove);
        }
    } else if (decisionIndex == 1){ // Block opponent
        cout << GetName() << " chooses to BLOCK!" << endl;
        vector<double> resultsOfBlock = block_nn->predict(CurrentBoardFeatures);
        moveIndex = SelectMove(resultsOfBlock);
        while(Player::GetBoard()->isFull(moveIndex)){ // Stuck in infinite loop, prediction results do not change
            resultsOfBlock = move_nn->predict(CurrentBoardFeatures);
            moveIndex = SelectMove(resultsOfBlock);
        }
    }
    // vector<double> results = move_nn->predict(CurrentBoardFeatures);
    // int moveIndex = SelectMove(results);
    // while(Player::GetBoard()->isFull(moveIndex)){ // Stuck in infinite loop, prediction results do not change
    //     results = move_nn->predict(CurrentBoardFeatures);
    //     moveIndex = SelectMove(results);
    // }
    cout << GetName() << " drops a checker into column " << moveIndex << "." << endl << endl; // This message primarily conveys that the action went through
    GetBoard()->placeChecker(moveIndex, GetSymbol());
}

void NeuralNetworkAI::SetPlayersBoard(Board* _board, int games){
    Player::SetPlayersBoard(_board);
    numGames = games;
    // If any of these special txt files do not exist in the program, make them, create the tree, and store its data into the txt files. Overwriting may occur.
    // Else if they all exist, check if the dimensions of the board in the existing data files match the board dimensions within the parameter
    // If any of them do not match, then the data needs to be overwritten; use the same process in this for loop again.
    if((!FileExists(movement_data_path) || !FileExists(block_data_path) || !FileExists(decision_data_path))){
        CreateNewData();
    } else if (!CheckDimensionsFromFile(movement_data_path) || !CheckDimensionsFromFile(block_data_path) || !CheckDimensionsFromFile(decision_data_path)){
        CreateNewData();
    } else {
        _labelledMoveData = ReadDataFromFile(movement_data_path);
        _labelledBlockingData = ReadDataFromFile(block_data_path);
        _labelledBehaviorData = ReadDataFromFile(decision_data_path);
    }

    cout << "Training Algorithm..." << endl;

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

    blockNNarchitecture.push_back(inputNeurons);
    for(int layerNeurons : hiddenLayers){
        blockNNarchitecture.push_back(layerNeurons);
    }
    blockNNarchitecture.push_back(movementOutput);
    PrepareData(_labelledBlockingData, _trainingBlockingData, _testingBlockingData);

    behaviorNNarchitecture.push_back(inputNeurons);
    for(int layerNeurons : hiddenLayers){
        behaviorNNarchitecture.push_back(layerNeurons);
    }
    behaviorNNarchitecture.push_back(behaviorOutput);
    PrepareData(_labelledBehaviorData, _trainingBehaviorData, _testingBehaviorData);

    if(move_nn != NULL){
        delete move_nn;
        move_nn = NULL;
    }

    if(block_nn != NULL){
        delete block_nn;
        block_nn = NULL;
    }

    if(decide_nn != NULL){
        delete decide_nn;
        decide_nn = NULL;
    }

    move_nn = new NeuralNetwork(movementNNarchitecture, _trainingMovementData.first, _trainingMovementData.second, lr, numTrainingCycles);
    block_nn = new NeuralNetwork(blockNNarchitecture, _trainingBlockingData.first, _trainingBlockingData.second, lr, numTrainingCycles);
    decide_nn = new NeuralNetwork(behaviorNNarchitecture, _trainingBehaviorData.first, _trainingBehaviorData.second, lr, numTrainingCycles);
}

void NeuralNetworkAI::Test(){
    int numMovesCorrect = 0;
    int numBlocksCorrect = 0;
    int numDecisionsCorrect = 0;
    for(int i = 0; i < _testingMovementData.first.size(); i++){
        vector<double> result = move_nn->predict(_testingMovementData.first.at(i));
        int bestMove = SelectMove(result);
        
        for(int j = 0; j < _testingMovementData.second.at(i).size(); j++){
            if(bestMove == j && _testingMovementData.second.at(i).at(j) == 1.0) // Check if position of Max corresponds with j and the neuron of value j is illuminated
            { 
                numMovesCorrect++;
                break;
            } 
        }
    }
    for(int i = 0; i < _testingBlockingData.first.size(); i++){
        vector<double> result = block_nn->predict(_testingBlockingData.first.at(i));
        int bestMove = SelectMove(result);
        
        for(int j = 0; j < _testingBlockingData.second.at(i).size(); j++){
            if(bestMove == j && _testingBlockingData.second.at(i).at(j) == 1.0) // Check if position of Max corresponds with j and the neuron of value j is illuminated
            { 
                numBlocksCorrect++;
                break;
            } 
        }
    }
    for(int i = 0; i < _testingBehaviorData.first.size(); i++){
        vector<double> result = decide_nn->predict(_testingBehaviorData.first.at(i));
        int bestMove = MakeChoice(result);
        
        for(int j = 0; j < _testingBehaviorData.second.at(i).size(); j++){
            if(bestMove == j && _testingBehaviorData.second.at(i).at(j) == 1.0) // Check if position of Max corresponds with j and the neuron of value j is illuminated
            { 
                numDecisionsCorrect++;
                break;
            } 
        }
    }

    double correctMovementRatio = numMovesCorrect/(double)_testingMovementData.first.size();
    double correctBlocksRatio = numBlocksCorrect/(double)_testingBlockingData.first.size();
    double correctDecisionsRatio = numDecisionsCorrect/(double)_testingBehaviorData.first.size();

    cout << "Number of correct movement predictions: " << numMovesCorrect << "/" << _testingMovementData.first.size() << " (" << correctMovementRatio << ")" << endl;
    cout << "Number of correct blocking predictions: " << numBlocksCorrect << "/" << _testingBlockingData.first.size() << " (" << correctBlocksRatio << ")" << endl;
    cout << "Number of correct decision predictions: " << numDecisionsCorrect << "/" << _testingBehaviorData.first.size() << " (" << correctDecisionsRatio << ")" << endl;
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
    if(b_label == "BLOCK"){
        return { 0, 1 };
    } else if(b_label == "MOVE"){
        return { 1, 0 };
    }
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

int NeuralNetworkAI::MakeChoice(vector<double> result){
    int posOfMax = 0; 
    if(result[0] < result[1]){
        posOfMax = 1;
    }
    return posOfMax;
}

bool NeuralNetworkAI::FileExists(string fileName){
    ifstream inData;
    inData.open(fileName);
    if(inData.fail()){
        inData.close();
        return false;
    } else if (inData.good()){
        string data; getline(inData, data);
        if(data.empty()){
            inData.close();
            return false;
        } else if(data.at(0) < '0' || data.at(0) > '9'){
            inData.close();
            return false;
        }
    }
    inData.close();
    return true;
}

bool NeuralNetworkAI::CheckDimensionsFromFile(string fileName){
    ifstream inData;
    inData.open(fileName);
    if(inData.good()){
        string dimensions; getline(inData, dimensions);
        int width = stoi(dimensions.substr(0, dimensions.find(',')));
        dimensions = dimensions.substr(dimensions.find(',') + 2);
        int height = stoi(dimensions.substr(0, dimensions.find(',')));
        int games = stoi(dimensions.substr(dimensions.find(',') + 2));
        if(width == Player::GetBoard()->GetWidth() && height == Player::GetBoard()->GetHeight() && numGames == games){
            return true;
        } else {
            return false;
        }
    } else {
        throw "Error trying to read input data file";
    }
}

void NeuralNetworkAI::CreateNewData(){
    cout << "Creating training data. This may take a moment..." << endl;
    ofstream outMovement; ofstream outBlockMovement; ofstream outDecisions;
    outMovement.open(movement_data_path); outBlockMovement.open(block_data_path); outDecisions.open(decision_data_path);

    NNDecisionTree _tree(Player::GetBoard()->GetWidth(), Player::GetBoard()->GetHeight());
    _tree.buildFullTree(numGames);
    unordered_map<string, string> _allMoves = _tree.getAllMoves();
    unordered_map<string, string> _allBlockingMoves = _tree.getAllBlockingMoves();
    unordered_map<string, string> _allBehaviors = _tree.getAllBehaviors();
    string dimensionsString = to_string(Player::GetBoard()->GetWidth()) + ", " + to_string(Player::GetBoard()->GetHeight()) + ", " + to_string(numGames) + "\n";
    outMovement << dimensionsString;
    outBlockMovement << dimensionsString;
    outDecisions << dimensionsString;
    for(auto& move : _allMoves){
        _labelledMoveData.push_back(move);
        string outputString = move.first + ", " + move.second + "\n";
        outMovement << outputString;
    }
    for(auto& block : _allBlockingMoves){
        _labelledBlockingData.push_back(block);
        string outputString = block.first + ", " + block.second + "\n";
        outBlockMovement << outputString;
    }
    for(auto& behavior : _allBehaviors){
        _labelledBehaviorData.push_back(behavior);
        string outputString = behavior.first + ", " + behavior.second + "\n";
        outDecisions << outputString;
    }
    outMovement.close();
    outBlockMovement.close();
    outDecisions.close();
}

vector<pair<string, string>> NeuralNetworkAI::ReadDataFromFile(string fileName){
    ifstream inData;
    vector<pair<string, string>> _labelledData;

    inData.open(fileName);
    if(inData.good()){
        string dataLine; getline(inData, dataLine); // Skip the line containing dimensions. That will not be needed.
        while(getline(inData, dataLine)){
            string feature = dataLine.substr(0, dataLine.find(','));
            string label = dataLine.substr(dataLine.find(',') + 2, dataLine.find('\n'));
            pair<string, string> featureData(feature, label);
            _labelledData.push_back(featureData);
        }

        return _labelledData;
    } else {
        throw "Error trying to read input data file";
    }
}