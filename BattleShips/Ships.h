#ifndef SHIPS_H
#define SHIPS_H
#include "Boards.h"

using namespace std;

class Ships
{
private:
    void clearTerminal();
    void playerSwitch();

    int coordinates[2];
    char direction;

    int oneMastedShips = 4;
    int twoMastedShips = 3;
    int threeMastedShips = 2;
    int fourMastedShips = 1;
public:
    Ships(/* args */);
    ~Ships();

    int getCoordinate(int index);
    bool checkCoordinate(Boards &playerBoards, int shipSize, int x, int y, char direction);
    char randomDirection();
    void randomCoordinates(Boards &playerBoards, int shipSize);
    void setCoordinates(Boards &playerBoards, int shipSize);

    void buildShip(Boards &playerBoards, int shipSize);

    char findShipDirection(Boards &playerBoards, int x, int y);
    void findShipStart(Boards &playerBoards, int x, int y, char direction, int &startX, int &startY);
    int findShipLength(Boards &playerBoards, int x, int y, char direction);

    bool isShipSunk(Boards &playerBoards, int startX, int startY, char direction, int shipSize);
    void surroundShip(Boards &attackerBoards, Boards &defenderBoards, int startX, int startY, char direction, int shipSize);
    bool areAllShipsSunk(Boards &defenderBoards);

    void placeFourMasted(Boards &playerBoards, bool random);
    void placeThreeMasted(Boards &playerBoards, bool random);
    void placeTwoMasted(Boards &playerBoards, bool random);
    void placeOneMasted(Boards &playerBoards, bool random);
    
    void clearShips();
};

#endif