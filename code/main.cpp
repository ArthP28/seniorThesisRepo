#include <iostream>
#include "Board.h"
using namespace std;

int main()
{
    Board _board('X', 'Y');
    _board.placeChecker(1, 4);
    _board.placeChecker(2, 4);
    _board.placeChecker(1, 4);
    _board.placeChecker(2, 4);
    _board.placeChecker(1, 4);
    _board.placeChecker(2, 4);
    _board.placeChecker(1, 3);
    _board.printBoard();

    return 0;
}