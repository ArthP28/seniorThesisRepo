#pragma once
#include <iostream>
#include "Player.h"

using namespace std;

class DummyAI : public Player{
    public:
        DummyAI(string _name, char _symbol);
        DummyAI(char _symbol);
        void dropChecker() override;
};

DummyAI::DummyAI(string _name, char _symbol) : Player(_name, _symbol){
    Player::_playerName = _name;
}

DummyAI::DummyAI(char _symbol) : Player(_symbol){
    Player::_playerName = "Lily";
}

void DummyAI::dropChecker(){
    int randColIndex = rand() % GetBoard()->GetWidth();
    cout << GetName() << " drops a checker into column " << randColIndex << "." << endl << endl; // This message primarily conveys that the action went through
    GetBoard()->placeChecker(randColIndex, GetSymbol());
}