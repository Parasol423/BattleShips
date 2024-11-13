#include "Players.h"
#include <iostream>
#include <limits>

using namespace std;

Players::Players(string name)
{
    this->name = name;
}

Players::~Players()
{
}

string Players::getName()
{
    return string(this->name);
}

int Players::getWins()
{
    return this->wins;
}

void Players::giveWin()
{
    this->wins++;
}

void Players::clearShots()
{
    this->shot[0] = -1;
    this->shot[1] = -1;
}

void Players::clearTerminal()
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

void Players::playerSwitch()
{
    cin.clear();
    cout << "<Press enter to continue>" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    clearTerminal();
}

int Players::getShot(int index)
{
    return this->shot[index];
}

bool Players::checkShot(Boards &playerBoards, int x, int y)
{
    if (x < 0 || x > 9 || y < 0 || y > 9)
    {
        return false;
    }
    else if (playerBoards.getBoardData(1, x, y) == 1 || playerBoards.getBoardData(1, x, y) == 2)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Players::inputShootCoordinates(Boards &playerBoards)
{
    string input;
    bool breakLoop = false;
    do
    {
        playerBoards.showBoards();
        cout << "Please enter a letter (A-J) followed by number (0-9):" << endl << endl
            << "Enter the coordinates of your shot: ";
            cin  >> input;
            cout << endl;

            if(input.length() != 2) {
                clearTerminal();
                cout << "Wrong Format!" << endl << endl;
            }
            else
            {
                input[0] = toupper(input[0]);
                shot[0] = input[0] - 'A';
                shot[1] = input[1] - '0';
                if  (checkShot(playerBoards, shot[0], shot[1]) == true)
                {    
                    clearTerminal();
                    breakLoop = true;
                }
                else
                {
                    clearTerminal();
                    cout << "Wrong Format! - You can't shoot there!" << endl << endl;
                }
            }
    } while (breakLoop == false);
}

void Players::attack(Boards &attackerBoards, Ships &attackerShips, Boards &defenderBoards, Ships &defenderShips)
{
    bool win = false;
    do
    {
        inputShootCoordinates(attackerBoards);
        char shipDirection = defenderShips.findShipDirection(defenderBoards, shot[0], shot[1]);
        int startX, startY;
        defenderShips.findShipStart(defenderBoards, shot[0], shot[1], shipDirection, startX, startY);
        int shipLength = defenderShips.findShipLength(defenderBoards, startX, startY, shipDirection);
        if (defenderBoards.getBoardData(0, shot[0], shot[1]) == 0)
        {
            defenderBoards.setBoardData(0, shot[0], shot[1], 1);
            attackerBoards.setBoardData(1, shot[0], shot[1], 1);
        }
        else
        {
            defenderBoards.setBoardData(0, shot[0], shot[1], 3);
            attackerBoards.setBoardData(1, shot[0], shot[1], 3);
            if (defenderShips.isShipSunk(defenderBoards, startX, startY, shipDirection, shipLength) == true)
            {
                attackerShips.surroundShip(attackerBoards, defenderBoards, startX, startY, shipDirection, shipLength);
            }
        }
        attackerBoards.showBoards();
        if (attackerBoards.getBoardData(1, shot[0], shot[1]) == 1)
        {
            clearTerminal();
            cout << "You missed!" << endl << endl;
            attackerBoards.showBoards();
            if (win == false)
            {
                playerSwitch();
            }
        }
        else if (attackerBoards.getBoardData(1, shot[0], shot[1]) == 3)
        {
            clearTerminal();
            cout << "You hit a ship";
            if (defenderShips.isShipSunk(defenderBoards, startX, startY, shipDirection, shipLength) == true)
            {
                cout << " - and you sunk it";
            }
            cout << "!" << endl << endl;
            if (defenderShips.areAllShipsSunk(defenderBoards) == true)
            {
                win = true;
                clearTerminal();
            }
        }
    } while (attackerBoards.getBoardData(1, shot[0], shot[1]) == 3 && win == false);
}
