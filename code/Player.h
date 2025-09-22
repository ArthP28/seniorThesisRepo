#pragma once

using namespace std;

class Player{
    public:
        Player(char Symbol) { _playerSymbol = Symbol; };
        char GetSymbol() { return _playerSymbol; };
    protected:
        char _playerSymbol;
};