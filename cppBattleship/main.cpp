//Main file for PA7 Battleship!

#include "battleship.h"

int main(){

    extern char field1[10][10];  //defined in battleship.cpp
    extern char attempts[10][10];
    extern char showOptions[11][11];
    extern char currentPlayPen[10][10];
    extern char showOptions[11][11];
    extern int userChoice;
    extern int ATTEMPTS;
    extern vector<int> attempt;
    

//--------------------------------------------------------------

    currentField(field1, currentPlayPen);
    do{// do while loops runs aslong as user doesnt select exit option
        system("clear");
        if(checkHits()){// if game is won it exits before the menu pops up
            break;
            gameWin();
    }
        printArray11(showOptions);
        displayMenu();
        if(ATTEMPTS > 40){// the total attempts the player has to win
            cout <<"too many attempts. the evil navy boats moved and sunk all ur boats\nbye lol\n";
            sleep(1);
            exit(0);
        }
        while(userChoice < 1 ||userChoice > 4){// makes it so the user has to pick one of the proper options
            cout << "please enter a valid option\n";
            cin >> userChoice;
        }
        switch(userChoice){// switch sorts out user options and runs the proper functions based on users choice
            case 1: pickField();
            break;
            case 2: getCoordinates(attempt);
            break;
            case 3: 
                    checkField(attempt);
                    checkHits();
                    break;
            case 4: break;
        }
    }while(userChoice != 4);


    cout << "Thanks for playing!\n";
    
       
    return 0;
}


