#pragma once
#include <vector>
using namespace std;

bool CheckForFourInRow(int& connectCount);

class Board{
    
    public:
        enum PLAYER_TURN{
            P1,
            P2
        };

        enum BOARD_STATE{
            INCOMPLETE,
            P1_WIN,
            P2_WIN,
            DRAW
        };

        Board(int w, int h);
        Board(string g_string, int h);
        Board(vector<string> g);
        Board();

        void placeChecker(int column, char checkerToDrop);
        Board::BOARD_STATE checkWin(char checker);
        Board::BOARD_STATE getCurrentState();
        void printBoard();
        void printHeader();
        PLAYER_TURN getNextTurn();
        bool isFull(int col);
        bool boardFilled() { return countAllCheckers() == _boardHeight * _boardWidth; };
        int GetWidth() { return _boardWidth; };
        int GetHeight() { return _boardHeight; };
        vector<string> GetGrid() { return _grid; };
        PLAYER_TURN getCurrentTurn(){ return _currTurn; };
        void setCurrentTurn(PLAYER_TURN _turn){ _currTurn = _turn; };
        char getEmptyChar(){ return _empty; };
        void firstTurn();
        string boardToString();
        void clearBoard();
    private:
        vector<string> _grid;
        int _boardWidth = 0;
        int _boardHeight = 0;
        char _empty = '0';
        Board::PLAYER_TURN _currTurn;
        void initializeGrid();
        int countAllCheckers();

        // Helper Search Methods
        bool searchHorizontally(char checker, int col, int row, int count);
        bool searchVertically(char checker, int col, int row, int count);
        bool searchRightDiagonally(char checker, int col, int row, int count);
        bool searchLeftDiagonally(char checker, int col, int row, int count);

        bool inBounds(int col, int row);
};

Board::Board(int w, int h){ // Make a new blank board of a custom width and height
    if(w < 4 || h < 4){
        throw runtime_error("Board must at least be 4x4");
    }
    _boardWidth = w;
    _boardHeight = h;

    initializeGrid();
}

Board::Board(string g_string, int h){ // Convert to a board of custom width and height from a string
    vector<string> g;

    _boardHeight = h;
    for(char letter : g_string){
        if(letter == '|'){
            _boardWidth++;
        }
    }
    if(_boardWidth < 4 || _boardHeight < 4){
        throw runtime_error("Board must at least be 4x4");
    }

    // Append all checker characters into each new grid column generated
    for(int i = 0; i < _boardWidth; i++){
        string newCol = "";
        for(int j = 0; j < _boardHeight; j++){
            if(g_string[j] == '|'){
                break;
            }
            if(g_string[j] != 'R' && g_string[j] != 'B' && g_string[j] != _empty){
                throw runtime_error("Invalid Character Detected!");
            }
            newCol+=g_string[j];
        }
        // Calculate Remainder and fill rest with empty chars
        int r = _boardHeight - newCol.length();
        if(r != 0){
            string remainderString(r, _empty);
            newCol+=remainderString;
        }
        g.push_back(newCol);
        g_string = g_string.substr(g_string.find('|')+1);
    }

    _grid = g;
}

Board::Board(vector<string> g){ // Make a board based on an existing one
    _boardWidth = g.size();
    _boardHeight = g.at(0).size();
    if(_boardWidth < 4 || _boardHeight < 4){
        throw runtime_error("Board must at least be 4x4");
    }

    for(string col : g){
        if(col.size() != _boardHeight){
            throw runtime_error("All Board Columns must be equal in size");
        }
    }
    _grid = g;
}

Board::Board(){ // Make a default board
    _boardWidth = 7;
    _boardHeight = 6;

    initializeGrid();
}

Board::PLAYER_TURN Board::getNextTurn(){
    // if(_currTurn == NULL){
    //     firstTurn();
    // }
    // else if(_currTurn == PLAYER_TURN::P1){
    //     _currTurn = PLAYER_TURN::P2;
    //     return PLAYER_TURN::P2;
    // } else if (_currTurn == PLAYER_TURN::P2){
    //     _currTurn = PLAYER_TURN::P1;
    //     return PLAYER_TURN::P1;
    // }

    PLAYER_TURN retVal;

    int numRsAndBs = 0;

    for(int col = 0; col < _boardWidth; col++){
        for(int row = 0; row < _boardHeight; row++){
            if (_grid.at(col)[row] == 'R' || _grid.at(col)[row] == 'B')
            {
                numRsAndBs++;
            }
        }
    }

    if (numRsAndBs % 2 == 1)
    {
        retVal = PLAYER_TURN::P2;
    }
    else
    {
        retVal = PLAYER_TURN::P1;
    }

    return retVal;
}

void Board::placeChecker(int column, char checkerToDrop){ // This method returns a bool so that the main software displays a warning message about overfilling one column
    if(checkerToDrop != NULL){
        for(int bottom = 0; bottom < _boardHeight; bottom++){
            if(_grid.at(column)[bottom] == _empty){
                _grid.at(column)[bottom] = checkerToDrop;
                break;
            } else if (_grid.at(column)[_boardHeight - 1] != _empty){
                cout << "Col " << column << ": full" << endl;
            }
        }
    }
}

// FUTURE TODO: In > 4-in-a-row, Current Win Algorithm searches through checkers it has already searched
// If possible, find a way to ignore already searched checker rows
Board::BOARD_STATE Board::checkWin(char checker){
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
                            hasWon = true;
                            break;
                        }
                    }
                }

                if(inBounds(col, row+1)){
                    if(_grid.at(col)[row+1] == checker) { // 2. Vertically
                        if(searchVertically(checker, col, row+1, connectCount+2)){
                            hasWon = true;
                            break;
                        }
                    }
                }

                if(inBounds(col-1, row+1)){
                    if(_grid.at(col-1)[row+1] == checker) { // 3. Diagonally (Left)
                        if(searchLeftDiagonally(checker, col-1, row+1, connectCount+2)){
                            hasWon = true;
                            break;
                        }
                    }
                }

                if(inBounds(col+1, row+1)){
                    if(_grid.at(col+1)[row+1] == checker) { // 3. Diagonally (Right)
                        if(searchRightDiagonally(checker, col+1, row+1, connectCount+2)){
                            hasWon = true;
                            break;
                        }
                    }
                }

            }
        }
    }
    if(hasWon){
        if(checker == 'R'){
            return BOARD_STATE::P1_WIN;
        } else if(checker == 'B'){
            return BOARD_STATE::P2_WIN;
        }
    }
    return BOARD_STATE::INCOMPLETE;
}

Board::BOARD_STATE Board::getCurrentState(){
    if(checkWin('R')){
        return Board::BOARD_STATE::P1_WIN;
    } else if (checkWin('B')){
        return Board::BOARD_STATE::P2_WIN;
    } else if (boardFilled()){
        return BOARD_STATE::DRAW;
    }
    return Board::BOARD_STATE::INCOMPLETE;
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
        return true;
    } else {
        connectCount = 0;
        return false;
    }
}

void Board::printBoard(){
    string ESC = "\033";
    for(int row = _boardHeight - 1; row >= 0; row--){
        for(int col = 0; col < _boardWidth; col++){
            cout << "|";
            if(_grid.at(col)[row] == 'R'){ // Player 1 Checkers
                cout << ESC << "[41m R " << ESC << "[m";
            } else if(_grid.at(col)[row] == 'B'){ // Player 2 Checkers
                cout << ESC << "[44m B " << ESC << "[m";
            } else { // Nothing
                cout << " " << _grid.at(col)[row] << " ";
            }
        }
        cout << "|" << endl;
        if(row > 0){
            for(int w = 0; w <= _boardWidth * 4; w++){
                if(w % 4 == 0){
                    cout << "+";
                } else {
                    cout << "-";
                }
            }
        }
        cout << endl;
    }
}

bool Board::isFull(int col){
    // Since a column is only full if the checkers are stacked all the way to the top,
    // only check if there is a checker at the top-most spot on the grid.
    return _grid.at(col)[_boardHeight - 1] != _empty;
}

void Board::printHeader(){
    for(int col = 0; col < _boardWidth; col++){
        cout << "  " << (col + 1) << " ";
    }
    cout << " " << endl;
    for(int col = 0; col < _boardWidth; col++){
        cout << "  V ";
    }
    cout << " " << endl;
}

void Board::initializeGrid(){
    _grid.resize(_boardWidth);
    for(int i = 0; i < _grid.size(); i++){
        string col(_boardHeight, _empty);
        _grid.at(i) = col;
    }
}

void Board::firstTurn(){
    int randomIndex = (rand() % 2) + 1;
    if(randomIndex == 1){
        _currTurn = Board::PLAYER_TURN::P1;
    } else if (randomIndex == 2){
        _currTurn = Board::PLAYER_TURN::P2;
    }
}

int Board::countAllCheckers(){
    int numCheckers = 0;
    for(int row = 0; row < _boardHeight; row++){
        for(int col = 0; col < _boardWidth; col++){
            if(_grid.at(col)[row] != _empty){
                numCheckers++;
            }
        }
    }
    return numCheckers;
}

string Board::boardToString(){
    string _boardString = "";
    for(string col : _grid){
        for(int i = 0; i < _boardHeight; i++){
            if(col[i] == _empty){
                break;
            }
            _boardString += col[i];
        }
        _boardString += '|';
    }
    return _boardString;
}

void Board::clearBoard(){
    for(string& col : _grid){
        col = string(_boardHeight, _empty);
    }
}