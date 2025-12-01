#pragma once
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cmath>
#include <unordered_set>
#include "QDecisionTree.h"
#include "Board.h"

using namespace std;

// FUTURE NOTE: Try to get the number of board states to tens of thousands
// Total board states should not be 4.5 trillion
// The states dimension should reflect the actual number of valid states possible in Connect Four
class NNDecisionTree
{
public:
    NNDecisionTree(int w, int h);
    ~NNDecisionTree();
    void buildFullTree(); // Construct the whole tree of possible states
    void buildFullTree(int max); // Construct the whole tree of possible states
    unordered_map<string, string> getAllMoves() { return _allMoves; };
    unordered_map<string, string> getAllBlockingMoves() { return _allBlocks; };
    unordered_map<string, string> getAllBehaviors() { return _behaviors; };
private:
    struct Node
    {
        //Board* b;
        string board_String;
        int actionIndex = 0;
        string label;
        vector < Node* > children;
        Node* parent;
        //int visits = 0;
        //int wins = 0;
        //vector<int> unexploredActions;
    };
    Node* root; // The first node that represents the current/first state of the game
    Node* currNode;
    
    // Counter Variables for the Full Tree
    int totalCurrentGames = 0;
    int totalGames = 0;
    int totalP1Wins = 0;
    int totalP2Wins = 0;
    int totalDraws = 0;
    int totalMoves = 0;

    int boardSize = 0;
    int width = 0;
    int height = 0;

    // NN Architecture
    // Inputs: 7x6 = 42 board spaces
    // Layers: Variable
    // Outputs: 7 Actions
    // Due to the variable structure of the Connect 4 Board, the action labels will have to be automatically generated
    //vector<int> networkArchitecture = { boardSize, 3, width };
    unordered_map<string, string> _allMoves;
    unordered_map<string, string> _allBlocks;
    unordered_map<string, string> _behaviors;
    
    
    // -- Helper Functions --
    Node* addNode(Node* p, string b_string, int col);
    void generateStates(Node* p, string& b_string);
    void generateStates(Node* p, string& b_string, int& max);
    void removeAll(Node* p); // Recursive Function that removes all of the nodes in the entire t
    void deleteNode(Node*& n); // Recursive Function that removes all of a source node's children
    void propagateBack(Node*& n, vector<Node*>& _path); // Go backwards through every node of the winning path and save each one to a vector
    //double calculateUCB1(Node*& n);
    //void explore(Node*& p);
    //void Save(); // Take the unordered_map of labeled features, and put each pair in an output file
};

/*************************/
//  -C- CONSTRUCTOR -C-  //
/*************************/
NNDecisionTree::NNDecisionTree(int w, int h){ // Construct the whole tree of possible states
    root = new Node;
    width = w;
    height = h;
    root->board_String = string(width, '|');
    root->parent = NULL;
    currNode = root;
}

/*************************/
// -X- DECONSTRUCTOR -X- //
/*************************/
NNDecisionTree::~NNDecisionTree(){
    removeAll(root); // Remove all of the tree's child nodes
    deleteNode(root); // Then delete the root node itself
}

/**************************/
// -P- PUBLIC METHODS -P- //
/**************************/
void NNDecisionTree::buildFullTree(){ // WARNING: Method is highly experimental! Call this method at your own risk!
    // Generate the children listing possible placements of O on the board
    generateStates(root, root->board_String);
    
    // Output stats
    cout << "Total Games: " << totalGames << endl;
    cout << "# Times P1 Wins: " << totalP1Wins << endl;
    cout << "# Times P2 Wins: " << totalP2Wins<< endl;
    cout << "# Draws: " << totalDraws << endl;
    cout << "Total Number of Possible Moves (Counter): " << totalMoves << endl;
    cout << "Total Number of Possible Moves (Unordered Set): " << _allMoves.size() << endl;

}

void NNDecisionTree::buildFullTree(int max){
    generateStates(root, root->board_String, max);
    // max /= width;
    // Board startingBoard(root->board_String, height);
    // for(int col = 0; col < startingBoard.GetWidth(); col++){
    //     if(!startingBoard.isFull(col)){
    //         Board nextBoard = startingBoard;
    //         nextBoard.placeChecker(col, 'R');
    //         string _nextBoardString = nextBoard.boardToString();
    //         totalMoves++;
    //         addNode(root, _nextBoardString, col);
    //     }
    // }
    // for(int i = 0; i < width; i++){
    //     Node* child = root->children.at(i);
    //     while(totalCurrentGames < max){
    //         generateStates(child, child->board_String, max);
    //     }
    //     totalGames+=totalCurrentGames;
    //     totalCurrentGames = 0;
    // }
    // Generate the children listing possible placements of O on the board
    //while(totalGames < max){
        //generateStates(root, root->board_String, max);
    //}
    
    // Output stats
    cout << "Total Games: " << totalGames << endl;
    cout << "# Times P1 Wins: " << totalP1Wins << endl;
    cout << "# Times P2 Wins: " << totalP2Wins<< endl;
    cout << "# Draws: " << totalDraws << endl;
    cout << "Total Number of Possible Moves (Counter): " << totalMoves << endl;
    cout << "Total Number of Possible Moves (Unordered Set): " << _allMoves.size() << endl;

}
/***************************/
// -p- Private Methods -p- //
/***************************/
void NNDecisionTree::generateStates(Node* p, string& b_string){ // Create a tree of all possible future states from a specific node
    char charToAdd;
    Board currBoard(b_string, height);
    //Board nextBoard = currBoard;
    if(currBoard.getCurrentState() == Board::BOARD_STATE::INCOMPLETE){
        if(currBoard.getNextTurn() == Board::PLAYER_TURN::P1){
            charToAdd = 'R';
        } else if (currBoard.getNextTurn() == Board::PLAYER_TURN::P2){
            charToAdd = 'B';
        }
        // Iterate through all possible char placements within the board
        for(int col = 0; col < currBoard.GetWidth(); col++){
            if(!currBoard.isFull(col)){
                Board nextBoard = currBoard;
                nextBoard.placeChecker(col, charToAdd);
                string _nextBoardString = nextBoard.boardToString();
                totalMoves++;
                addNode(p, _nextBoardString, col);
                
                //p->label = to_string(col); // Move to play from current state of the board
            }
        }
        for(int i = 0; i < p->children.size(); i++){
            generateStates(p->children.at(i), p->children.at(i)->board_String);
        }
        while(!p->children.empty()){
            deleteNode(p->children.back());
            p->children.pop_back();
        }

    } else { // If the game is complete, determine if the endgame is an O Victory, an X victory, or a draw
        if(currBoard.getCurrentState() == Board::BOARD_STATE::P1_WIN){
            totalP1Wins++;
        } else if (currBoard.getCurrentState() == Board::BOARD_STATE::P2_WIN){ // AI Wins
            totalP2Wins++;
            vector<Node*> _winPath;
            propagateBack(p, _winPath); // Referenced path goes from end to start
            // Add each node of the whole path into the unordered map of all moves
            for(int i = _winPath.size() - 2; i >= 1; i-=2){
                Node*& n = _winPath.at(i);
                Node*& n_child = _winPath.at(i-1);
                string label = to_string(n_child->actionIndex); // Label is the player move that advances the game from one board state to the next
                // FUTURE: Label is calculated from the column move index of the next node, board string is from the current node
                // Pair<board string, label>
                pair<string, string> labeledFeatureString(n->board_String, label);
                _allMoves.insert(labeledFeatureString);
            }
        } else if (currBoard.getCurrentState() == Board::BOARD_STATE::DRAW){
            totalDraws++;
        }
        totalGames++;
        if(totalGames % 100000 == 0)
        {
            cout<<totalGames<<endl;
        }
    }
    //depthVal--; // Going up tree
}

void NNDecisionTree::generateStates(Node* p, string& b_string, int& max){ // Create a tree of all possible future states from a specific node
    char charToAdd;
    Board currBoard(b_string, height);
    // if(b_string == "R|||||||" || b_string == "|R||||||" || b_string == "||R|||||" || b_string == "|||R||||" || b_string == "||||R|||" || b_string == "|||||R||" || b_string == "||||||R|"){
    //     cout << b_string << endl;
    // }
    if(totalCurrentGames < max){
        if(currBoard.getCurrentState() == Board::BOARD_STATE::INCOMPLETE){
            if(currBoard.getNextTurn() == Board::PLAYER_TURN::P1){
                charToAdd = 'R';
            } else if (currBoard.getNextTurn() == Board::PLAYER_TURN::P2){
                charToAdd = 'B';
            }
            // Iterate through all possible char placements within the board
            for(int col = 0; col < currBoard.GetWidth(); col++){
                if(!currBoard.isFull(col)){
                    Board nextBoard = currBoard;
                    nextBoard.placeChecker(col, charToAdd);
                    string _nextBoardString = nextBoard.boardToString();
                    totalMoves++;
                    addNode(p, _nextBoardString, col);
                    
                    //p->label = to_string(col); // Move to play from current state of the board
                }
            }
            // int randIndex = rand() % p->children.size();
            // generateStates(p->children.at(randIndex), p->children.at(randIndex)->board_String, max);
            for(int i = 0; i < p->children.size(); i++){
                generateStates(p->children.at(i), p->children.at(i)->board_String, max);
            }
            while(!p->children.empty()){
                deleteNode(p->children.back());
                p->children.pop_back();
            }
    
        } else { // If the game is complete, determine if the endgame is an O Victory, an X victory, or a draw
            if(currBoard.getCurrentState() == Board::BOARD_STATE::P1_WIN){
                totalP1Wins++;
                // Set the grandchild of the current node (AKA red's move before blue's move that led to red's win) to BLOCK.
                // Record winning move as the label of the column number that will block the winning move.
                Node*& prevP1 = p->parent->parent;
                string blockLabel = to_string(p->actionIndex); // Red's winning move
                pair<string, string> labeledBehaviorString(prevP1->board_String, "BLOCK");
                pair<string, string> labeledBlockString(prevP1->board_String, blockLabel);
                _allBlocks.insert(labeledBlockString);
                _behaviors.insert(labeledBehaviorString);
            } else if (currBoard.getCurrentState() == Board::BOARD_STATE::P2_WIN){ // AI Wins
                totalP2Wins++;
                vector<Node*> _winPath;
                propagateBack(p, _winPath); // Referenced path goes from end to start
                // Add each node of the whole path into the unordered map of all moves
                for(int i = _winPath.size() - 2; i >= 1; i-=2){
                    Node*& n = _winPath.at(i); // Red's Turn
                    Node*& n_child = _winPath.at(i-1); // Blue's Turn
                    string label = to_string(n_child->actionIndex); // Label is the player move that advances the game from one board state to the next
                    // FUTURE: Label is calculated from the column move index of the next node, board string is from the current node
                    // Pair<board string, label>
                    pair<string, string> labeledBehaviorString(n->board_String, "MOVE");
                    pair<string, string> labeledMovementString(n->board_String, label);
                    _allMoves.insert(labeledMovementString);
                    _behaviors.insert(labeledBehaviorString);
                }
            } else if (currBoard.getCurrentState() == Board::BOARD_STATE::DRAW){
                totalDraws++;
            }
            totalCurrentGames++;
            if(totalCurrentGames % 100000 == 0)
            {
                cout<<totalCurrentGames<<endl;
            }
        }
    } else {
        //cout << totalGames << " reached!" << endl;
    }
}

NNDecisionTree::Node* NNDecisionTree::addNode(Node* p, string b_string, int col){ // Make a new node and link it to the parent
    Node* n = new Node;
    n->board_String = b_string;
    n->actionIndex = col;
    n->parent = p;
    p->children.push_back(n);
    return n;
}

void NNDecisionTree::removeAll(Node* p){ // Delete all of a parent node's children and their descendants
    while(!p->children.empty()){ // Recursive call to deal with all the nodes children first before deleting itself
        removeAll(p->children.back());
        p->children.pop_back();
    }
    if(p->parent != NULL){
        // Only if the node has no children will it be deleted
        deleteNode(p);
    }
}

void NNDecisionTree::deleteNode(Node*& n){ // Set all its pointer info to null and remove the node
    //std::cout <<"Deleting Node with "<<n->board->getBoardString()<< endl; 
    //delete n->board;
    //n->board_String = NULL;
    n->parent = NULL;
    delete n;
    n = NULL;
}

void NNDecisionTree::propagateBack(Node*& n, vector<Node*>& _path){
    _path.push_back(n);
    if(n->parent != NULL){
        propagateBack(n->parent, _path);
    }
}

// void NNDecisionTree::Save(){
//     for(auto& move : _allMoves){
        
//     }
// }

// double NNDecisionTree::calculateUCB1(Node*& n){
//     if(n->visits == 0){
//         return double('inf');
//     }
//     Node* top_node = n;
//     if(n->parent != NULL){
//         top_node = n->parent;
//     }
//     double avg = n->wins / n->visits;
//     double c = 1.4;
//     return avg + c * sqrt(log(top_node->visits) / n->visits);
// }

// void NNDecisionTree::explore(Node*& p){
//     for(int i = 0; i < p->children.size(); i++){
//         // Generate actions of child with most UCB
//         double max_UCB = 0.0;

//     }
// }