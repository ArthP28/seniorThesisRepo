#pragma once
#include <vector>

using namespace std;

bool CheckForFourInRow(int& connectCount, bool& hasWon);

class Board{
    struct Player{
        char symbol;
    };

    public:
        Board(char p1Symbol, char p2Symbol);
        bool placeChecker(int playerNum, int columnToPlace);
        bool checkWin(int checkerNum);
        void printBoard();
        void printHeader();

    private:
        Player _players[2];
        int _boardSpaces[7][6];
};


Board::Board(char p1Symbol, char p2Symbol){
    // Make sure that entire board starts completely empty (Full of 0s)
    for(int col = 0; col < 7; col++){
        for(int row = 0; row < 6; row++){
            _boardSpaces[col][row] = 0;
        }
    }
    _players[0].symbol = p1Symbol;
    _players[1].symbol = p2Symbol;
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

    return canBePlaced;
}

// FUTURE TODO: In > 4-in-a-row, Current Win Algorithm searches through checkers it has already searched
// If possible, find a way to ignore already searched checker rows
bool Board::checkWin(int checkerNum){
    bool hasWon = false;
    int connectCount = 0;
    // Scan the entire board for four in a row after each turn
    for(int row = 0; row < 6; row++){
        for(int col = 0; col < 7; col++){
            if(_boardSpaces[col][row] == checkerNum){ // When the loop finds the matching player checker, it then checks to see if there is another
                // Win searching algorithms check if there is four in a row
                // If there is, winning bool is set to true
                // If not, reset the connectCounter and go to the other search algorithm
                if(_boardSpaces[col+1][row] == checkerNum) { // 1. Horizontaly
                    connectCount+=2; // Two player checkers found so far
                    for(int c1 = 2; c1 < 4; c1++){
                        if(_boardSpaces[col + c1][row] == checkerNum){
                            connectCount++;
                        } else {
                            break;
                        }
                    }
                    if(CheckForFourInRow(connectCount, hasWon)){
                        cout << "Player " << checkerNum << " wins!" << endl;
                        break;
                    }
                }

                if(_boardSpaces[col][row+1] == checkerNum) { // 2. Vertically
                    connectCount+=2;
                    for(int r1 = 2; r1 < 4; r1++){
                        if(_boardSpaces[col][row + r1] == checkerNum){
                            connectCount++;
                        } else {
                            break;
                        }
                    }
                    if(CheckForFourInRow(connectCount, hasWon)){
                        cout << "Player " << checkerNum << " wins!" << endl;
                        break;
                    }
                }

                if(_boardSpaces[col-1][row+1] == checkerNum) { // 3. Diagonally (Left)
                    connectCount+=2;
                    for(int d = 2; d < 4; d++){
                        if(_boardSpaces[col - d][row + d] == checkerNum){ // Searching left and down
                            connectCount++;
                        } else {
                            break;
                        }
                    }
                    if(CheckForFourInRow(connectCount, hasWon)){
                        cout << "Player " << checkerNum << " wins!" << endl;
                        break;
                    }
                }

                if(_boardSpaces[col+1][row+1] == checkerNum) { // 3. Diagonally (Right)
                    connectCount+=2;
                    for(int d = 2; d < 4; d++){
                        if(_boardSpaces[col + d][row + d] == checkerNum){ // Searching right and down
                            connectCount++;
                        } else {
                            break;
                        }
                    }
                    if(CheckForFourInRow(connectCount, hasWon)){
                        cout << "Player " << checkerNum << " wins!" << endl;
                        break;
                    }
                }
            }
            if(hasWon){ // If there is a connect four, there is no further need to keep searching
                break;
            }
        }
    }
    
    return hasWon;
}

bool CheckForFourInRow(int& connectCount, bool& hasWon){
    if(connectCount == 4){
        cout << "Connect Four!" << endl;
        hasWon = true;
        return true;
    } else {
        connectCount = 0;
        return false;
    }
}

void Board::printBoard(){
    string ESC = "\033";
    for(int row = 0; row < 6; row++){
        for(int col = 0; col < 7; col++){
            if(_boardSpaces[col][row] == 1){ // Player 1 Checkers
                cout << ESC << "[41m" << _players[0].symbol << ESC << "[m ";
            } else if(_boardSpaces[col][row] == 2){ // Player 2 Checkers
                cout << ESC << "[44m" << _players[1].symbol << ESC << "[m ";
            } else { // Nothing
                cout << _boardSpaces[col][row] << " ";
            }
        }
        cout << endl;
    }
}

void Board::printHeader(){
    cout << "1 2 3 4 5 6 7" << endl;
    cout << "V V V V V V V" << endl;
    cout << "-------------" << endl;
}