#pragma once
#include <iomanip>
#include <iostream>
#include "Player.h"
#include <algorithm>

using namespace std;

class QLearningAI : public Player{
    public:
        QLearningAI(string _name, char _symbol);
        QLearningAI(char _symbol);
        void dropChecker() override;
        void SetPlayersBoard(Board* _board) override;
        void Train(int numEpochs);
        int EGreedyPolicy(Board childBoard, int stateIndex, float e);
    private:
        // By Default: 7 Actions, 7 States
        int numStates; // Incomplete, P1 Win, and P2 Win
        int numActions;
        // numStates corresponds with the index of a vector of possible moves
        
        // numActions corresponds with the parameter in the dropChecker function
        vector<vector<float>> Q_Table; // Each float represents the immediate reward value of each action
        Board::BOARD_STATE _goalState = Board::BOARD_STATE::P2_WIN;
        
        float learningRate = 0.8;
        float discountFactor = 0.95;
        float explorationProbability = 0.2;

        // Helper Functions
        int FindMostRewardingIndex(vector<Board> children, vector<float> stateArray);
        vector<Board> MakeChildren(Board& p);
        vector<Board> CalculateAvailableActions(vector<Board> actions);
        void TakeStep(int actionIndex, int& reward, bool& done);
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
    numStates = _board->GetWidth();
    Q_Table.resize(numStates, vector<float>(numActions));
}

void QLearningAI::dropChecker(){
    int randColIndex = rand() % GetBoard()->GetWidth();
    cout << GetName() << " drops a checker into column " << randColIndex << "." << endl << endl; // This message primarily conveys that the action went through
    GetBoard()->placeChecker(randColIndex, GetSymbol());
}

void QLearningAI::Train(int numEpochs){

    vector<Board> _firstChildren = MakeChildren(*Player::GetBoard()); // First Time Player 1 Moves
    int randStartIndex;
    randStartIndex = (rand() % _firstChildren.size());
    vector<Board> _secondChildren = MakeChildren(_firstChildren.at(randStartIndex)); // First Time Player 2 (AI) Moves
    float _reward = 0.0;
    vector<Board> statesToChoose;
    vector<Board> nextStatesToChoose;
    vector<vector<float>> Next_Q_Table;
    
    for(int i = 0; i < numEpochs; i++){
        randStartIndex = (rand() % _secondChildren.size());
        Board _currentState = _secondChildren.at(randStartIndex); // Select Random Starting State
        while(_currentState.getCurrentState() == Board::BOARD_STATE::INCOMPLETE){
            // Make children and make a future state based on the child of actionIndex
            statesToChoose = MakeChildren(_currentState);
            int actionIndex = EGreedyPolicy(statesToChoose, randStartIndex, explorationProbability);
            // Check if the AI wins by taking this future state, and if so reward = 1
            Board _nextState = statesToChoose.at(actionIndex);
            if(_nextState.getCurrentState() == _goalState){
                _reward = 1.0;
            } else {
                _reward = 0.0;
            }
            // Calculate Q Formula to update Q Table
            float nextBestActionIndex = *max_element(Q_Table.at(randStartIndex).begin(), Q_Table.at(randStartIndex).end());
            Q_Table[randStartIndex][actionIndex] += learningRate * (float)(_reward + discountFactor * nextBestActionIndex - Q_Table[randStartIndex][actionIndex]);
            _currentState = _nextState;
            randStartIndex = actionIndex;
            explorationProbability *= 0.99; // Decay Exploration Rate
            // Set current state to the future state
        }

    }

    cout<<"   Col:";
    for(int i = 0;i < numStates;i++)
    {
        cout<<setw(5)<<i;
    }
    cout << endl;
    for(int row = 0;row < Q_Table.size();row++)
    {
        cout<<"Row "<<setw(2)<<row<<"| ";
        for(int col = 0; col < Q_Table.at(row).size();col++)
        {
            cout<<fixed<<setprecision(1)<<setw(4)<<Q_Table[row][col]<<" ";
        }
        cout<<endl;
    }
}

int QLearningAI::EGreedyPolicy(Board childBoard, int stateIndex, float e){
    int actionIndex = 0;
    float randFloat = (float)((rand() % 100) / 100.0f); // 0 - 1 exclusive
    if(randFloat > e){ // If the random value exceeds the probability of exploration (e)
        // Exploit existing Q Table data to find most rewarding action
        vector<float> stateArray = Q_Table.at(stateIndex);
        float highestReward = stateArray.front();
        for(int col = 0; col < childBoard.GetWidth(); col++){
            if(!childBoard.isFull(col)){
                if(stateArray.at(col) > highestReward){
                    actionIndex = col;
                    highestReward = stateArray.at(col);
                }
            }
        }
    } else {
        // Explore
        vector<int> validActions;
        for(int col = 0; col < childBoard.GetWidth(); col++){
            if(!childBoard.isFull(col)){
                validActions.push_back(col);
            }
        }
        actionIndex = validActions[rand() % (validActions.size())];
    }

    return actionIndex;
}

vector<Board> QLearningAI::CalculateAvailableActions(vector<Board> actions){
    
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