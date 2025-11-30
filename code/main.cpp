#include <iostream>
#include <chrono>
#include <thread>
#include <unordered_set>
#include "Board.h"
#include "Player.h"
#include "DummyAI.h"
#include "QLearningAI.h"
#include "NeuralNetworkAI.h"

using namespace std;

// Menu Functions
void LogIn(); // For Later
void MainMenu();
void PlayerVsPlayer();
void PlayerVsAI();
//void ViewScores();
void Options();
// Game Functions
string SelectPlayer();
string MakeNewPlayer();
string ChooseExistingPlayer();
void SaveData(string p_name);
void LoadData();
void DeleteData();
bool UserFileExists(string p_name);
void SelectAI();
void PlayGame(Player* p1, Player* p2);
void PlayQGame(Player* p1, QLearningAI* p2, Board* _board);
void PlayNNGame(Player* p1, NeuralNetworkAI* p2, Board* _board);
string GetFileName(string p_name);
// If possible, after finishing main Q-Learning AI, create a function that saves all player data to a new file using outfile

unordered_map<string, Player*> ALL_PLAYERS; // Player objects are retrieved by name
//vector<Player*> ALL_PLAYERS;
QLearningAI* q_AI = new QLearningAI('B');
NeuralNetworkAI* nn_AI = new NeuralNetworkAI('B');

// ***NOTICE***
// The following code is to test the underlying logic of the Connect Four game works well.
// A later implementation will incorporate the meat of the software: The Q-Learning Algorithm for AI versus options.

int main()
{
    srand(time(0));
    // NeuralNetworkAI* _nn = new NeuralNetworkAI('B');
    // Board* _board = new Board("|||||||", 6);
    // _nn->SetPlayersBoard(_board, 2000000);
    // _nn->Test();
    //Player* p1 = new Player('R');
    // p1->SetPlayersBoard(_board);

    // Board* _board = new Board("||||", 4);
    // QLearningAI* p2 = new QLearningAI('B');
    // p2->SetPlayersBoard(_board);
    // p2->Train(2000000);


    // for(int i = 0; i < 10; i++){
    //     PlayNNGame(p1, _nn, _board);
    // }

    Player* _p2 = new Player("Emma Rochester", 'B');
    //DummyAI* _ai1 = new DummyAI('B');
    //ALL_PLAYERS.insert(make_pair(p1->GetName(), p1));
    ALL_PLAYERS.insert(make_pair(_p2->GetName(), _p2));

    //SaveData("Emma Rochester");
    //SaveData("Arthur");
    LoadData();

    MainMenu();
    
    // while(!ALL_PLAYERS.empty()){
    //     ALL_PLAYERS.
    //     delete ALL_PLAYERS.back();
    //     ALL_PLAYERS.back() = NULL;
    //     ALL_PLAYERS.pop_back();
    // }

    for(auto& p : ALL_PLAYERS){
        //ALL_PLAYERS.erase(p);
        delete p.second;
        p.second = NULL;
    }
    ALL_PLAYERS.clear();

    delete q_AI;
    q_AI = NULL;
    delete nn_AI;
    nn_AI = NULL;

    return 0;
}

void MainMenu(){ // Menu interface with various options
    string ESC = "\033";
    string _userInput;

    while(_userInput[0] != tolower('Q')){
        system("clear");
        cout << "Welcome to the ML Connect Four Software!" << endl << endl;
        cout << "MAIN MENU" << endl;
        cout << "Type in the corresponding number to get started." << endl << endl;
        cout << "[1] - Play Player vs. AI" << endl;
        cout << "[2] - Play Player vs. Player" << endl;
        cout << "[3] - View Scoreboard" << endl;
        cout << "[4] - Options" << endl;
        cout << "[Q] - Quit" << endl;
        _userInput = "";
        while(_userInput == ""){ // Program will wait for valid input
            getline(cin, _userInput);
            switch(_userInput[0]){
                case '1': // Proceeds to game where player competes against AI
                    PlayerVsAI();
                    break;
                case '2': // Proceeds to game where player competes with another human player
                    PlayerVsPlayer();
                    break;
                case '3': // Proceeds to screen where user can view all play records of both human and machine players
                    //ViewScores();
                    break;
                case '4': // Proceeds to Options Menu where user can change player data
                    Options();
                    break;
                case 'Q': // Quits the application
                    cout << "See you soon!" << endl;
                    break;
                case 'q': // Quits the application
                    cout << "See you soon!" << endl;
                    break;
                default: // Any other input is invalid
                    cout << ESC << "[A" << ESC << "[2KInvalid Input!" << endl;
                    sleep_for(milliseconds(500));
                    _userInput = ""; // Input is reset back to "null" and the loop restarts.
                    cout << ESC << "[A" << ESC << "[2K"; // Clears the error message
            }
        }
    }

}

void PlayerVsPlayer(){
    system("clear");

    // Prompt Players to select their profiles
    cout << "Player 1" << endl;
    string p1_Name = SelectPlayer();
    string p2_Name = "";
    while(p2_Name == ""){
        system("clear");
        cout << "Player 2" << endl;
        p2_Name = SelectPlayer();
        if(p2_Name == p1_Name){
            cout << "Player 1 is already using this account. Please select a different name!" << endl;
            cout << "Type in any key to continue" << endl;
            getline(cin, p2_Name);
            p2_Name = "";
        }
    }

    Player* p1 = ALL_PLAYERS.at(p1_Name);
    Player* p2 = ALL_PLAYERS.at(p2_Name);

    cout << "Let's play PvP Connect Four!" << endl << endl;
    string affirmationSignal = "y";
    while(tolower(affirmationSignal[0]) == 'y'){ // This function goes on as long as the user wants it to go
        PlayGame(p1, p2);
        cout << "Would you like to play again?" << endl << 
        "[y] = YES\n[n] = NO" << endl;
        getline(cin, affirmationSignal);
        system("clear");
    }

    // Save both players results to text files
    SaveData(p1->GetName());
    SaveData(p2->GetName());
}

void PlayerVsAI(){
    system("clear");
    // Board* _board = new Board("|||||", 4);
    // Player* p1 = ALL_PLAYERS.at(0);
    // QLearningAI* p2 = new QLearningAI('B');
    // p1->SetPlayersBoard(_board);
    // p2->SetPlayersBoard(_board);
    // p2->Train(2000000);
    // cout << "Let's play PvAI Connect Four!" << endl << endl;
    // string affirmationSignal = "y";
    
    // while(tolower(affirmationSignal[0]) == 'y'){ // This function goes on as long as the user wants it to go
    //     PlayQGame(ALL_PLAYERS.at(0), p2, _board);
    //     cout << "Would you like to play again?" << endl << 
    //     "[y] = YES\n[n] = NO" << endl;
    //     getline(cin, affirmationSignal);
    //     system("clear");
    // }
    // delete _board;
    // _board = NULL;
    // p1->RemovePlayersBoard();
    // p2->RemovePlayersBoard();
    // delete p2;
    // p2 = NULL;


}

// void ViewScores(){
//     system("clear");
//     cout << "Player Records" << endl;
//     for(int i = 0; i < ALL_PLAYERS.size(); i++){
//         cout << (i + 1) << ": "; ALL_PLAYERS.at(i)->viewPlayRecord(); cout << endl;
//     }
//     // cout << endl << "AI Records" << endl;
//     // for(int i = 0; i < ALL_AI_MODELS.size(); i++){
//     //     cout << (i + 1) << ": "; ALL_AI_MODELS.at(i)->viewPlayRecord(); cout << endl;
//     // }
//     string _userInput = "";
//     cout << "Press any key to return to the menu." << endl;
//     getline(cin, _userInput);
// }

void Options(){
    system("clear");
    cout << "Options to be added!" << endl;
    // Load Player Data from File
    // Delete Player Data
    // Modify AI training data
    // Reset NN Training data
    string _userInput = "";
    cout << "Press any key to return to the menu." << endl;
    getline(cin, _userInput);
}

string SelectPlayer(){
    string ESC = "\033";

    cout << "Press [1] to create a new player profile or..." << endl;
    cout << "Press [2] to choose an existing profile." << endl;
    string _userInput = "";
    while(_userInput == ""){ // Program will wait for valid input
        getline(cin, _userInput);
        switch(_userInput[0]){
            case '1': // Proceeds to game where player competes against AI
                _userInput = MakeNewPlayer();
                break;
            case '2': // Proceeds to game where player competes with another human player
                _userInput = ChooseExistingPlayer();
                break;
            default: // Any other input is invalid
                cout << ESC << "[A" << ESC << "[2KInvalid Input!" << endl;
                sleep_for(milliseconds(500));
                _userInput = ""; // Input is reset back to "null" and the loop restarts.
                cout << ESC << "[A" << ESC << "[2K"; // Clears the error message
        }
    }

    return _userInput;
}

string MakeNewPlayer(){
    string ESC = "\033";
    system("clear");
    // Prompt the user to type in their name
    cout << "Type in your name..." << endl;
    string _userName = "";
    while(_userName == ""){ // Program will wait for valid input
        getline(cin, _userName);
        if(ALL_PLAYERS.find(_userName) == NULL){ // Player does not exist with that name
            Player* new_player = new Player(_userName);
            ALL_PLAYERS.insert(make_pair(_userName, new_player));
            cout << "Your profile is now ready!" << endl;
            sleep_for(milliseconds(3000));
        } else { // Player DOES exist with that name. Ask user to try again
            cout << "Sorry, but an account already exists with that username. Cannot proceed!" << endl;
            cout << "It helps to use your last name or some other identifier." << endl;
            cout << "Press any key to try again." << endl;
            getline(cin, _userName);
            for(int i = 0; i < 5; i++){
                cout << ESC << "[A" << ESC << "[2K"; // Clears the error message
            }
            _userName = "";
        }
    }

    return _userName; // The user's inputted name will be returned so that the account will be accessed later
}

string ChooseExistingPlayer(){
    string ESC = "\033";
    system("clear");
    for(auto& p : ALL_PLAYERS){
        cout << "| " << p.first << " ";
    }
    cout << "|" << endl;
    // Prompt the user to type in their name
    cout << "Select a player..." << endl;
    string _userName = "";
    while(_userName == ""){ // Program will wait for valid input
        getline(cin, _userName);
        if(ALL_PLAYERS.find(_userName) == NULL){ // Player DOES exist with that name. Ask user to try again
            cout << "Player not found" << endl;
            cout << "Would you like to create a new profile? [y/n]" << endl;
            string yesno;
            getline(cin, yesno);
            if(tolower(yesno[0]) == 'y'){
                _userName = MakeNewPlayer();
            } else {
                for(int i = 0; i < 4; i++){
                    cout << ESC << "[A" << ESC << "[2K"; // Clears the error message
                }
                _userName = "";
            }
        }
    }

    return _userName; // The user's inputted name will be returned so that the account will be accessed later
}

void SaveData(string p_name){
    if(ALL_PLAYERS.find(p_name) != NULL){
        Player* p = ALL_PLAYERS.at(p_name);
        string fileName = GetFileName(p_name);
        ofstream PlayerData; PlayerData.open(fileName);
        // Save name, num games played, num wins, num losses
        PlayerData << p->GetName() << "\n";
        PlayerData << p->GetGamesPlayed() << "\n";
        PlayerData << p->GetWins() << "\n";
        PlayerData << p->GetLosses() << "\n";
        PlayerData.close();

        cout << p->GetName() << "'s records saved!" << endl;
    } else {
        throw "Account with that name not found";
    }
}

void LoadData(){
    system("clear");
    system("ls PlayerData");
    cout << "\nType one of the txt files to load the data for that player" << endl << endl;
    string userInput = "";
    while(userInput == ""){
        getline(cin, userInput);
        string fileName = "PlayerData/" + userInput;
        ifstream inFile; inFile.open(fileName);
        if(inFile.good()){
            vector<string> p_data;
            string curr_data;
            while(getline(inFile, curr_data)){
                p_data.push_back(curr_data);
            }
            string name = p_data.at(0); int games = stoi(p_data.at(1)); int wins = stoi(p_data.at(2)); int losses = stoi(p_data.at(3));
            Player* p = new Player(name);
            p->LoadRecords(wins, losses, games);
            ALL_PLAYERS.insert(make_pair(name, p));
            cout << name << "'s profile successfully loaded!" << endl;
            sleep_for(milliseconds(3000));
        } else {
            cout << "File name cannot be found." << endl;
            userInput = "";
        }
    }

}

void DeleteData(){
    system("clear");
    system("ls PlayerData");
    cout << "\nType one of the txt files to delete the data of that player" << endl << endl;
    string userInput = "";
    while(userInput == ""){
        getline(cin, userInput);
        string fileName = "PlayerData/" + userInput;
        ifstream inFile; inFile.open(fileName);
        if(inFile.good()){
            string cmd_string = "ls " + fileName;
            const char* cmd = cmd_string.c_str();
            system(cmd);
            cout << "Data successfully deleted!" << endl;
            sleep_for(milliseconds(3000));
        } else {
            cout << "File name cannot be found." << endl;
            userInput = "";
        }
    }
}

void PlayQGame(Player* p1, QLearningAI* p2, Board* _board){

    // Actual game begins. Loops as long as no one wins
    Board::BOARD_STATE _currState = Board::BOARD_STATE::INCOMPLETE;
    while(_currState == Board::BOARD_STATE::INCOMPLETE){
        if(_board->getNextTurn() == Board::PLAYER_TURN::P1){
            cout << p1->GetName() << "'s turn!" << endl;
            p1->dropChecker();
            //_currState = _board->checkWin(p1->GetSymbol());
        } else if (_board->getNextTurn() == Board::PLAYER_TURN::P2){
            cout << p2->GetName() << "'s turn!" << endl;
            p2->dropChecker();
            //_currState = _board->checkWin(p2->GetSymbol());
        }
        for(int i = 0; i <= _board->GetWidth() * 4; i++){
            cout << "-";
        }
        cout << "\n" << endl;
        _currState = _board->getCurrentState();
    }

    _board->printHeader();
    _board->printBoard();
    cout << endl;

    if(_currState == Board::BOARD_STATE::P1_WIN){
        cout << p1->GetName() << " Wins!" << endl;
        p1->win();
        p2->loss();
    } else if(_currState == Board::BOARD_STATE::P2_WIN){
        cout << p2->GetName() << " Wins!" << endl;
        p2->win();
        p1->loss();
    } else if(_currState == Board::BOARD_STATE::DRAW){
        cout << "Incredible! It's a draw!" << endl;
    }

    _board->clearBoard();
}

void PlayNNGame(Player* p1, NeuralNetworkAI* p2, Board* _board){

    // Actual game begins. Loops as long as no one wins
    Board::BOARD_STATE _currState = Board::BOARD_STATE::INCOMPLETE;
    while(_currState == Board::BOARD_STATE::INCOMPLETE){
        if(_board->getNextTurn() == Board::PLAYER_TURN::P1){
            cout << p1->GetName() << "'s turn!" << endl;
            p1->dropChecker();
            //_currState = _board->checkWin(p1->GetSymbol());
        } else if (_board->getNextTurn() == Board::PLAYER_TURN::P2){
            cout << p2->GetName() << "'s turn!" << endl;
            p2->dropChecker();
            //_currState = _board->checkWin(p2->GetSymbol());
        }
        for(int i = 0; i <= _board->GetWidth() * 4; i++){
            cout << "-";
        }
        cout << "\n" << endl;
        _currState = _board->getCurrentState();
    }

    _board->printHeader();
    _board->printBoard();
    cout << endl;

    if(_currState == Board::BOARD_STATE::P1_WIN){
        cout << p1->GetName() << " Wins!" << endl;
        p1->win();
        p2->loss();
    } else if(_currState == Board::BOARD_STATE::P2_WIN){
        cout << p2->GetName() << " Wins!" << endl;
        p2->win();
        p1->loss();
    } else if(_currState == Board::BOARD_STATE::DRAW){
        cout << "Incredible! It's a draw!" << endl;
    }

    _board->clearBoard();
}

void PlayGame(Player* p1, Player* p2){
    p1->SetSymbol('R');
    p2->SetSymbol('B');
    Board* _board = new Board();
    _board->firstTurn();
    p1->SetPlayersBoard(_board);
    p2->SetPlayersBoard(_board);

    // Actual game begins. Loops as long as no one wins
    Board::BOARD_STATE _currState = Board::BOARD_STATE::INCOMPLETE;
    while(_currState == Board::BOARD_STATE::INCOMPLETE){
        if(_board->getNextTurn() == Board::PLAYER_TURN::P1){
            cout << p1->GetName() << "'s turn!" << endl;
            p1->dropChecker();
            _currState = _board->checkWin(p1->GetSymbol());
        } else if (_board->getNextTurn() == Board::PLAYER_TURN::P2){
            cout << p2->GetName() << "'s turn!" << endl;
            p2->dropChecker();
            _currState = _board->checkWin(p2->GetSymbol());
        }
        for(int i = 0; i <= _board->GetWidth() * 4; i++){
            cout << "-";
        }
        cout << "\n" << endl;
    }

    _board->printHeader();
    _board->printBoard();
    cout << endl;

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
    p1->RemovePlayersBoard();
    p2->RemovePlayersBoard();
}

string GetFileName(string p_name){
    string p_name_with_underscore = p_name;
    for(char& c : p_name_with_underscore){
        if(c == ' '){
            c = '_';
        }
    }
    string fileName = "PlayerData/" + p_name_with_underscore;
    fileName += "_PlayerData.txt";

    return fileName;
}