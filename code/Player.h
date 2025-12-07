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
        Player(string name);
        Player(char symbol);
        ~Player();
        virtual void SetPlayersBoard(Board* _board);
        void RemovePlayersBoard();
        void SetSymbol(char symbol);
        virtual void dropChecker();
        void viewPlayRecord();
        void win();
        void loss();
        void tie();
        char GetSymbol();
        string GetName();
        Board* GetBoard(){ return _playersBoard; };
        int GetGamesPlayed(){ return _numGamesPlayed; };
        int GetWins(){ return _numWins; };
        int GetLosses(){ return _numLosses; };
        void LoadRecords(int wins, int losses, int games);
    protected:
        string _playerName = "Arthur";
    private:
        int _numWins = 0;
        int _numLosses = 0;
        int _numGamesPlayed = 0;
        Board* _playersBoard = NULL;
        char _tokenSymbol = ' ';
};
    
Player::Player(string name, char symbol){
    _playerName = name;
    _tokenSymbol = symbol;
}

Player::Player(string name){
    _playerName = name;
}

Player::Player(char symbol){
    _tokenSymbol = symbol;
}

Player::~Player(){
    if(_playersBoard != NULL){ // !FIX!
        delete _playersBoard;
        RemovePlayersBoard();
    }
}

void Player::SetPlayersBoard(Board* _board){
    _playersBoard = _board;
}

void Player::RemovePlayersBoard(){
    _playersBoard = NULL;
}

void Player::SetSymbol(char symbol){
    _tokenSymbol = symbol;
}

void Player::dropChecker(){
    string ESC = "\033";

    // Ask the user where to drop their checker
    cout << endl << "Select which column to place your checker." << endl << endl;
    _playersBoard->printHeader();
    _playersBoard->printBoard();
    cout << endl;
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
    _playersBoard->placeChecker(colIndex - 1, _tokenSymbol);
}

void Player::viewPlayRecord(){
    cout << _playerName << endl << endl;
    cout << "Games Played: " << _numGamesPlayed << endl;
    cout << "Games Won: " << _numWins << endl;
    cout << "Games Lost: " << _numLosses << endl;
    float ratio = 0.0f;
    if(_numGamesPlayed > 0){
        ratio = ((float)_numWins)/_numGamesPlayed;
    }
    cout << "Ratio: " << _numWins << ":" << _numLosses << " (" << ratio << ")" << endl;
}

void Player::win(){
    _numWins++;
    _numGamesPlayed++;
}

void Player::loss(){
    _numLosses++;
    _numGamesPlayed++;
}

void Player::tie(){
    _numGamesPlayed++;
}

char Player::GetSymbol(){
    return _tokenSymbol;
}

string Player::GetName(){
    return _playerName;
}

void Player::LoadRecords(int wins, int losses, int games){
    _numWins = wins;
    _numLosses = losses;
    _numGamesPlayed = games;
}

