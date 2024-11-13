#include "Boards.h"
#include <iostream>

using namespace std;

Boards::Boards()
{
}

Boards::~Boards()
{
}

int Boards::getBoardData(int type, int x, int y)
{
    return this->playerBoardsData[type][x][y];
}

void Boards::setBoardData(int type, int x, int y, int value)
{
    this->playerBoardsData[type][x][y] = value;
}

void Boards::printRow(int index, int i)
{
    cout << "[" << alphabet[i] << "] ";
    for (int j = 0; j < 10; j++)
    {
        cout << " ";
        switch (playerBoardsData[index][i][j])
        {
        case 0: //  [ ] - puste (bez interakcji) 
            cout << "◦"; 
            break;
        
        case 1: // [•] - nie trafiony
            cout << "•";
            break;

        case 2: // [□] - statek
            cout << "□";
            break;
        
        case 3: // [■] - trafiony
            cout << "■";
            break;
        default:
            cout << "?";
            break;
        }
        cout <<  "  ";
    }
}

void Boards::showBoards()
{
    cout << "Your Boards:" << endl;
    cout << "\t\t\t Ocean Grid\t\t\t\t\t Target Grid" << endl;
    cout << "\t    " << indexNumbers;
    cout << "\t";
    cout <<  "    " << indexNumbers << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << "\t";
        printRow(0, i);
        cout << "\t";
        printRow(1, i);
        cout << endl;
    }
    cout << endl << endl;
}

void Boards::clearBoards()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            setBoardData(0, i, j, 0);
            setBoardData(1, i, j, 0);
        }
    }
}