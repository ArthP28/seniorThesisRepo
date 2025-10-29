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
    DecisionTree();
    ~DecisionTree(); // Deconstructor
    void createChildren(Board*& b); // Construct the whole tree of possible states

    // Search Algorithms
    void breadthFirstSearchForOutcome(string boardSring, Board::BOARD_STATE requestedState);
    void depthFirstSearchForOutcome(string boardSring, Board::BOARD_STATE requestedState);

    unordered_set<string> _allValidBoardStrings;
private:

    struct Node
    {
        Board* board;
        vector < Node* > children;
        Node* parent;
    };
    Node* root; // The first node that represents the current/first state of the game
    Node* currNode;
    
    // Counter Variables for the Full Tree
    int totalGames;
    int totalXWins;
    int totalOWins;
    int totalDraws;
    long totalMoves;

    // -- Helper Functions --
    Node* addNode(Node* p, Board* b);
    void generateStates(Node* p, Board*& b);
    void removeAll(Node* p); // Recursive Function that removes all of the nodes in the entire t
    void deleteNode(Node*& n); // Recursive Function that removes all of a source node's childre
};

/*************************/
//  -C- CONSTRUCTOR -C-  //
/*************************/
DecisionTree::DecisionTree(){ // Construct the whole tree of possible states
    root = new Node;
    root->board = new Board;
    root->parent = NULL;
    currNode = root;
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
void DecisionTree::createChildren(Board*& b){

}
/***************************/
// -p- Private Methods -p- //
/***************************/
void DecisionTree::generateStates(Node* p, Board*& b){ // Create a tree of all possible future states from a specific node
    char charToAdd;
    vector<string> currentGrid = b->GetGrid();
    Board* futureBoard;
    if(b->getNextTurn() == Board::PLAYER_TURN::P1){
        charToAdd = 'R';
    } else if (b->getNextTurn() == Board::PLAYER_TURN::P2){
        charToAdd = 'B';
    }
    // Iterate through all possible char placements within the board
    for(int col = 0; col < currentGrid.size(); col++){
        if(!b->isFull(col)){
            for(int row = 0; row < currentGrid.at(col).length(); row++){
                if(currentGrid.at(col)[row] == b->getEmptyChar()){
                    currentGrid.at(col)[row] = charToAdd;
                    futureBoard = new Board(currentGrid);
                    addNode(p, futureBoard);
                    currentGrid.at(col)[row] = b->getEmptyChar();
                    break;
                }
            }
        }
    }
}

DecisionTree::Node* DecisionTree::addNode(Node* p, Board* b){ // Make a new node and link it to the parent
    Node* n = new Node;
    n->board = b;
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
    delete n->board;
    n->board = NULL;
    n->parent = NULL;
    delete n;
    n = NULL;
}