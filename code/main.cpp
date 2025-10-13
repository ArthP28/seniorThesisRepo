#include <iostream>
#include <chrono>
#include <thread>
#include "Board.h"
#include "Player.h"
#include "DummyAI.h"

using namespace std;

void PlayGame(Player* p1, Player* p2);

// ***NOTICE***
// The following code is only a fraction of the overall ML Connect Four Software (The Player vs. Player Mode).
// This is to test that the underlying logic of the Connect Four game works well within the software.
// A later implementation will incorporate the meat of the software: The Q-Learning Algorithm for AI versus options.

int main()
{
    srand(time(0));
    Player* _p1 = new Player('R');
    DummyAI* _p2 = new DummyAI('B');
    cout << "Let's play Connect Four!" << endl << endl;
    string affirmationSignal = "y";
    while(tolower(affirmationSignal[0]) == 'y'){ // This function goes on as long as the user wants it to go
        PlayGame(_p1, _p2);
        cout << "Would you like to play again?" << endl << 
        "[y] = YES\n[n] = NO" << endl;
        getline(cin, affirmationSignal);
        system("clear");
    }
    cout << "See you soon!" << endl;

    delete _p2;
    delete _p1;
    _p1 = NULL;
    _p2 = NULL;
    return 0;
}

void PlayGame(Player* p1, Player* p2){
    Board::PLAYER_TURN _currTurn;
    int randomIndex = (rand() % 2) + 1;
    if(randomIndex == 1){
        _currTurn = Board::PLAYER_TURN::P1;
    } else if (randomIndex == 2){
        _currTurn = Board::PLAYER_TURN::P2;
    }
    Board* _board = new Board(p1->GetSymbol(), p2->GetSymbol());
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
}