#pragma once
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <unordered_set>
#include "Board.h"

using namespace std;

// FUTURE NOTE: Try to get the number of board states to tens of thousands
// Total board states should not be 4.5 trillion
// The states dimension should reflect the actual number of valid states possible in Connect Four
class DecisionTree
{
public:
    DecisionTree(int w, int h);
    ~DecisionTree(); // Deconstructor
    void buildFullTree(); // Construct the whole tree of possible states
    void buildFullTree(int max); // Construct the whole tree of possible states

    // Search Algorithms
    void breadthFirstSearchForOutcome(string boardSring, Board::BOARD_STATE requestedState);
    void depthFirstSearchForOutcome(string boardSring, Board::BOARD_STATE requestedState);
    unordered_set<string> GetAllValidBoardStrings() { return _allValidBoardStrings; };

    unordered_set<string> _allValidBoardStrings;
private:

    struct Node
    {
        string board_String;
        vector < Node* > children;
        Node* parent;
    };
    Node* root; // The first node that represents the current/first state of the game
    Node* currNode;
    
    // Counter Variables for the Full Tree
    int totalGames = 0;
    int totalP1Wins = 0;
    int totalP2Wins = 0;
    int totalDraws = 0;
    int totalMoves = 0;

    int maxDepth = 0;
    int depthVal = 0;

    int width;
    int height;

    // -- Helper Functions --
    Node* addNode(Node* p, string b_string);
    void generateStates(Node* p, string& b_string);
    void generateStates(Node* p, string& b_string, int& max);
    void removeAll(Node* p); // Recursive Function that removes all of the nodes in the entire t
    void deleteNode(Node*& n); // Recursive Function that removes all of a source node's childre
};

/*************************/
//  -C- CONSTRUCTOR -C-  //
/*************************/
DecisionTree::DecisionTree(int w, int h){ // Construct the whole tree of possible states
    root = new Node;
    width = w;
    height = h;
    root->board_String = string(width, '|');
    root->parent = NULL;
    currNode = root;
    _allValidBoardStrings.insert(root->board_String);
}

/*************************/
// -X- DECONSTRUCTOR -X- //
/*************************/
DecisionTree::~DecisionTree(){
    removeAll(root); // Remove all of the tree's child nodes
    deleteNode(root); // Then delete the root node itself
}

/**************************/
// -P- PUBLIC METHODS -P- //
/**************************/
void DecisionTree::buildFullTree(){
    // Generate the children listing possible placements of O on the board
    generateStates(root, root->board_String);
    
    // Output stats
    cout << "Total Games: " << totalGames << endl;
    cout << "# Times P1 Wins: " << totalP1Wins << endl;
    cout << "# Times P2 Wins: " << totalP2Wins<< endl;
    cout << "# Draws: " << totalDraws << endl;
    cout << "Total Number of Possible Moves (Unordered Set): " << _allValidBoardStrings.size() << endl;
    cout << "Total Number of Possible Moves (Counter): " << totalMoves << endl;
    cout << "Maximum Depth: " << maxDepth << endl;
}

void DecisionTree::buildFullTree(int max){
    // Generate the children listing possible placements of O on the board
    generateStates(root, root->board_String, max);
    
    // Output stats
    cout << "Total Games: " << totalGames << endl;
    cout << "# Times P1 Wins: " << totalP1Wins << endl;
    cout << "# Times P2 Wins: " << totalP2Wins<< endl;
    cout << "# Draws: " << totalDraws << endl;
    cout << "Total Number of Possible Moves (Unordered Set): " << _allValidBoardStrings.size() << endl;
    cout << "Total Number of Possible Moves (Counter): " << totalMoves << endl;
    cout << "Maximum Depth: " << maxDepth << endl;
}
/***************************/
// -p- Private Methods -p- //
/***************************/
void DecisionTree::generateStates(Node* p, string& b_string){ // Create a tree of all possible future states from a specific node
    char charToAdd;
    Board currBoard(b_string, height);
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
                if(_allValidBoardStrings.find(_nextBoardString) == _allValidBoardStrings.end()){
                    addNode(p, _nextBoardString);
                    _allValidBoardStrings.insert(_nextBoardString);
                    totalMoves++;

                    if(totalMoves % 100000 == 0)
                    {
                        cout<<totalMoves<<endl;
                    }
                } else {
                    //cout << "Duplicate of board string found: " << _nextBoardString << endl;
                }
            }
        }
        for(int i = 0; i < p->children.size(); i++){
            // if(p->children.at(i) == root->children.at(1)){
            //     cout << "Generating other children" << endl;
            // }
            generateStates(p->children.at(i), p->children.at(i)->board_String);
        }
        while(!p->children.empty()){
            deleteNode(p->children.back());
            p->children.pop_back();
        }

    } else { // If the game is complete, determine if the endgame is an O Victory, an X victory, or a draw
        if(currBoard.getCurrentState() == Board::BOARD_STATE::P1_WIN){
            totalP1Wins++;
        } else if (currBoard.getCurrentState() == Board::BOARD_STATE::P2_WIN){
            totalP2Wins++;
        } else if (currBoard.getCurrentState() == Board::BOARD_STATE::DRAW){
            totalDraws++;
        }
        totalGames++;
    }
    //depthVal--; // Going up tree
}

void DecisionTree::generateStates(Node* p, string& b_string, int& max){ // Create a tree of all possible future states from a specific node
    char charToAdd;
    Board currBoard(b_string, height);
    if(totalGames < max){
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
                    if(_allValidBoardStrings.find(_nextBoardString) == _allValidBoardStrings.end()){
                        addNode(p, _nextBoardString);
                        _allValidBoardStrings.insert(_nextBoardString);
                        totalMoves++;
    
                        if(totalMoves % 100000 == 0)
                        {
                            cout<<totalMoves<<endl;
                        }
                    } else {
                        //cout << "Duplicate of board string found: " << _nextBoardString << endl;
                    }
                }
            }
            for(int i = 0; i < p->children.size(); i++){
                // if(p->children.at(i) == root->children.at(1)){
                //     cout << "Generating other children" << endl;
                // }
                generateStates(p->children.at(i), p->children.at(i)->board_String, max);
            }
            while(!p->children.empty()){
                deleteNode(p->children.back());
                p->children.pop_back();
            }
    
        } else { // If the game is complete, determine if the endgame is an O Victory, an X victory, or a draw
            if(currBoard.getCurrentState() == Board::BOARD_STATE::P1_WIN){
                totalP1Wins++;
            } else if (currBoard.getCurrentState() == Board::BOARD_STATE::P2_WIN){
                totalP2Wins++;
            } else if (currBoard.getCurrentState() == Board::BOARD_STATE::DRAW){
                totalDraws++;
            }
            totalGames++;
        }
    } else {
        cout << totalGames << " reached!" << endl;
    }
}

DecisionTree::Node* DecisionTree::addNode(Node* p, string b_string){ // Make a new node and link it to the parent
    Node* n = new Node;
    n->board_String = b_string;
    n->parent = p;
    p->children.push_back(n);
    return n;
}

void DecisionTree::removeAll(Node* p){ // Delete all of a parent node's children and their descendants
    while(!p->children.empty()){ // Recursive call to deal with all the nodes children first before deleting itself
        removeAll(p->children.back());
        p->children.pop_back();
    }
    if(p->parent != NULL){
        // Only if the node has no children will it be deleted
        deleteNode(p);
    }
}

void DecisionTree::deleteNode(Node*& n){ // Set all its pointer info to null and remove the node
    //std::cout <<"Deleting Node with "<<n->board->getBoardString()<< endl; 
    //delete n->board;
    //n->board_String = NULL;
    n->parent = NULL;
    delete n;
    n = NULL;
}