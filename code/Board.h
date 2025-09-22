#pragma once

using namespace std;

class Board{
    public:
        Board();
        void placeChecker(int spotToPlace);
    protected:
        int _boardSpaces[7][6];
};