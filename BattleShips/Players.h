#ifndef PLAYERS_H
#define PLAYERS_H
#include "Boards.h"
#include "Ships.h"
#include <string>

using namespace std;

class Players
{
private:
    string name = "NULL";
    int wins = 0;

    int shot[2];
    void clearTerminal();
    void playerSwitch();
public:
    Players(string name);
    ~Players();
    
    string getName();  
    int getWins();
    void giveWin();  
    void clearShots();

    int getShot(int index);
    bool checkShot(Boards &playerBoards, int x, int y);
    void inputShootCoordinates(Boards &playerBoards);

    void attack(Boards &attackerBoards, Ships &attackerShips, Boards &defenderBoards, Ships &defenderShips);
};
#endif
