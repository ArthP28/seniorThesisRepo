#pragma once
#include <string>
#include "Board.h"

using namespace std;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

// For board class, store players as pointers


class Player{
    public:
        Player(string name, char symbol);
        Player(char symbol);
        void SetPlayersBoard(Board* _board);
        void dropChecker();
        void win();
        void loss();
        char GetSymbol();
        string GetName();
    private:
        int _numWins = 0;
        int _numLosses = 0;
        Board* _playersBoard;
        string _playerName = "Arthur";
        char _tokenSymbol;
};

Player::Player(string name, char symbol){
    _playerName = name;
    _tokenSymbol = symbol;
}

Player::Player(char symbol){
    _tokenSymbol = symbol;
}

void Player::SetPlayersBoard(Board* _board){
    _playersBoard = _board;
}

void Player::dropChecker(){
    string ESC = "\033";

    // Ask the user where to drop their checker
    cout << endl << "Select which column to place your checker." << endl;
    string playerInput;
    int colIndex;

    // Logic handling the validity of the user's input
    while(playerInput == ""){
        getline(cin, playerInput);

        if(playerInput[0] < 48 || playerInput[0] > 57){ // Check if the user's input is a number by checking its ASCII Value
            cout << ESC << "[A" << ESC << "[2KInvalid Input" << endl;
            sleep_for(milliseconds(500));
            playerInput = ""; // Input is reset back to "null" and the loop restarts.
            cout << ESC << "[A" << ESC << "[2K"; // Clears the error message
        } else {
            colIndex = stoi(playerInput);
            if(colIndex < 1 || colIndex > 7){ // If user types in a number not between 1 - 7, prompt user to try again
                cout << ESC << "[A" << ESC << "[2KInvalid Input" << endl;
                sleep_for(milliseconds(500));
                playerInput = ""; // Input is reset back to "null" and the loop restarts.
                cout << ESC << "[A" << ESC << "[2K"; // Clears the error message
            } else if(_playersBoard->isFull(colIndex - 1)) { // Else place the checker into the appropriate column
                cout << ESC << "[A" << ESC << "[2KColumn is full!" << endl;
                sleep_for(milliseconds(500));
                playerInput = ""; // Input is reset back to "null" and the loop restarts.
                cout << ESC << "[A" << ESC << "[2K"; // Clears the error message
            }
        }
    }

    system("clear"); // Clean up previously printed strings so that software output looks nice.
    //cout << ESC << "[2J\r";

    cout << _playerName << " drops a checker into column " << playerInput << "." << endl << endl; // This message primarily conveys that the action went through

    _playersBoard->printHeader();
    _playersBoard->placeChecker(colIndex - 1, _tokenSymbol);
    _playersBoard->printBoard();
}

void Player::win(){
    _numWins++;
}

void Player::loss(){
    _numLosses++;
}

char Player::GetSymbol(){
    return _tokenSymbol;
}

string Player::GetName(){
    return _playerName;
}

