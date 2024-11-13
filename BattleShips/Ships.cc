#include "Ships.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <random> 
#include <string>

using namespace std;

Ships::Ships()
{
}

Ships::~Ships()
{
}

void Ships::clearTerminal()
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

void Ships::playerSwitch()
{
    cin.clear();
    cout << "<Press enter to continue>" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    clearTerminal();
}

int Ships::getCoordinate(int index)
{
    return this->coordinates[index];
}

bool Ships::checkCoordinate(Boards &playerBoards, int shipSize, int x, int y, char direction)
{
    if (direction == '\0')
    {
        if (x < 0 || x > 9 || y < 0 || y > 9)
        {
            return false;
        }
        if (playerBoards.getBoardData(0, x, y) != 0) 
        {
            return false;
        }
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (i != 0 || j != 0)
                {
                    if (x + i >= 0 && x + i < 10 && y + j >= 0 && y + j < 10)
                    {
                        if (playerBoards.getBoardData(0, x + i, y + j) != 0)
                        {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
        
    }
    else
    {
        if (direction != 'H' && direction != 'V')
        {
            return false;
        }
        if (x < 0 || x > 9 || y < 0 || y > 9)
        {
            return false;
        }
        if (direction == 'V')
        {
            if (x + shipSize > 10) 
            {
                return false;
            }
            for (int i = 0; i < shipSize; i++) 
            {
                if (playerBoards.getBoardData(0, x + i, y) != 0) 
                {
                    return false;
                }
            }
            for (int i = -1; i <= shipSize; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (x + i >= 0 && x + i < 10 && y + j >= 0 && y + j < 10)
                    {
                        if (playerBoards.getBoardData(0, x + i, y + j) != 0)
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        if (direction == 'H')
        {
            if (y + shipSize > 10) 
            {
                return false;
            }
            for (int i = 0; i < shipSize; i++)
            {
                if (playerBoards.getBoardData(0, x, y + i) != 0)
                {
                    return false;
                }
            }
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= shipSize; j++)
                {
                    if (x + i >= 0 && x + i < 10 && y + j >= 0 && y + j < 10)
                    {
                        if (playerBoards.getBoardData(0, x + i, y + j) != 0)
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        return false;
    }
}

char Ships::randomDirection() {
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1); 

    int dir = dis(gen);
    return (dir == 0) ? 'H' : 'V';
}

void Ships::randomCoordinates(Boards &playerBoards, int shipSize)
{
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(0, 9);
    bool breakLoop = false;
    do
    {
        if (shipSize != 1)
        {
            coordinates[0] = dis(gen);
            coordinates[1] = dis(gen);
            direction = randomDirection();
        }
        else
        {
            coordinates[0] = dis(gen);
            coordinates[1] = dis(gen); 
            direction = '\0';
        }
        
        if (checkCoordinate(playerBoards, shipSize, coordinates[0], coordinates[1], direction) == true)
        {
            breakLoop = true;
        }
    } while (breakLoop == false);
}

void Ships::setCoordinates(Boards &playerBoards, int shipSize)
{
    string input;
    bool breakLoop = false;
    do
    {
        playerBoards.showBoards();
        if (shipSize != 1)
        {
            cout << "Please enter a letter (A-J) followed by number (0-9) and ship's direction (H or V):" << endl
                << "Example: B4H (the ships can't touch)" << endl
                << "Enter the coordinates and direction of your ship: ";
            cin  >> input;
            cout << endl;
            if(input.length() != 3) {
                clearTerminal();
                cout << "Wrong format!" << endl << endl;
            }
            else
            {
                input[0] = toupper(input[0]);
                input[2] = toupper(input[2]);
                coordinates[0] = input[0] - 'A';
                coordinates[1] = input[1] - '0';
                direction = input[2];
                if  (checkCoordinate(playerBoards, shipSize, coordinates[0], coordinates[1], direction) == true)
                {    
                    clearTerminal();
                    breakLoop = true;
                }
                else
                {
                    clearTerminal();
                    cout << "Wrong format!" << endl << endl;
                }
            }
        }
        else
        {
            cout << "Please enter a letter (A-J) followed by number (0-9):" << endl << endl;
            cout << "Enter the coordinates of your ship: ";
            cin  >> input;
            cout << endl;
            if(input.length() != 2) {
                clearTerminal();
                cout << "Wrong format!" << endl << endl;
            }
            else
            {
                input[0] = toupper(input[0]);
                input[2] = toupper(input[2]);
                coordinates[0] = input[0] - 'A';
                coordinates[1] = input[1] - '0';
                direction = '\0';
                if  (checkCoordinate(playerBoards, shipSize, coordinates[0], coordinates[1], direction) == true)
                {    
                    clearTerminal();
                    breakLoop = true;
                }
                else
                {
                    clearTerminal();
                    cout << "Wrong format!" << endl << endl;
                }
            }
        }
    } while (breakLoop == false);
}

void Ships::buildShip(Boards &playerBoards, int shipSize)
{
    if (playerBoards.getBoardData(0, coordinates[0], coordinates[1]) == 0)
    {
        for (int i = 0; i < shipSize; i++)
        {
            playerBoards.setBoardData(0, coordinates[0], coordinates[1], 2);
            if (direction == 'V')
            {
                coordinates[0] += 1;
            }
            else if (direction == 'H')
            {
                coordinates[1] += 1;
            }
        }
    }
}

char Ships::findShipDirection(Boards &playerBoards, int x, int y)
{
    int verticalLength = 0;
    int horizontalLength = 0;

    for (int i = x; i >= 0; i--)
    {
        if (playerBoards.getBoardData(0, i, y) == 2 || playerBoards.getBoardData(0, i, y) == 3)
        {
            verticalLength++;
        }
        else
        {
            break;
        }
    }
    for (int i = x + 1; i < 10; i++)
    {
        if (playerBoards.getBoardData(0, i, y) == 2 || playerBoards.getBoardData(0, i, y) == 3)
        {
            verticalLength++;
        }
        else
        {
            break;
        }
    }

    for (int j = y; j >= 0; j--)
    {
        if (playerBoards.getBoardData(0, x, j) == 2 || playerBoards.getBoardData(0, x, j) == 3)
        {
            horizontalLength++;
        }
        else
        {
            break;
        }
    }
    for (int j = y + 1; j < 10; j++)
    {
        if (playerBoards.getBoardData(0, x, j) == 2 || playerBoards.getBoardData(0, x, j) == 3)
        {
            horizontalLength++;
        }
        else
        {
            break;
        }
    }

    if (verticalLength > 1)
    {
        return 'V';
    }
    else if (horizontalLength > 1)
    {
        return 'H';
    }
    return '\0';
}

void Ships::findShipStart(Boards &playerBoards, int x, int y, char direction, int &startX, int &startY)
{
    if (direction == '\0')
    {
        startX = x;
        startY = y;
    }
    else if (direction == 'H')
    {
        while (y > 0 && (playerBoards.getBoardData(0, x, y - 1) == 2 || playerBoards.getBoardData(0, x, y - 1) == 3))
        {
            y--;
        }
        
        startX = x;
        startY = y;
    }
    else if (direction == 'V')
    {
        while (x > 0 && (playerBoards.getBoardData(0, x - 1, y) == 2 || playerBoards.getBoardData(0, x - 1, y) == 3))
        {
            x--;
        }
        startX = x;
        startY = y;
    }
    else
    {
        startX = -1;
        startY = -1;
    }
}

int Ships::findShipLength(Boards &playerBoards, int x, int y, char direction)
{   
    int length = 0;

    if (direction == 'V')
    {
        for (int i = x; i < 10; i++)
        {
            if (playerBoards.getBoardData(0, i, y) == 2 || playerBoards.getBoardData(0, i, y) == 3)
            {
                length++;
            }
            else
            {
                break;
            }
        }
    }
    if (direction == 'H')
    {
        for (int j = y; j < 10; j++)
        {
            if (playerBoards.getBoardData(0, x, j) == 2 || playerBoards.getBoardData(0, x, j) == 3)
            {
                length++;
            }
            else
            {
                break;
            }
        }
    }
    if (direction == '\0')
    {
        length = 1;
    }
    return length;
}

bool Ships::isShipSunk(Boards &playerBoards, int startX, int startY, char direction, int shipSize)
{
    if (shipSize == 1)
    {
        return true;
    }
    if (direction == 'V')
    {
        for (int i = startX; i < startX + shipSize; i++)
        {
            if (playerBoards.getBoardData(0, i, startY) == 2)
            {
                return false;
            }  
        }
        return true;
    }
    if (direction == 'H')
    {
        for (int i = startY; i < startY + shipSize; i++)
        {
            if (playerBoards.getBoardData(0, startX, i) == 2)
            {
                return false;
            }  
        }
        return true;
    }
    return false;
}

void Ships::surroundShip(Boards &attackerBoards, Boards&defenderBoards, int startX, int startY, char direction, int shipSize)
{
    if (isShipSunk(defenderBoards, startX, startY, direction, shipSize))
    {
        if (direction == 'V')
        {
            for (int i = startX - 1; i <= startX + shipSize; i++)
            {
                for (int j = startY - 1; j <= startY + 1; j++)
                {
                    if (i >= 0 && i < 10 && j >= 0 && j < 10)
                    {
                        if (defenderBoards.getBoardData(0, i, j) == 0)
                        {
                            defenderBoards.setBoardData(0, i, j, 1);
                            attackerBoards.setBoardData(1, i, j, 1);
                        }
                    }
                }
            }
        }
        else if (direction == 'H')
        {
            for (int i = startX - 1; i <= startX + 1; i++)
            {
                for (int j = startY - 1; j <= startY + shipSize; j++)
                {
                    if (i >= 0 && i < 10 && j >= 0 && j < 10)
                    {
                        if (defenderBoards.getBoardData(0, i, j) == 0)
                        {
                            defenderBoards.setBoardData(0, i, j, 1);
                            attackerBoards.setBoardData(1, i, j, 1);
                        }
                    }
                }
            }
        }
        else if (direction == '\0')
        {
            for (int i = startX - 1; i <= startX + 1; i++)
            {
                for (int j = startY - 1; j <= startY + 1; j++)
                {
                    if (i >= 0 && i < 10 && j >= 0 && j < 10)
                    {
                        if (defenderBoards.getBoardData(0, i, j) == 0)
                        {
                            defenderBoards.setBoardData(0, i, j, 1);
                            attackerBoards.setBoardData(1, i, j, 1);
                        }
                    }
                }
            }
        }
    }
}

bool Ships::areAllShipsSunk(Boards &defenderBoards)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (defenderBoards.getBoardData(0, i, j) == 2)
            {
                return false;
            }
        }
    }
    return true;
}

void Ships::placeFourMasted(Boards &playerBoards, bool random)
{
    for (int i = this-> fourMastedShips; i > 0; i--)
    {
        if(random == false)
        {
            cout << "You're now placing your four-masted ships!" << endl
                << "Number of ships to place: " << this->fourMastedShips << endl << endl;
            setCoordinates(playerBoards, 4);
        }
        else
        {
            randomCoordinates(playerBoards, 4);
        }
        buildShip(playerBoards, 4);
    } 
}

void Ships::placeThreeMasted(Boards &playerBoards, bool random)
{
    for (int i = this->threeMastedShips; i > 0; i--)
    {
        if(random == false)
        {
            cout << "You're now placing your three-masted ships!" << endl
                << "Number of ships to place: " << i << endl << endl;
            setCoordinates(playerBoards, 3);
        }
        else
        {
            randomCoordinates(playerBoards, 3);
        }
        buildShip(playerBoards, 3);
    }
}

void Ships::placeTwoMasted(Boards &playerBoards, bool random)
{
    for (int i = this->twoMastedShips; i > 0; i--)
    {
        if(random == false)
        {
            cout << "You're now placing your two-masted ships!" << endl
                << "Number of ships to place: " << i << endl << endl;
            setCoordinates(playerBoards, 2);
        }
        else
        {
            randomCoordinates(playerBoards, 2);
        }

        buildShip(playerBoards, 2);
    }
}

void Ships::placeOneMasted(Boards &playerBoards, bool random)
{
    for (int i = this->oneMastedShips; i > 0; i--)
    {
        if(random == false)
        {
            cout << "You're now placing your one-masted ships!" << endl
                << "Number of ships to place: " << i << endl << endl;
            setCoordinates(playerBoards, 1);
        }
        else
        {
            randomCoordinates(playerBoards, 1);
        }
        buildShip(playerBoards, 1);
    }
}

void Ships::clearShips()
{
    this->coordinates[0] = -1;
    this->coordinates[1] = -1;
    this->direction = ' ';
}


