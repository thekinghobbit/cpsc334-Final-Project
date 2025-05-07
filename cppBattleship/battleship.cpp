// Implementation file for PA7 Battleship!

#include "battleship.h"

// The ships are deployed as shown. (You may create additional ship deployments if you wish.)
// This 2D array is NOT shown to the user.
vector<int> attempt;// the users attempt at hitting a ship
int userChoice;// used for the menu
// basically the hp bar for all the ships
vector<int> destroyerHits = {2,2};
vector<int> battleshipHits = {4,4,4,4};
vector<int> crusierHits = {3,3,3};
vector<int> carrierHits = {5,5,5,5,5};
vector<int> submarineHits = {3,3,3};
//these are so the sunkenShip() doesn't run every time the board is checked
int carr = 0, subm = 0, batt = 0, dest = 0 ,crus = 0;
// total amount of attempts
int ATTEMPTS = 0;


char currentPlayPen[10][10];// the playboard that holds the players attempts
// game boards 1-3
char field1[10][10] = {{'d','-','-','-','-','-','-','-','-','-'},
                      {'d','-','C','-','-','-','-','-','-','-'},
                      {'-','-','C','-','-','-','-','-','-','-'},
                      {'-','-','C','-','-','b','b','b','b','-'},
                      {'-','-','-','-','c','-','-','-','-','-'},
                      {'-','-','-','-','c','-','-','s','s','s'},
                      {'-','-','-','-','c','-','-','-','-','-'},
                      {'-','-','-','-','c','-','-','-','-','-'},
                      {'-','-','-','-','c','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'}};

char field2[10][10] = {{'-','-','-','-','-','-','-','-','-','-'},
                      {'-','c','-','-','-','-','-','d','-','-'},
                      {'-','c','-','-','-','-','-','d','-','-'},
                      {'-','c','-','-','-','-','-','-','-','-'},
                      {'-','c','-','s','s','s','-','-','-','-'},
                      {'-','c','-','-','-','-','-','-','b','-'},
                      {'-','-','-','-','-','-','-','-','b','-'},
                      {'-','-','-','-','-','-','-','-','b','-'},
                      {'-','-','-','-','-','-','-','-','b','-'},
                      {'-','C','C','C','-','-','-','-','-','-'}};

char field3[10][10] = {{'-','-','-','-','-','-','-','-','d','-'},
                       {'-','-','-','-','-','-','-','-','d','-'},
                       {'-','-','-','-','C','-','-','-','-','-'},
                       {'s','-','-','-','C','-','-','-','-','-'},
                       {'s','-','-','-','C','-','-','-','-','-'},
                       {'s','-','c','-','-','-','b','-','-','-'},
                       {'-','-','c','-','-','-','b','-','-','-'},
                       {'-','-','c','-','-','-','b','-','-','-'},
                       {'-','-','c','-','-','-','b','-','-','-'},
                       {'-','-','c','-','-','-','-','-','-','-'}};
//blank
char menuDisplay[11][11] = {{'x','0','1','2','3','4','5','6','7','8','9'},
                         {'0','-','-','-','-','-','-','-','-','-','-'},
                         {'1','-','-','-','-','-','-','-','-','-','-'},
                         {'2','-','-','-','-','-','-','-','-','-','-'},
                         {'3','-','-','-','-','-','-','-','-','-','-'},
                         {'4','-','-','-','-','-','-','-','-','-','-'},
                         {'5','-','-','-','-','-','-','-','-','-','-'},
                         {'6','-','-','-','-','-','-','-','-','-','-'},
                         {'7','-','-','-','-','-','-','-','-','-','-'},
                         {'8','-','-','-','-','-','-','-','-','-','-'},
                         {'9','-','-','-','-','-','-','-','-','-','-'}};
char showOptions[11][11] = {{'x','0','1','2','3','4','5','6','7','8','9'},
                         {'0','-','-','-','-','-','-','-','-','-','-'},
                         {'1','-','-','-','-','-','-','-','-','-','-'},
                         {'2','-','-','-','-','-','-','-','-','-','-'},
                         {'3','-','-','-','-','-','-','-','-','-','-'},
                         {'4','-','-','-','-','-','-','-','-','-','-'},
                         {'5','-','-','-','-','-','-','-','-','-','-'},
                         {'6','-','-','-','-','-','-','-','-','-','-'},
                         {'7','-','-','-','-','-','-','-','-','-','-'},
                         {'8','-','-','-','-','-','-','-','-','-','-'},
                         {'9','-','-','-','-','-','-','-','-','-','-'}};

// Prints an array
void printArray(char arr[10][10]){

    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

}
// Prints an 11 x 11 array
void printArray11(char arr[11][11]){

    for (int i = 0; i < 11; i++){
        for (int j = 0; j < 11; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

}
// displays menu and gets user input
int displayMenu(void){

    //system("clear");
    cout <<" -------------------\n    -BATTLE SHIP- \n -------------------" << endl;
    cout <<"Please select your choice: \n 1.Select gameboard \n 2.Select coordinates \n 3.Fire! \n 4.Quit" << endl;
    cin >> userChoice;
    return userChoice;
}
// resets the display to a blank playfield if the user changes fields mid game
void resetMenuDisplay(char arr[11][11],char arr2[11][11]){
    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 11; j++)
            arr2[i][j] = arr[i][j];
}
// lets the user pick what field they want
char pickField(void) {
    destroyerHits = {2, 2};
    battleshipHits = {4, 4, 4, 4};
    crusierHits = {3, 3, 3};
    carrierHits = {5, 5, 5, 5, 5};
    submarineHits = {3, 3, 3};
    carr = 0, subm = 0, batt = 0, dest = 0, crus = 0;
    int mapChoice;
    ATTEMPTS = 0;
    resetMenuDisplay(menuDisplay, showOptions);
    cout << "WARNING: RESETTING GAMEBOARD RESETS PROGRESS\n";
    cout << "What gameboard would you like? \n 1. North Pacific \n 2. South Pacific \n 3. Upper left Atlantic? idk\n";
    cin >> mapChoice;
    while (mapChoice < 1 || mapChoice > 3) {
        cout << "Please enter a valid choice. >:((\n";
        cin >> mapChoice;
    }
    switch (mapChoice) {
        case 1:
            currentField(field1, currentPlayPen);
            return field1[0][0]; // Return a valid element
        case 2:
            currentField(field2, currentPlayPen);
            return field2[0][0]; // Return a valid element
        case 3:
            currentField(field3, currentPlayPen);
            return field3[0][0]; // Return a valid element
        default:
            currentField(field1, currentPlayPen);
            return field1[0][0]; // Default to a valid element
    }
}
// gets the coordinates from the user and stores them in a vector
void getCoordinates(vector<int> &vec){
    int num;


    cout << "Please select a row:\n";
    cin >> num;
    while(num < 0 || num > 9){
        cout << "Please enter a valid row\n";
        cin >> num;
    }
    vec.push_back(num);

    cout << "Please select a column: \n";
    cin >> num;
     while(num < 0 || num > 9){
        cout << "Please enter a valid column\n";
        cin >> num;
    }
    vec.push_back(num);
    //cout << vec[0] << " " << vec[1] << endl;

}
// checks the field for hits and marks hits and misses on the playboard displayed to the user
void checkField(vector<int> &attempt) {
    int x = attempt[0];
    int y = attempt[1];

    if (currentPlayPen[x][y] == 'c' || currentPlayPen[x][y] == 'b' || currentPlayPen[x][y] == 'd' || currentPlayPen[x][y] == 's') {
        currentPlayPen[x][y] = 'x'; // Mark as hit
        showOptions[x + 1][y + 1] = 'H'; // Update showOptions to indicate a hit
    } else {
        showOptions[x + 1][y + 1] = 'M'; // Update showOptions to indicate a miss
    }

    attempt.clear(); // Clear the attempt vector
}
// sets the current field that the user selects in the pickField()
void currentField(char arr[10][10], char arr2[10][10]){
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            arr2[i][j] = arr[i][j];
}
// display a little "animation" when a ship is sunk
void sunkenShip(int x){
    const string arr[] = {"carrier","submarine","battleship","destroyer","crusier"};
    system("clear");
    cout <<"*   \n";
    sleep(.1);
    cout <<"          *   \n";
    sleep(.1);
    cout <<"                     *   \n";
    sleep(.1);
    cout <<"                            *   \n";
    sleep(.1);
    cout <<"                          ****BOOOOMMM****\n";
    sleep(.1);
    cout <<"you sunk my " << arr[x] << "!\n";
    sleep(.2);
}
// displays a you win screen
void gameWin(void){
    char winScreen[10][10] = {{'_','_','_','_','_','_','_','_','_','_'},
                              {' ','Y','O','U',' ','W','I','N','!',' '},
                              {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                              {'B','A','T','T','L','E','S','H','I','P'},
                              {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                              {' ',' ',' ','/','\\',' ',' ',' ',' ',' '},
                              {' ','_','_','|','|','_','_','_','_',' '},
                              {'-','\\',' ',' ','o','o','o',' ','/','-'},
                              {'-','-','\\','_','_','_','_','/','-','-'},
                              {'-','-','-','-','-','-','-','-','-','-'}};
    system("clear");

    printArray(winScreen);
}
// checks to see what ships have sunk and returns a bool for if the game is won or not
bool checkHits(void){
    
    cout << "in check hits\n";
    bool hitBool = false;
    if(carrierHits.empty()){
        carr += 1;
        if(carr < 2){sunkenShip(0);}
    }
    if(submarineHits.empty()){
        subm += 1;
        if(subm < 2){sunkenShip(1);}
    }
    if(battleshipHits.empty()){
        batt += 1;
        if(batt < 2){sunkenShip(2);}
    }
    if(destroyerHits.empty()){
        dest += 1;
        if(dest < 2){sunkenShip(3);}
                
    }
    if(crusierHits.empty()){
        crus += 1;
        if(crus < 2){sunkenShip(4);}    
    }

    if( carrierHits.empty() && submarineHits.empty() && battleshipHits.empty() && destroyerHits.empty() && crusierHits.empty()){
        gameWin();
        hitBool = true;
    }
    else{
        hitBool = false;
    }
    return hitBool;
}

