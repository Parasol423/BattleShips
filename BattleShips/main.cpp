#include <iostream>
#include <limits>
#ifdef _WIN32
#include <windows.h>
#endif
#include "Players.cc"
#include "Boards.cc"
#include "Ships.cc"

using namespace std;

void clearTerminal()
{
    #ifdef _WIN32
        system("cls");
        system("cls");
    #elif __APPLE__

        system("clear");
        system("clear");
    #elif __linux__
        system("clear");
        system("clear");
    #else
        std::cout << "\033[2J\033[1;1H";
        std::cout << "\033[2J\033[1;1H";
    #endif
}

void playerSwitch()
{
    cin.clear();
    cout << "<Press enter to continue>" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    clearTerminal();
}

string chooseYourName(int playerNum)
{
    string name;
    char choiceConfirm;
    do
    {
        cout << "Player " << playerNum << ": " << endl;
        cout << "Choose what name you want to be called by: ";
        cin >> name;

        if (name.empty()) {
            continue;
        }
        do
        {
            cout << "Are you sure you want to be called \"" << name << "\"? [Y/N]: ";
            cin >> choiceConfirm; 
            choiceConfirm = toupper(choiceConfirm);
            clearTerminal();
            if (choiceConfirm != 'Y' && choiceConfirm != 'N' && choiceConfirm != '\0')
            {
                cout << "Player " << playerNum << ": " << endl;
                cout << "Choose what name you want to be called by: " << name << endl;
            }
        } while (choiceConfirm != 'Y' && choiceConfirm != 'N');
        if (choiceConfirm == 'N')
        {
            cout << "Okay, let's try again! - ";
        }
    } while (choiceConfirm == 'N');
    clearTerminal();
    return string(name);
}

void placeAllShips(Players &player, Ships &playerShips, Boards &playerBoards)
{
    char choiceR;
    bool random = true;
    do
    {   playerBoards.showBoards();
        cout << player.getName() << " - Do you want to place your ships randomly or manually? [R/M]: ";
        cin >> choiceR;
        choiceR = toupper(choiceR);
        clearTerminal();
    } while (choiceR != 'M' && choiceR != 'R');

    random = (choiceR == 'R') ? true : false;

    playerShips.placeFourMasted(playerBoards, random);
    playerShips.placeThreeMasted(playerBoards, random);
    playerShips.placeTwoMasted(playerBoards, random);
    playerShips.placeOneMasted(playerBoards, random);
}

void turn(Players &attacker, Boards &attackerBoards, Ships &attackerShips, Boards &defenderBoards, Ships &defenderShips, int round)
{
    cout << attacker.getName() << " - Your turn is about to begin!" << endl;
    playerSwitch();
    cout << attacker.getName() << " - " << "Round " << round << endl;
    attacker.attack(attackerBoards, attackerShips, defenderBoards, defenderShips);
}

void showWinCount(Players &winner, Players &loser)
{
    cout << "Win count:" << endl
        << "\t" << winner.getName() << " - " << winner.getWins() << " wins" << endl
        << "\t" << loser.getName() << " - " << loser.getWins() << " wins" << endl;
}

void askToPlayAgain(bool &playAgain)
{
    char choiceYN;
    while (true)
    {
        cout << "Do you want to play again? (y/n): ";
        cin >> choiceYN;
        choiceYN = toupper(choiceYN);
        if (choiceYN == 'Y')
        {
            clearTerminal();
            playAgain = true;
            break;
        }
        else if (choiceYN == 'N')
        {
            clearTerminal();
            playAgain = false;
            break;
        }                
        else
        {
            clearTerminal();
        }
    }
}

int main()
{
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    Boards P1Boards;
    Players P1(chooseYourName(1));
    Ships P1Ships;

    Boards P2Boards;
    Players P2(chooseYourName(2));
    Ships P2Ships;

    bool playAgain = false; 
    
    do
    {
        if (playAgain == true)
        {
            P1.clearShots();
            P1Boards.clearBoards();
            P1Ships.clearShips();

            P2.clearShots();
            P2Boards.clearBoards();
            P2Ships.clearShips();
        }
        cout << P1.getName() << " - Its your turn to place your ships!" << endl;
        playerSwitch();
        placeAllShips(P1, P1Ships, P1Boards);

        cout << P1.getName() << " - Looks like you have placed all of your ships!" << endl << endl;
        P1Boards.showBoards();
        playerSwitch();

        cout << P2.getName() << " - Its your turn to place your ships!" << endl ;
        playerSwitch();
        placeAllShips(P2, P2Ships, P2Boards);

        cout << P2.getName() << " - Looks like you have placed all of your ships!" << endl << endl;
        P2Boards.showBoards();
        playerSwitch();

        int round = 1;
        bool win = false;

        while (win == false)
        {
            turn(P1, P1Boards, P1Ships, P2Boards, P2Ships, round);

            if (P2Ships.areAllShipsSunk(P2Boards) == true)
            {
                win = true;
                P1.giveWin();
                cout << P1.getName() << " - Congratulations, you have won the game!" << endl
                    << P2.getName() << " - Better luck next time!" << endl << endl;
                P1Boards.showBoards();
                if (playAgain == true)
                {
                    showWinCount(P1, P2); 
                }
                playerSwitch();
                continue;
            }

            turn(P2, P2Boards, P2Ships, P1Boards, P1Ships, round);

            if (P1Ships.areAllShipsSunk(P1Boards) == true)
            {
                P2.giveWin();
                win = true;
                cout << P2.getName() << " - Congratulations, you have won the game!" << endl
                    << P1.getName() << " - Better luck next time!" << endl << endl;
                P2Boards.showBoards();
                if (playAgain == true)
                {
                    showWinCount(P2, P1); 
                }
                playerSwitch();
                continue;
            }
            
            round++;
        }
        askToPlayAgain(playAgain);
    } while (playAgain == true);
}