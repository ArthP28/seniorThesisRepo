#pragma once
#include <iomanip>
#include <iostream>
#include "Player.h"
#include "DecisionTree.h"
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// Note: Consider using an unordered-set: Only stores unique states
// Use valid board state as key, vector of actions is the value
// Write a for loop to calculate the largest Q-Value

class QLearningAI : public Player{
    public:
        QLearningAI(string _name, char _symbol);
        QLearningAI(char _symbol);
        ~QLearningAI();
        void dropChecker() override;
        void SetPlayersBoard(Board* _board) override;
        void Train(int numEpochs);
        int EGreedyPolicy(Board childBoard, string stateString, double e);
    private:
        // By Default: 7 Actions, 7 States
        int numStates; // Incomplete, P1 Win, and P2 Win
        int numActions;
        // numStates corresponds with the index of a vector of possible moves
        
        // numActions corresponds with the parameter in the dropChecker function
        vector<vector<float>> Q_Table; // Each float represents the immediate reward value of each action
        unordered_map<string, vector<double>>* New_Q_Table;
        Board::BOARD_STATE _goalState = Board::BOARD_STATE::P2_WIN;
        Board::BOARD_STATE _defeatState = Board::BOARD_STATE::P1_WIN;
        
        double learningRate = 0.1;
        double discountFactor = 0.9;
        double explorationProbability = 0.5;

        // Helper Functions
        int FindMostRewardingIndex(vector<double> stateArray);
        vector<Board> MakeChildren(Board& p);
        vector<Board> CalculateAvailableActions(vector<Board> actions);
        void TakeStep(int actionIndex, int& reward, bool& done);
        void InitializeQTable();
        vector<int> GetAllAvailableActionIndices(string stateString);
        bool isAllZeroes(vector<double>& vec);
        void updateQTable(string currentState, string nextState, int actionIndex, double reward);
};


QLearningAI::QLearningAI(string _name, char _symbol) : Player(_name, _symbol){
    Player::_playerName = _name;
}

QLearningAI::QLearningAI(char _symbol) : Player(_symbol){
    Player::_playerName = "Q";
}

QLearningAI::~QLearningAI(){
    delete New_Q_Table;
    New_Q_Table = NULL;
}

void QLearningAI::InitializeQTable(){
    DecisionTree _tree(Player::GetBoard()->GetWidth(), Player::GetBoard()->GetHeight());
    _tree.buildFullTree();
    unordered_set<string> _validBoardStrings = _tree.GetAllValidBoardStrings();

    New_Q_Table = new unordered_map<string, vector<double>>;
    for(string _boardString : _validBoardStrings){
        pair<string, vector<double>> _stateActionPair(_boardString, vector<double>(numActions));
        New_Q_Table->insert(_stateActionPair);
    }
}

void QLearningAI::SetPlayersBoard(Board* _board){
    Player::SetPlayersBoard(_board);
    numActions = _board->GetWidth();
    //numStates = 4500000000000;
    numStates = _board->GetWidth();
    InitializeQTable();
    //Q_Table.resize(numStates, vector<float>(numActions));
}

void QLearningAI::dropChecker(){
    string _currBoardString = Player::GetBoard()->boardToString();
    vector<int> _availableActions = GetAllAvailableActionIndices(_currBoardString);
    vector<double> Q_State = New_Q_Table->at(_currBoardString);
    double highestReward = INT32_MIN;
    int mostValuedAction = _availableActions[0];
    for(int actionIndex : _availableActions){
        if(Q_State.at(actionIndex) > highestReward){
            highestReward = Q_State.at(actionIndex);
            mostValuedAction = actionIndex;
        }
    }
    // for(int i = 0; i < Q_State.size(); i++){
    //     if(Q_State.at(i) > highestReward){
    //         highestReward = Q_State.at(i);
    //         mostValuedAction = i;
    //     }
    // }
    cout << GetName() << " drops a checker into column " << mostValuedAction << "." << endl << endl; // This message primarily conveys that the action went through
    GetBoard()->placeChecker(mostValuedAction, GetSymbol());
}

void QLearningAI::Train(int numEpochs){
    char curr_checkers[] = {'R', 'B'};
    double _reward = 0.0; // Reward Value
    vector<int> statesToChoose; // A scalable array containing indices of all the available states to select
    // Each training episode (epoch) ends when either player wins or the board is filled with no winner (A tie, although rare, is still a possibility)
    for(int i = 0; i < numEpochs; i++){ // The training cycle loops for a certain number of epochs
        char currentCheckerIndex = 0;
        Board _currentState = *Player::GetBoard();
        // Prepare Q-Learning Environment: Player 2 always goes after Player 1
        //vector<Board> _firstChildren = MakeChildren(*Player::GetBoard()); // First Time Player 1 Moves
        // int lastActionTaken = (rand() % _currentState.GetWidth());; // Index storing the previous action taken by the AI player
        // _currentState.placeChecker(lastActionTaken, curr_checkers[currentCheckerIndex]);
        // currentCheckerIndex = 1;
        while(_currentState.getCurrentState() == Board::BOARD_STATE::INCOMPLETE){
            string _currentStateString = _currentState.boardToString();
            int actionIndex = EGreedyPolicy(_currentState, _currentStateString, explorationProbability); // Generate an index of the next move based on an epsilon greedy policy
            Board _nextState = _currentState; // Make a new board to play the decided action
            _nextState.placeChecker(actionIndex, curr_checkers[currentCheckerIndex]);
            Board::BOARD_STATE _futureStatus = _nextState.getCurrentState();
            if(_futureStatus != Board::BOARD_STATE::INCOMPLETE){
                if(_futureStatus == _goalState){ // Check if the AI wins by taking this action, and if so, reward = 1
                    _reward = 1.0;
                } else if(_futureStatus == Board::BOARD_STATE::DRAW){
                    _reward = 0.5;
                } else {
                    _reward = -1.0;
                }
                updateQTable(_currentStateString, _currentStateString, actionIndex, _reward);
            } else {
                _reward = 0.0;
                string _nextStateString = _nextState.boardToString();
                updateQTable(_currentStateString, _nextStateString, actionIndex, _reward);
                currentCheckerIndex = (currentCheckerIndex + 1) % 2;
                // vector<int> validActions = GetAllAvailableActionIndices(_nextStateString);
                // int randColIndex = validActions[rand() % (validActions.size())];
                // _nextState.placeChecker(randColIndex, curr_checkers[0]);
    
                // Set current state to the next state
                
                //lastActionTaken = actionIndex;
            }

            // if(_currentState.getCurrentState() == Board::BOARD_STATE::INCOMPLETE){
                
            // }
            _currentState = _nextState;
        }
        explorationProbability *= 0.99; // Decay Exploration Rate: AI exploits existing table data more

        if(i % 10000 == 0){
            cout << "Current Number of Epochs: " << i << endl;
        }
    }

    int allNonZero = 0;
    for(auto& Q_Pair : *New_Q_Table){
        if(!isAllZeroes(Q_Pair.second)){
            //int w = (Player::GetBoard()->GetHeight() * Player::GetBoard()->GetWidth()) + Player::GetBoard()->GetWidth() - Q_Pair.first.length();
            cout << Q_Pair.first << " - { ";
            for(int i = 0; i < Q_Pair.second.size(); i++){
                cout << Q_Pair.second.at(i);
                if(i < Q_Pair.second.size() - 1){
                    cout << ", ";
                } else {
                    cout << " ";
                }
            }
            cout << "}" << endl;
            allNonZero++;
        }
    }

    cout << "Non-zero States: " << allNonZero << "/" << New_Q_Table->size() << endl;
}

void QLearningAI::updateQTable(string currentState, string nextState, int actionIndex, double reward){
    double nextBestQAction = INT16_MIN;
    Board nextStateBoard = Board(nextState, Player::GetBoard()->GetHeight());
    // Determine the next possible future action
    for(int col = 0; col < Player::GetBoard()->GetWidth(); col++) {
        if(!nextStateBoard.isFull(col)) {
            // if(New_Q_Table->find(nextState) == New_Q_Table->end()){ // TEMPORARY
            //     pair<string, vector<double>> _stateActionPair(nextState, vector<double>(numActions));
            //     New_Q_Table->insert(_stateActionPair);
            // }
            if(New_Q_Table->at(nextState).at(col) > nextBestQAction){
                nextBestQAction = New_Q_Table->at(nextState).at(col);
            }
        } else {
            New_Q_Table->at(nextState).at(col) = -1.0;
        }
    }

    // if(New_Q_Table->find(currentState) == New_Q_Table->end()){ // TEMPORARY
    //     pair<string, vector<double>> _stateActionPair(currentState, vector<double>(numActions));
    //     New_Q_Table->insert(_stateActionPair);
    // }
    vector<double> StateActionPair = New_Q_Table->at(currentState);
    // Calculate Q Formula to update Q Table
    StateActionPair.at(actionIndex) += learningRate * (double)(reward + discountFactor * nextBestQAction - StateActionPair.at(actionIndex));
    New_Q_Table->at(currentState) = StateActionPair;

}

int QLearningAI::EGreedyPolicy(Board childBoard, string stateString, double e){
    vector<int> validActions = GetAllAvailableActionIndices(stateString);
    int actionIndex = validActions[0];
    double randdouble = (double)((rand() % 100) / 100.0f); // 0 - 1 exclusive
    if(randdouble > e){ // If the random value exceeds the probability of exploration (e)
        // Exploit existing Q Table data to find most rewarding action
        // if(New_Q_Table->find(stateString) == New_Q_Table->end()){ // TEMPORARY
        //     pair<string, vector<double>> _stateActionPair(stateString, vector<double>(numActions));
        //     New_Q_Table->insert(_stateActionPair);
        // }
        vector<double> listOfActions = New_Q_Table->at(stateString);
        double highestReward = INT32_MIN;
        for(int validAction : validActions){
            if(listOfActions.at(validAction) > highestReward){
                actionIndex = validAction;
                highestReward = listOfActions.at(validAction);
            }
        }
    } else {
        // Explore
        vector<int> validActions = GetAllAvailableActionIndices(stateString);
        actionIndex = validActions[rand() % (validActions.size())];
    }

    return actionIndex;
}

vector<int> QLearningAI::GetAllAvailableActionIndices(string stateString){
    vector<int> _availableActions;
    Board b = Board(stateString, Player::GetBoard()->GetHeight());
    for(int i = 0; i < Player::GetBoard()->GetWidth(); i++){
        if(!b.isFull(i)){
            _availableActions.push_back(i);
        }
    }
    return _availableActions;
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

bool QLearningAI::isAllZeroes(vector<double>& vec){
    for(double f : vec){
        if(f != 0.0) return false;
    }
    return true;
}