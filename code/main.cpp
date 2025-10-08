#include <iostream>
#include <chrono>
#include <thread>
#include "Board.h"
using namespace std;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

int DetermineFirstPlayer();
void PlayGame(int firstPlayerIndex);

// ***NOTICE***
// The following code is only a fraction of the overall ML Connect Four Software (The Player vs. Player Mode).
// This is to test that the underlying logic of the Connect Four game works well within the software.
// A later implementation will incorporate the meat of the software: The Q-Learning Algorithm for AI versus options.

int main()
{
    Board _board;
    _board.dropChecker(3, _board.getPlayerTurn());
    _board.dropChecker(2, _board.getPlayerTurn());
    _board.dropChecker(2, _board.getPlayerTurn());
    _board.dropChecker(1, _board.getPlayerTurn());
    _board.dropChecker(2, _board.getPlayerTurn());
    _board.dropChecker(1, _board.getPlayerTurn());
    _board.dropChecker(1, _board.getPlayerTurn());
    _board.dropChecker(0, _board.getPlayerTurn());
    _board.dropChecker(1, _board.getPlayerTurn());
    _board.dropChecker(0, _board.getPlayerTurn());
    _board.dropChecker(0, _board.getPlayerTurn());
    _board.dropChecker(1, _board.getPlayerTurn());
    _board.dropChecker(0, _board.getPlayerTurn());
    _board.printBoard();
    _board.checkWin('1');
    /*
    srand(time(0));
    cout << "Let's play Connect Four!" << endl << endl;
    string affirmationSignal = "y";
    while(tolower(affirmationSignal[0]) == 'y'){ // This function goes on as long as the user wants it to go
        PlayGame(DetermineFirstPlayer());
        cout << "Would you like to play again?" << endl << 
        "[y] = YES\n[n] = NO" << endl;
        getline(cin, affirmationSignal);
        system("clear");
    }
    cout << "See you soon!" << endl;
    return 0;
    */
}
/*
void PlayGame(int firstPlayerIndex){
    Board _board('R', 'B'); // Parameters: Player 1 = RED, Player 2 = BLUE
    string ESC = "\033";
    int currentPlayerIndex = firstPlayerIndex;
    int colIndex;

    while(true){
        // First Print which Player is going as well as the current state of the board grid
        if(currentPlayerIndex == 1){
            cout << ESC << "[41m";
        } else if (currentPlayerIndex == 2){
            cout << ESC << "[44m";
        }
        cout << "Player " << currentPlayerIndex << "'s turn!" << ESC << "[m" << endl << endl;
        _board.printHeader();
        _board.printBoard();

        // Then ask the user where to drop their checker
        cout << endl << "Select which column to place your checker." << endl;
        string playerInput;

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
                } else if(!_board.placeChecker(currentPlayerIndex, colIndex - 1)) { // Else place the checker into the appropriate column
                    cout << ESC << "[A" << ESC << "[2KColumn is full!" << endl;
                    sleep_for(milliseconds(500));
                    playerInput = ""; // Input is reset back to "null" and the loop restarts.
                    cout << ESC << "[A" << ESC << "[2K"; // Clears the error message
                }
            }
            
        }

        system("clear"); // Clean up previously printed strings so that software output looks nice.
        //cout << ESC << "[2J\r";

        cout << "Player " << currentPlayerIndex << " drops a checker into column " << playerInput << "." << endl << endl; // This message primarily conveys that the action went through

        if(_board.checkWin(currentPlayerIndex)){ // Check if the current player has won
            break;
        } else {
            if((currentPlayerIndex + 1) > 2){ // Switch the player count to player 1 if player 2's turn has concluded
                currentPlayerIndex = 1;
            } else { // Otherwise if Player 1's turn has ended, switch to Player 2
                currentPlayerIndex++;
            }
        }
    }
    cout << endl << "Results" << endl << endl; // Display winning board grid
    _board.printBoard();
}

int DetermineFirstPlayer(){ // Decides who gets to go first. Is completely random for every game.
    int randomIndex = (rand() % 2) + 1;
    cout << "Player " << randomIndex << " goes first!" << endl << endl;
    return randomIndex;
}
*/