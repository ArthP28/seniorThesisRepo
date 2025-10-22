#pragma once
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include "Board.h"

using namespace std;

class DecisionTree
{
public:
    ~DecisionTree(); // Deconstructor
    void buildFullTree(); // Construct the whole tree of possible states

    // Search Algorithms
    void breadthFirstSearchForOutcome(string boardSring, Board::BOARD_STATE requestedState);
    void depthFirstSearchForOutcome(string boardSring, Board::BOARD_STATE requestedState);
    private:

    struct Node
    {
        Board* board;
        vector < Node* > children;
        Node* parent;
    };
    Node* root; // The first node that represents the current/first state of the game
    
    // Counter Variables for the Full Tree
    int totalGames;
    int totalXWins;
    int totalOWins;
    int totalDraws;
    int totalMoves;

    // -- Helper Functions --
    Node* addNode(Node* p, Board* b);
    void generateAllStates(Node* p, Board*& b);
    void removeAll(Node* p); // Recursive Function that removes all of the nodes in the entire t
    void deleteNode(Node*& n); // Recursive Function that removes all of a source node's childre
};

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
void DecisionTree::buildFullTree(){ // Construct the whole tree of possible states
    root = new Node;
    root->board = new Board;
    root->parent = NULL;

    totalGames = 0;

    

    // Generate the children listing possible placements of O on the board
    generateAllStates(root, root->board);
}

/***************************/
// -p- Private Methods -p- //
/***************************/
void DecisionTree::generateAllStates(Node* p, Board*& b){ // Create a tree of all possible future states from a specific node
    char charToAdd;
    vector<string> currentGrid = b->GetGrid();
    Board* futureBoard;
    if(b->getPlayerTurn() == b->O_TURN){
        charToAdd = 'O';
    } else if (b->getPlayerTurn() == b->X_TURN){
        charToAdd = 'X';
    }
    // Iterate through all possible char placements within the board
    for(int i = 0; i < currentStateString.length(); i++){
        if(currentStateString[i] == '-'){
            currentStateString[i] = charToAdd;
            futureBoard = new Board(currentStateString);
            // Generate State based on this possible future action
            addNode(p, futureBoard);
            currentStateString[i] = '-';
        }
    }

    for(int i = 0; i < p->children.size(); i++){
        generateAllStates(p->children.at(i), p->children.at(i)->board);
    }
    totalMoves++;
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