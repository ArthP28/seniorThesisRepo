#pragma once
#include <iostream>
#include "Player.h"

using namespace std;

class QLearningAI : public Player{
    public:
        QLearningAI(string _name, char _symbol);
        QLearningAI(char _symbol);
        void dropChecker() override;
        void SetPlayersBoard(Board* _board) override;
        void Train(int numEpochs);
        int EGreedyPolicy(vector<vector<float>> qtable, int stateIndex, float e);
    private:
        // By Default: 7 Actions, 7 States
        int numStates = 3; // Incomplete, P1 Win, and P2 Win
        int numActions;
        // numStates corresponds with the index of a vector of possible moves
        vector<Board> statesToChoose;
        // numActions corresponds with the parameter in the dropChecker function
        vector<vector<float>> Q_Table; // Each float represents the immediate reward value of each action
        Board::BOARD_STATE _goalState = Board::BOARD_STATE::P2_WIN;
        
        float learningRate = 0.8;
        float discountFactor = 0.95;
        float explorationProbability = 0.2;

        // Helper Functions
        int FindMostRewardingIndex(vector<float> stateArray);
        vector<Board> MakeChildren(Board& p);
};


QLearningAI::QLearningAI(string _name, char _symbol) : Player(_name, _symbol){
    Player::_playerName = _name;
}

QLearningAI::QLearningAI(char _symbol) : Player(_symbol){
    Player::_playerName = "Q";
}

void QLearningAI::SetPlayersBoard(Board* _board){
    Player::SetPlayersBoard(_board);
    numActions = _board->GetWidth();
    Q_Table.resize(numStates, vector<float>(numActions));
}

void QLearningAI::dropChecker(){
    int randColIndex = rand() % GetBoard()->GetWidth();
    cout << GetName() << " drops a checker into column " << randColIndex << "." << endl << endl; // This message primarily conveys that the action went through
    GetBoard()->placeChecker(randColIndex, GetSymbol());
}

void QLearningAI::Train(int numEpochs){

    vector<Board> _firstChildren = MakeChildren(*Player::GetBoard());
    int randStartIndex = (rand() % _firstChildren.size() + 1);
    vector<Board> _secondChildren = MakeChildren(_firstChildren.at(randStartIndex));
    
    for(int i = 0; i < numEpochs; i++){
        int randState = (rand() % _secondChildren.size() + 1);
        Board _currentState = _secondChildren.at(randState);
        while(_currentState.getCurrentState() != _goalState){
            int actionIndex = EGreedyPolicy(Q_Table, randState, explorationProbability);
            // Make children and make a future state based on the child of actionIndex
            
            // Check if the AI wins by taking this future state, and if so reward = 1

            // Calculate Q Formula

            // Set current state to the future state
        }

    }
}

int QLearningAI::EGreedyPolicy(vector<vector<float>> qtable, int stateIndex, float e){
    int actionIndex = 0;
    float randFloat = rand(); // 0 - 1 exclusive
    if(randFloat > e){ // If the random value exceeds the probability of exploration (e)
        // Exploit existing Q Table data to find most rewarding action
        actionIndex = FindMostRewardingIndex(qtable.at(stateIndex));
    } else {
        // Explore
        actionIndex = (rand() % numActions) + 1;
    }

    return actionIndex;
}

int QLearningAI::FindMostRewardingIndex(vector<float> stateArray){
    int highestIndex = 0;
    float highestReward = stateArray.front();
    for(int i = 1; i < stateArray.size(); i++){
        if(stateArray.at(i) > highestReward){
            highestIndex = i;
            highestReward = stateArray.at(i);
        }
    }
    return highestIndex;
}

vector<Board> QLearningAI::MakeChildren(Board& p){
    vector<Board> allChildren;
    char charToAdd;
    vector<string> currentGrid = p.GetGrid();
    Board futureBoard;
    if(p.getNextTurn() == Board::PLAYER_TURN::P1){
        charToAdd = 'R';
    } else if (p.getNextTurn() == Board::PLAYER_TURN::P2){
        charToAdd = 'B';
    }
    // Iterate through all possible char placements within the board
    for(int col = 0; col < currentGrid.size(); col++){
        if(!p.isFull(col)){
            for(int row = 0; row < currentGrid.at(col).length(); row++){
                if(currentGrid.at(col)[row] == p.getEmptyChar()){
                    currentGrid.at(col)[row] = charToAdd;
                    futureBoard = Board(currentGrid);
                    allChildren.push_back(futureBoard);
                    currentGrid.at(col)[row] = p.getEmptyChar();
                    break;
                }
            }
        }
    }
    return allChildren;
}