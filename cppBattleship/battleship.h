// Header file for PA7 Battleship!

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <iostream>
#include <vector>
#include <unistd.h> 
#include <ctime>
#include <string>
using namespace std;

extern char currentPlayPen[10][10];
extern char showOptions[11][11];
extern vector<int> carrierHits;
extern vector<int> battleshipHits;
extern vector<int> submarineHits;
extern vector<int> destroyerHits;
extern vector<int> crusierHits;

void printArray(char arr[10][10]);
void printArray11(char arr[11][11]);
bool checkHits(void);
void checkField(vector<int> &vec);
void getCoordinates(vector<int>& vec);
int displayMenu(void);
char pickField(void);
void currentField(char arr[10][10], char arr2[10][10]);
void resetMenuDisplay(char arr[11][11],char arr2[11][11]);
void sunkenShip(int x);
void gameWin(void);

#endif