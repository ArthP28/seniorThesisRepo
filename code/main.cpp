#include <iostream>
#include "Board.h"
using namespace std;

int main()
{
    Board _board('X', 'Y');
    _board.placeChecker(1, 5);
    _board.placeChecker(2, 4);
    _board.placeChecker(2, 3);
    _board.placeChecker(2, 2);

    _board.placeChecker(1, 4);
    _board.placeChecker(2, 3);
    _board.placeChecker(2, 2);

    _board.placeChecker(1, 3);
    _board.placeChecker(2, 2);
    _board.placeChecker(1, 2);

    _board.printBoard();
    if(_board.checkWin(1)){
        cout << "Player 1 Wins!" << endl;
    }
    if(_board.checkWin(2)){
        cout << "Player 2 Wins!" << endl;
    }

    return 0;
}