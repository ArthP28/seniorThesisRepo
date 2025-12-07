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
void MainMenu();
void PlayerVsPlayer();
void PlayerVsAI();
void ViewScores();
void Options();
void ManageQData();
void ManageNNData();
// Game Functions
string SelectPlayer();
string MakeNewPlayer();
string ChooseExistingPlayer();
void SaveData(string p_name);
void LoadData();
void SaveQData();
void LoadAndTrainQ();
void DeleteData();
bool UserFileExists(string p_name);
void SelectAI();
void PlayGame(Player* p1, Player* p2);
void PlayQGame(Player* p1, QLearningAI* p2, Board* _board);
void PlayNNGame(Player* p1, NeuralNetworkAI* p2, Board* _board);
string GetFileName(string p_name);
bool NN_Warning();
// If possible, after finishing main Q-Learning AI, create a function that saves all player data to a new file using outfile

unordered_map<string, Player*> ALL_PLAYERS; // Player objects are retrieved by name

QLearningAI* q_AI = new QLearningAI('B');
int q_TrainingEpochs = 1000000;
//int q_BoardDimensions[2] = {4, 4};
NeuralNetworkAI* nn_AI = new NeuralNetworkAI('B');
int nn_TrainingGames = 10000000;

// ***NOTICE***
// The following code is to test the underlying logic of the Connect Four game works well.
// A later implementation will incorporate the meat of the software: The Q-Learning Algorithm for AI versus options.

int main()
{
    srand(time(0));
    // Train Algorithms on boards
    
    Board* q_Board = new Board("||||", 4);
    q_AI->SetPlayersBoard(q_Board);
    q_AI->Train(q_TrainingEpochs);

    Board* nn_Board = new Board("|||||||", 6);
    nn_AI->SetPlayersBoard(nn_Board);
    nn_AI->Train(nn_TrainingGames);

    MainMenu();

    for(auto& p : ALL_PLAYERS){
        //ALL_PLAYERS.erase(p);
        delete p.second;
        p.second = NULL;
    }
    ALL_PLAYERS.clear();

    q_AI->RemovePlayersBoard();
    nn_AI->RemovePlayersBoard();
    delete q_Board;
    q_Board = NULL;
    delete nn_Board;
    nn_Board = NULL;
    delete q_AI;
    q_AI = NULL;
    delete nn_AI;
    nn_AI = NULL;

    return 0;
}

void MainMenu(){ // Menu interface with various options
    string ESC = "\033";
    string _userInput;

    while(tolower(_userInput[0]) != 'q'){
        system("clear");
        cout << ESC << "[4mWelcome to the ML Connect Four Software!" << ESC << "[24m" << endl << endl;
        cout << ESC << "[1;4mMAIN MENU" << ESC << "[0m" << endl;
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
                    ViewScores();
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
    string ESC = "\033";
    // Prompt Players to select their profiles
    cout << ESC << "[41mPlayer 1" << ESC << "[0m" << endl;
    string p1_Name = SelectPlayer();
    string p2_Name = "";
    while(p2_Name == ""){
        system("clear");
        cout << ESC << "[44mPlayer 2" << ESC << "[0m" << endl;
        p2_Name = SelectPlayer();
        if(p2_Name == p1_Name){
            cout << "Player 1 is already using this account. Please select a different name!" << endl;
            cout << "Type in any key to continue" << endl;
            getline(cin, p2_Name);
            p2_Name = "";
        }
    }

    Player* p1 = ALL_PLAYERS.at(p1_Name);
    p1->SetSymbol('R');
    Player* p2 = ALL_PLAYERS.at(p2_Name);
    p2->SetSymbol('B');

    cout << ESC << "[4mLet's play PvP Connect Four!" << ESC << "[0m" << endl << endl;
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
    string ESC = "\033";
    Board* gameBoard;
    string p1_Name = SelectPlayer();
    Player* p1 = ALL_PLAYERS.at(p1_Name);
    p1->SetSymbol('R');
    string _userInput = "";
    string affirmationSignal = "y";
    while(_userInput == ""){ // Program will wait for valid input
        cout << "Select which AI to play with." << endl;
        cout << "[1] - Q-Learning (4x4)" << endl;
        cout << "[2] - Neural Network (7x6)" << endl;
        getline(cin, _userInput);
        switch(_userInput[0]){
            case '1': // Proceeds to game where player competes against AI
                cout << ESC << "[4mLet's play Q-Learning Connect Four!" << ESC << "[0m" << endl << endl;
                while(tolower(affirmationSignal[0]) == 'y'){ // This function goes on as long as the user wants it to go
                    gameBoard = q_AI->GetBoard();
                    p1->SetPlayersBoard(gameBoard);
                    PlayQGame(p1, q_AI, gameBoard);
                    cout << "Would you like to play again?" << endl << 
                    "[y] = YES\n[n] = NO" << endl;
                    getline(cin, affirmationSignal);
                    system("clear");
                }
                // Save player results to text files
                SaveData(p1->GetName());
                p1->RemovePlayersBoard();
                break;
            case '2': // Proceeds to game where player competes with another human player
                if(NN_Warning()){
                    cout << ESC << "[4mLet's play Neural Network Connect Four!" << ESC << "[0m" << endl << endl;
                    while(tolower(affirmationSignal[0]) == 'y'){ // This function goes on as long as the user wants it to go
                        gameBoard = nn_AI->GetBoard();
                        p1->SetPlayersBoard(gameBoard);
                        PlayNNGame(p1, nn_AI, gameBoard);
                        cout << "Would you like to play again?" << endl << 
                        "[y] = YES\n[n] = NO" << endl;
                        getline(cin, affirmationSignal);
                        system("clear");
                    }
                    // Save player results to text files
                    SaveData(p1->GetName());
                    p1->RemovePlayersBoard();
                } else {
                    _userInput = "";
                }
                break;
            default: // Any other input is invalid
                cout << ESC << "[A" << ESC << "[2KInvalid Input!" << endl;
                sleep_for(milliseconds(500));
                _userInput = ""; // Input is reset back to "null" and the loop restarts.
                cout << ESC << "[A" << ESC << "[2K"; // Clears the error message
        }
    }
}

void ViewScores(){
    system("clear");
    string ESC = "\033";
    cout << ESC << "[1;4mPlayer Records" << ESC << "[0m" << endl; // Cycle through all player scores
    if(ALL_PLAYERS.empty()){
        cout << "No Player Data Found!" << endl << endl;
    } else {
        int i = 1; // i is being used as a label, so its starting value is 1
        for(auto& p_object : ALL_PLAYERS){
            Player* p = p_object.second;
            cout << i << ": "; p->viewPlayRecord(); cout << endl;
            i++;
        }
        cout << endl;
    }

    // Then display the score data for the Q-Learning AI and the Neural Network AI
    cout << ESC << "[1;4mQ Records" << ESC << "[0m" << endl;
    q_AI->viewPlayRecord(); cout << endl;
    cout << endl;

    cout << ESC << "[1;4mNeural Network Records" << ESC << "[0m" << endl;
    nn_AI->viewPlayRecord(); cout << endl;
    cout << endl;

    string _userInput = "";
    cout << "Press any key to return to the menu." << endl;
    getline(cin, _userInput);
}

void Options(){
    system("clear");
    string ESC = "\033";
    string _userInput;
    
    while(tolower(_userInput[0]) != 'q'){
        system("clear");
        string ESC = "\033";
        cout << ESC << "[1;4mOPTIONS" << ESC << "[0m" << endl << endl;
        cout << "What would you like to change?" << endl << endl;
        cout << "[1] - Modify Player Data" << endl;
        cout << "[2] - Delete Player Data" << endl;
        cout << "[Q] - Quit" << endl;
        _userInput = "";
        while(_userInput == ""){ // Program will wait for valid input
            getline(cin, _userInput);
            switch(_userInput[0]){
                case '1': // Load Player Data from File
                    LoadData();
                    break;
                case '2': // Delete Player Data
                    DeleteData();
                    break;
                case 'Q': // Quit
                    break;
                case 'q': // Quit
                    break;
                default: // Any other input is invalid
                    cout << ESC << "[A" << ESC << "[2KInvalid Input!" << endl;
                    sleep_for(milliseconds(500));
                    _userInput = ""; // Input is reset back to "null" and the loop restarts.
                    cout << ESC << "[A" << ESC << "[2K"; // Clears the error message
            }
        }
    }
    // Manage Q Data (TBA)
    // Manage NN Data (TBA)
}

void ManageQData(){
    system("clear");

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
            cout << ESC << "[1;32mYour profile is now ready!" << ESC << "[0m" << endl;
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
    if(!ALL_PLAYERS.empty()){
        for(auto& p : ALL_PLAYERS){
            cout << "| " << p.first << " ";
        }
        cout << "|" << endl;
    }
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
    string ESC = "\033";
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

        cout << ESC << "[1;32m" << p->GetName() << "'s records saved!" << ESC <<"[0m" << endl;
    } else {
        throw "Account with that name not found";
    }
}

void LoadData(){
    system("clear");
    system("ls PlayerData");
    string ESC = "\033";
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
            if(ALL_PLAYERS.find(name) == NULL){
                Player* p = new Player(name);
                p->LoadRecords(wins, losses, games);
                ALL_PLAYERS.insert(make_pair(name, p));
                cout << ESC << "[1;32m" << name << "'s profile successfully loaded!" << ESC << "[0m" << endl;
            } else {
                cout << "Data for " << name << " is already loaded." << endl;
            }
            sleep_for(milliseconds(3000));
        } else {
            cout << ESC << "[1;31mFile name cannot be found." << ESC << "[0m" << endl;
            userInput = "";
        }
    }

}

void SaveQData(){
    ofstream QData; QData.open("Q_Data.txt");
    // Save name, num games played, num wins, num losses
    QData << q_AI->GetName() << "\n";
    QData << q_AI->GetGamesPlayed() << "\n";
    QData << q_AI->GetWins() << "\n";
    QData << q_AI->GetLosses() << "\n";
    QData << q_AI->GetBoard()->GetWidth() + ", " + q_AI->GetBoard()->GetHeight() << "\n";
    QData << q_TrainingEpochs << "\n";
    QData.close();
}

// void LoadAndTrainQ(){
//     ifstream inFile; inFile.open("Q_Data.txt");
//     if(inFile.good()){
//         vector<string> p_data;
//         string curr_data;
//         while(getline(inFile, curr_data)){
//             p_data.push_back(curr_data);
//         }
//         string name = p_data.at(0); int games = stoi(p_data.at(1)); int wins = stoi(p_data.at(2)); int losses = stoi(p_data.at(3));
//         Player* p = new Player(name);
//         p->LoadRecords(wins, losses, games);
//         ALL_PLAYERS.insert(make_pair(name, p));
//         cout << name << "'s profile successfully loaded!" << endl;
//         sleep_for(milliseconds(3000));
//     } else {
//         cout << "File name cannot be found." << endl;
//         userInput = "";
//     }
// }

void DeleteData(){
    system("clear");
    system("ls PlayerData");
    string ESC = "\033";
    cout << "\nType one of the txt files to delete the data of that player" << endl << endl;
    string userInput = "";
    while(userInput == ""){
        getline(cin, userInput);
        string fileName = "PlayerData/" + userInput;
        ifstream inFile; inFile.open(fileName);
        if(inFile.good()){
            cout << ESC << "[1;31mWARNING" << ESC << "[0m: The account linked to your save data will also be removed upon deletion!" << endl;
            cout << "Are you sure you want to proceed? [y/n]" << endl;
            string yesorno = ""; getline(cin, yesorno);
            inFile.close();
            if(tolower(yesorno[0]) == 'y'){
                // Delete the account associated with the txt file
                string name = "";
                for(int i = userInput.length() - 1; i >= 0; i--){
                    if(userInput[i] == '_'){
                        name = userInput.substr(0, i);
                        break;
                    }
                }
                for(int k = 0; k < name.length(); k++){
                    if(name[k] == '_'){
                        name[k] = ' ';
                    }
                }
                if(ALL_PLAYERS.find(name) != NULL){
                    delete ALL_PLAYERS.at(name);
                    ALL_PLAYERS.at(name) = NULL;
                    ALL_PLAYERS.erase(name);
                } else {
                    cout << "Account with that name not found. Txt file will still be deleted." << endl;
                }
                string cmd_string = "rm " + fileName;
                const char* cmd = cmd_string.c_str();
                system(cmd);
                cout << ESC << "[1;32mData successfully deleted!" << ESC << "[0m" << endl;
                sleep_for(milliseconds(3000));
            }
        } else {
            cout << ESC << "[1;31mFile name cannot be found." << ESC << "[0m" << endl;
            userInput = "";
        }
    }
}

void PlayQGame(Player* p1, QLearningAI* p2, Board* _board){
    // Actual game begins. Loops as long as no one wins
    string ESC = "\033";
    Board::BOARD_STATE _currState = Board::BOARD_STATE::INCOMPLETE;
    while(_currState == Board::BOARD_STATE::INCOMPLETE){
        if(_board->getNextTurn() == Board::PLAYER_TURN::P1){
            cout << ESC << "[1;41m" << p1->GetName() << "'s turn!" << ESC << "[0m" << endl;
            p1->dropChecker();
            //_currState = _board->checkWin(p1->GetSymbol());
        } else if (_board->getNextTurn() == Board::PLAYER_TURN::P2){
            cout << ESC << "[1;44m" << p2->GetName() << "'s turn!" << ESC << "[0m" << endl;
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
        cout << ESC << "[1;41m" << p1->GetName() << " Wins!" << ESC << "[0m" << endl;
        p1->win();
        p2->loss();
    } else if(_currState == Board::BOARD_STATE::P2_WIN){
        cout << ESC << "[1;44m" << p2->GetName() << " Wins!" << ESC << "[0m" << endl;
        p2->win();
        p1->loss();
    } else if(_currState == Board::BOARD_STATE::DRAW){
        cout << ESC << "[1mIncredible! It's a draw!" << ESC << "[0m" << endl;
        p1->tie();
        p2->tie();
    }

    _board->clearBoard();
}

void PlayNNGame(Player* p1, NeuralNetworkAI* p2, Board* _board){

    // Actual game begins. Loops as long as no one wins
    string ESC = "\033";
    Board::BOARD_STATE _currState = Board::BOARD_STATE::INCOMPLETE;
    while(_currState == Board::BOARD_STATE::INCOMPLETE){
        if(_board->getNextTurn() == Board::PLAYER_TURN::P1){
            cout << ESC << "[1;41m" << p1->GetName() << "'s turn!" << ESC << "[0m" << endl;
            p1->dropChecker();
            //_currState = _board->checkWin(p1->GetSymbol());
        } else if (_board->getNextTurn() == Board::PLAYER_TURN::P2){
            cout << ESC << "[1;44m" << p2->GetName() << "'s turn!" << ESC << "[0m" << endl;
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
        cout << ESC << "[1;41m" << p1->GetName() << " Wins!" << ESC << "[0m" << endl;
        p1->win();
        p2->loss();
    } else if(_currState == Board::BOARD_STATE::P2_WIN){
        cout << ESC << "[1;44m" << p2->GetName() << " Wins!" << ESC << "[0m" << endl;
        p2->win();
        p1->loss();
    } else if(_currState == Board::BOARD_STATE::DRAW){
        cout << ESC << "[1mIncredible! It's a draw!" << ESC << "[0m" << endl;
        p1->tie();
        p2->tie();
    }

    _board->clearBoard();
}

void PlayGame(Player* p1, Player* p2){
    string ESC = "\033";
    Board* _board = new Board();
    p1->SetPlayersBoard(_board);
    p2->SetPlayersBoard(_board);

    // Actual game begins. Loops as long as no one wins
    Board::BOARD_STATE _currState = Board::BOARD_STATE::INCOMPLETE;
    while(_currState == Board::BOARD_STATE::INCOMPLETE){
        if(_board->getNextTurn() == Board::PLAYER_TURN::P1){
            cout << ESC << "[1;41m" << p1->GetName() << "'s turn!" << ESC << "[0m" << endl;
            p1->dropChecker();
            //_currState = _board->checkWin(p1->GetSymbol());
        } else if (_board->getNextTurn() == Board::PLAYER_TURN::P2){
            cout << ESC << "[1;44m" << p2->GetName() << "'s turn!" << ESC << "[0m" << endl;
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
        cout << ESC << "[1;41m" << p1->GetName() << " Wins!" << ESC << "[0m" << endl;
        p1->win();
        p2->loss();
    } else if(_currState == Board::BOARD_STATE::P2_WIN){
        cout << ESC << "[1;44m" << p2->GetName() << " Wins!" << ESC << "[0m" << endl;
        p2->win();
        p1->loss();
    } else if(_currState == Board::BOARD_STATE::DRAW){
        cout << ESC << "[1mIncredible! It's a draw!" << ESC << "[0m" << endl;
        p1->tie();
        p2->tie();
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

bool NN_Warning(){
    system("clear");
    string ESC = "\033";
    cout << ESC << "[1;4;31mWARNING" << ESC << "[0m" << endl;
    cout << "The Neural Network AI is a highly experimental feature" << endl;
    cout << "Training may take some time and the algorithm may act unexpectedly." << endl;
    cout << "Are you sure you want to proceed? [y/n]" << endl;
    string yesorno = "";
    getline(cin, yesorno);
    if(tolower(yesorno[0]) == 'y'){
        return true;
    } else {
        return false;
    }
    system("clear");
}