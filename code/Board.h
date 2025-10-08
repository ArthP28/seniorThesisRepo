#pragma once
#include <vector>

using namespace std;

bool CheckForFourInRow(int& connectCount);

class Board{
    struct Player{
        char symbol;
    };

    
    public:
        enum PLAYER_TURN{
            P1,
            P2
        };

        enum BOARD_STATE{
            INCOMPLETE,
            P1_WIN,
            P2_WIN
        };

        Board(int w, int h, char p1, char p2);
        Board(int w, int h);
        Board(char p1, char p2);
        Board();

        bool dropChecker(int column, PLAYER_TURN _currPlayerTurn);

        bool placeChecker(int playerNum, int columnToPlace);
        bool checkWin(char checker);
        void printBoard();
        void printHeader();
        PLAYER_TURN getPlayerTurn();
    private:
        Player _players[2];
        vector<string> _grid;
        int _boardSpaces[7][6];
        int _boardWidth;
        int _boardHeight;
        char _p1Checker;
        char _p2Checker;
        char _empty = '0';
        void initializeGrid();

        // Helper Search Methods
        bool searchHorizontally(char checker, int col, int row, int count);
        bool searchVertically(char checker, int col, int row, int count);
        bool searchRightDiagonally(char checker, int col, int row, int count);
        bool searchLeftDiagonally(char checker, int col, int row, int count);

        bool inBounds(int col, int row);
};

Board::Board(int w, int h, char p1, char p2){
    _boardWidth = w;
    _boardHeight = h;

    _p1Checker = p1;
    _p2Checker = p2;

    initializeGrid();
}

Board::Board(int w, int h){
    _boardWidth = w;
    _boardHeight = h;

    _p1Checker = '1';
    _p2Checker = '2';

    initializeGrid();
}

Board::Board(char p1, char p2){
    _boardWidth = 7;
    _boardHeight = 6;

    _p1Checker = p1;
    _p2Checker = p2;

    initializeGrid();
}

Board::Board(){
    _boardWidth = 7;
    _boardHeight = 6;

    _p1Checker = '1';
    _p2Checker = '2';

    initializeGrid();
}

Board::PLAYER_TURN Board::getPlayerTurn(){
    PLAYER_TURN _retval;
    int numCheckers = 0;

    for(string col : _grid){
        for(int i = 0; i < col.length(); i++){
            if(col[i] == _p1Checker || col[i] == _p2Checker){
                numCheckers++;
            }
        }
    }

    if(numCheckers % 2 == 1){
        _retval = PLAYER_TURN::P2;
    } else if (numCheckers % 2 == 0){
        _retval = PLAYER_TURN::P1;
    }

    return _retval;
}

bool Board::dropChecker(int column, PLAYER_TURN _currPlayerTurn){ // This method returns a bool so that the main software displays a warning message about overfilling one column
    bool canBePlaced = false;

    char _checkerToDrop;
    if(_currPlayerTurn == PLAYER_TURN::P1){
        _checkerToDrop = _p1Checker;
    } else if(_currPlayerTurn == PLAYER_TURN::P2){
        _checkerToDrop = _p2Checker;
    }

    if(_checkerToDrop != NULL){
        for(int bottom = _boardHeight; bottom >= 0; bottom--){
            if(_grid.at(column)[bottom] == _empty){
                _grid.at(column)[bottom] = _checkerToDrop;
                canBePlaced = true;
                break;
            }
        }
    }

    return canBePlaced;
}

// FUTURE TODO: In > 4-in-a-row, Current Win Algorithm searches through checkers it has already searched
// If possible, find a way to ignore already searched checker rows
bool Board::checkWin(char checker){
    bool hasWon = false;
    int connectCount = 0;
    // Scan the entire board for four in a row after each turn
    for(int row = 0; row < _boardHeight; row++){
        for(int col = 0; col < _boardWidth; col++){
            if(_grid.at(col)[row] == checker){ // When the loop finds the matching player checker, it then checks to see if there is another
                // Win searching algorithms check if there is four in a row
                // If there is, winning bool is set to true
                // If not, reset the connectCounter and go to the other search algorithm
                if(inBounds(col+1, row)){
                    if(_grid.at(col+1)[row] == checker) { // 1. Horizontaly
                        if(searchHorizontally(checker, col+1, row, connectCount+2)){
                            return true;
                        }
                    }
                }

                if(inBounds(col, row+1)){
                    if(_grid.at(col)[row+1] == checker) { // 2. Vertically
                        if(searchVertically(checker, col, row+1, connectCount+2)){
                            return true;
                        }
                    }
                }

                if(inBounds(col-1, row+1)){
                    if(_grid.at(col-1)[row+1] == checker) { // 3. Diagonally (Left)
                        if(searchLeftDiagonally(checker, col-1, row+1, connectCount+2)){
                            return true;
                        }
                    }
                }

                if(inBounds(col+1, row+1)){
                    if(_grid.at(col+1)[row+1] == checker) { // 3. Diagonally (Right)
                        if(searchRightDiagonally(checker, col+1, row+1, connectCount+2)){
                            return true;
                        }
                    }
                }

            }
        }
    }
    return false;
}

bool Board::inBounds(int col, int row){
    return (col >= 0 && row >= 0) && (col < _boardWidth && row < _boardHeight);
}

bool Board::searchHorizontally(char checker, int col, int row, int count){
    for(int c1 = 1; c1 <= 2; c1++){
        if(inBounds(col+c1, row)){
            if(_grid.at(col+c1)[row] == checker){
                count++;
            }
        } else {
            break;
        }
    }
    return (CheckForFourInRow(count));
}

bool Board::searchVertically(char checker, int col, int row, int count){
    for(int r1 = 1; r1 <= 2; r1++){
        if(inBounds(col, row+r1)){
            if(_grid.at(col)[row + r1] == checker){
                count++;
            }
        } else {
            break;
        }
    }
    return (CheckForFourInRow(count));
}

bool Board::searchRightDiagonally(char checker, int col, int row, int count){
    for(int d = 1; d <= 2; d++){
        if(inBounds(col+d, row+d)){
            if(_grid.at(col+d)[row + d] == checker){ // Searching right and down
                count++;
            }
        } else {
            break;
        }
    }
    return (CheckForFourInRow(count));
}

bool Board::searchLeftDiagonally(char checker, int col, int row, int count){
    for(int d = 1; d <= 2; d++){
        if(inBounds(col-d, row)){ // Searching left and down
            if(_grid.at(col-d)[row + d] == checker){ // Searching left and down
                count++;
            }
        } else {
            break;
        }
    }
    return (CheckForFourInRow(count));
}

bool CheckForFourInRow(int& connectCount){
    if(connectCount == 4){
        cout << "Connect Four!" << endl;
        return true;
    } else {
        connectCount = 0;
        return false;
    }
}

void Board::printBoard(){
    string ESC = "\033";
    for(int row = 0; row < _boardWidth; row++){
        for(int col = 0; col < _boardHeight; col++){
            if(_grid.at(col)[row] == _p1Checker){ // Player 1 Checkers
                cout << ESC << "[41m" << _p1Checker << ESC << "[m ";
            } else if(_grid.at(col)[row] == _p2Checker){ // Player 2 Checkers
                cout << ESC << "[44m" << _p2Checker << ESC << "[m ";
            } else { // Nothing
                cout << _grid.at(col)[row] << " ";
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

void Board::initializeGrid(){
    _grid.resize(_boardWidth);
    for(int i = 0; i < _grid.size(); i++){
        string col(_boardHeight, _empty);
        _grid.at(i) = col;
    }
}