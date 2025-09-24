#pragma once

using namespace std;

class Board{
    public:
        Board();
        bool placeChecker(int playerNum, int columnToPlace);
        void checkWin();
        void printBoard();
    protected:
        int _boardSpaces[7][6];
};

Board::Board(){
    // Make sure that entire board starts completely empty (Full of 0s)
    for(int col = 0; col < 7; col++){
        for(int row = 0; row < 6; row++){
            _boardSpaces[col][row] = 0;
        }
    }
}

bool Board::placeChecker(int playerNum, int columnToPlace){
    bool canBePlaced = false;
    // Checker falls down specific spot and lands either on the bottom of the board or on top of another checker
    for(int bottomRow = 5; bottomRow >= 0; bottomRow--){
        if(_boardSpaces[columnToPlace][bottomRow] == 0){
            _boardSpaces[columnToPlace][bottomRow] = playerNum;
            canBePlaced = true;
            break;
        }
    }

    if(!canBePlaced){
        cout << "Invalid place to drop a checker!" << endl;
    }

    return canBePlaced;
}

void Board::checkWin(){
    // Scan the entire board for four in a row after each turn
    // 1. Horizontals
    // 2. Verticals
    // 3. Diagonals
}

void Board::printBoard(){
    for(int row = 0; row < 6; row++){
        for(int col = 0; col < 7; col++){
            cout << _boardSpaces[col][row] << " ";
        }
        cout << endl;
    }
}