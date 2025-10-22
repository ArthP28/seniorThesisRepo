#include <iostream>
#include <chrono>
#include <thread>
#include "Board.h"
#include "Player.h"
#include "DummyAI.h"

using namespace std;

// Menu Functions
void LogIn(); // For Later
void MainMenu();
void PlayerVsPlayer();
void PlayerVsAI();
void ViewScores();
void Options();
// Game Functions
void SelectPlayer();
void SelectAI();
void PlayGame(Player* p1, Player* p2);
// If possible, after finishing main Q-Learning AI, create a function that saves all player data to a new file using outfile

vector<Player*> ALL_PLAYERS;
vector<Player*> ALL_AI_MODELS;

// ***NOTICE***
// The following code is to test the underlying logic of the Connect Four game works well.
// A later implementation will incorporate the meat of the software: The Q-Learning Algorithm for AI versus options.

int main()
{
    srand(time(0));
    vector<string> _boardData = {
        "R00000", 
        "BR0000",
        "BRB000",
        "RBRB00",
        "RBR000",
        "BR0000",
        "R00000",
    };
    Board* _b = new Board(_boardData);
    _b->printBoard();
    // Player* _p1 = new Player('R');
    // Player* _p2 = new Player("Emma", 'B');
    // DummyAI* _ai1 = new DummyAI('B');
    // ALL_PLAYERS.push_back(_p1);
    // ALL_PLAYERS.push_back(_p2);
    // ALL_AI_MODELS.push_back(_ai1);

    // MainMenu();
    
    // while(!ALL_PLAYERS.empty()){
    //     delete ALL_PLAYERS.back();
    //     ALL_PLAYERS.back() = NULL;
    //     ALL_PLAYERS.pop_back();
    // }
    // while(!ALL_AI_MODELS.empty()){
    //     delete ALL_AI_MODELS.back();
    //     ALL_AI_MODELS.back() = NULL;
    //     ALL_AI_MODELS.pop_back();
    // }
    delete _b;
    _b = NULL;
    return 0;
}

void MainMenu(){ // Menu interface with various options
    string ESC = "\033";
    string _userInput;

    while(_userInput[0] != tolower('Q')){
        system("clear");
        cout << "Welcome to the ML Connect Four Software!" << endl;
        cout << "Type in the corresponding number to get started." << endl << endl;
        cout << "[1] - Play Player vs. AI" << endl;
        cout << "[2] - Play Player vs. Player" << endl;
        cout << "[3] - View Scoreboard" << endl;
        cout << "[4] - Options" << endl;
        cout << "[Q] - Quit" << endl;
        _userInput = "";
        while(_userInput == ""){ // Program will wait for valid input
            getline(cin, _userInput);
            switch(_userInput[0]){
                case '1': // Proceeds to game where player competes against AI
                    PlayerVsAI();
                    break;
                case '2': // Proceeds to game where player competes with another human player
                    PlayerVsPlayer();
                    break;
                case '3': // Proceeds to screen where user can view all play records of both human and machine players
                    ViewScores();
                    break;
                case '4': // Proceeds to Options Menu where user can change player data
                    Options();
                    break;
                case 'Q': // Quits the application
                    cout << "See you soon!" << endl;
                    break;
                case 'q': // Quits the application
                    cout << "See you soon!" << endl;
                    break;
                default: // Any other input is invalid
                    cout << ESC << "[A" << ESC << "[2KInvalid Input!" << endl;
                    sleep_for(milliseconds(500));
                    _userInput = ""; // Input is reset back to "null" and the loop restarts.
                    cout << ESC << "[A" << ESC << "[2K"; // Clears the error message
            }
        }
    }

}

void PlayerVsPlayer(){
    system("clear");
    cout << "Let's play PvP Connect Four!" << endl << endl;
    string affirmationSignal = "y";
    while(tolower(affirmationSignal[0]) == 'y'){ // This function goes on as long as the user wants it to go
        PlayGame(ALL_PLAYERS.at(0), ALL_PLAYERS.at(1));
        cout << "Would you like to play again?" << endl << 
        "[y] = YES\n[n] = NO" << endl;
        getline(cin, affirmationSignal);
        system("clear");
    }
}

void PlayerVsAI(){
    system("clear");
    cout << "Let's play PvAI Connect Four!" << endl << endl;
    string affirmationSignal = "y";
    while(tolower(affirmationSignal[0]) == 'y'){ // This function goes on as long as the user wants it to go
        PlayGame(ALL_PLAYERS.at(0), ALL_AI_MODELS.at(0));
        cout << "Would you like to play again?" << endl << 
        "[y] = YES\n[n] = NO" << endl;
        getline(cin, affirmationSignal);
        system("clear");
    }
}

void ViewScores(){
    system("clear");
    cout << "Player Records" << endl;
    for(int i = 0; i < ALL_PLAYERS.size(); i++){
        cout << (i + 1) << ": "; ALL_PLAYERS.at(i)->viewPlayRecord(); cout << endl;
    }
    cout << endl << "AI Records" << endl;
    for(int i = 0; i < ALL_AI_MODELS.size(); i++){
        cout << (i + 1) << ": "; ALL_AI_MODELS.at(i)->viewPlayRecord(); cout << endl;
    }
    string _userInput = "";
    cout << "Press any key to return to the menu." << endl;
    getline(cin, _userInput);
}

void Options(){
    system("clear");
    cout << "Options to be added!" << endl;
    string _userInput = "";
    cout << "Press any key to return to the menu." << endl;
    getline(cin, _userInput);
}

void PlayGame(Player* p1, Player* p2){
    Board::PLAYER_TURN _currTurn;
    int randomIndex = (rand() % 2) + 1;
    p1->SetSymbol('R');
    p2->SetSymbol('B');
    if(randomIndex == 1){
        _currTurn = Board::PLAYER_TURN::P1;
    } else if (randomIndex == 2){
        _currTurn = Board::PLAYER_TURN::P2;
    }
    Board* _board = new Board();
    p1->SetPlayersBoard(_board);
    p2->SetPlayersBoard(_board);

    // Actual game begins. Loops as long as no one wins
    Board::BOARD_STATE _currState = Board::BOARD_STATE::INCOMPLETE;
    while(_currState == Board::BOARD_STATE::INCOMPLETE){
        if(_currTurn == Board::PLAYER_TURN::P1){
            cout << p1->GetName() << "'s turn!" << endl;
            p1->dropChecker();
            _currState = _board->checkWin(p1->GetSymbol());
        } else if (_currTurn == Board::PLAYER_TURN::P2){
            cout << p2->GetName() << "'s turn!" << endl;
            p2->dropChecker();
            _currState = _board->checkWin(p2->GetSymbol());
        }
        _currTurn = _board->getNextTurn(_currTurn);
        for(int i = 0; i <= _board->GetWidth() * 4; i++){
            cout << "-";
        }
        cout << "\n" << endl;
    }

    _board->printHeader();
    _board->printBoard();
    cout << endl;

    if(_currState == Board::BOARD_STATE::P1_WIN){
        cout << p1->GetName() << " Wins!" << endl;
        p1->win();
        p2->loss();
    } else if(_currState == Board::BOARD_STATE::P2_WIN){
        cout << p2->GetName() << " Wins!" << endl;
        p2->win();
        p1->loss();
    }

    delete _board;
    _board = NULL;
    p1->SetPlayersBoard(NULL);
    p2->SetPlayersBoard(NULL);
}