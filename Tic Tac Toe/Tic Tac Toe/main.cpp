//  Debugging Rows 0 0 0 doesn't win.
//  main.cpp
//  A playful program using a linear array to represent a 2D matrix and has useful simple applications on rows and colums traversals
//
//  Created by Zouhair Khallaf on 2/10/17.
//  Copyright © 2017 Zouhair Khallaf. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#include <vector>
#include<iomanip>



using namespace std;

void welcomeMessage();
void setGameVariables(string& userSymbol, string& computerSymbol, string& player , int& Row, int&Column);
void createGameBoard(char* & board, const int Row, const int Column);
void fillBoard(char* arr, const int Row, const int Column);
void displayBoard(char* board, const int Row, const int Column);
int getStartingIndexOfRow(const int Row, const int Column, const int ithRow);
void displayIthRow(char* arr, const int Row, const int Column, const int ithRow);
void displayAllRow(char* arr, const int Row, const int Column);
void getFirstColumnIndices(char* arr, const int Row, const int Column);
void displayAllColumnIndices(char* arr, const int Row, const int Column);
bool MatrixIsnByn(const int Row, const int Column);
void displayAllDiagonals(char* arr, const int Row, const int Column);

bool isPlayerWinner(char* arr, int Row, int Column, string playerTurn);

bool completedRow(char* arr, int Row, int Column, int playerNumber);
bool validMove(char* arr, string input, string symbol);
void goodByMessage();
void wanToPlayMore(bool& wantToPlay);
void playGame(char* board, const int rows, const int columns, bool& gameOn, string userSymbol,string computerSymbol, string& playerTurn);
void playComputer(char* board, const int rows, const int columns, string computerSymbol);
void playUser(char* board, const int rows, const int columns, string userSymbol);
//----------------UTILITIES------------------------------------------------------------------
int howManyEmptySpotsInBoard(char* board, const int boardSize);
void drawLine(int N);
bool boardIsFull(char*board, const int rows, const int columns);
bool completedRow(char* arr, int Row, int Column, string player);
bool completedColumn(char* arr, int Row, int Column, string player);
bool completedDiagonal(char* arr, int Row, int Column, string player);
//----------------------------------------------------------------------------------------MAIN()



int main(int argc, const char * argv[]) {
    bool wantToPlay=true;
    welcomeMessage();
    while(wantToPlay){
        srand (time(NULL) );
        string userSymbol,computerSymbol,playerTurn;
        char* board;
        bool gameOn = true;
        int rows=0, columns=0;
        createGameBoard(board, rows, columns);
        setGameVariables(userSymbol,computerSymbol,playerTurn,rows,columns);
        for (int i=0; i<rows*columns; i++)
            cout << board[i] <<" ";
        cout << "\t GAME ON " <<endl<<endl;
        while(gameOn){
            playGame(board, rows, columns, gameOn,userSymbol,computerSymbol, playerTurn);
            displayBoard(board, rows, columns);
            if(isPlayerWinner(board, rows, columns,playerTurn))
                gameOn = false;
        }
        cout << "\t GAME OVER " <<endl<<endl;
        wanToPlayMore(wantToPlay);
    }
    goodByMessage();
    
    return 0;
}


//----------------------------------------------------------------------------------------FUNCTIONS (needs house keeping)

bool boardIsFull(char*board, const int rows, const int columns){
    bool tied_game = true;
    int board_size = rows*columns;
    for (int i=0; i<board_size; i++) {
        if(board[i] == '\0'){
            return false;
        }
    }
    cout << " GAME TIED , No winners ... " <<endl;
    return tied_game;
}


//Assuming playerTurn has been verified before.
void playGame(char* board, const int rows, const int columns, bool& gameOn, string userSymbol,string computerSymbol, string& playerTurn){
    if (playerTurn == "Y") {
        playerTurn = "I";
        playComputer(board, rows, columns, computerSymbol);
    }else if (playerTurn == "I"){
        playerTurn = "Y";
        playUser(board, rows, columns, userSymbol);
    }
    //gameOn = !isPlayerWinner(board, rows, columns, playerTurn);
}

//Picks a random index from those who are empty in the string and places it's simbol

void playComputer(char* board, const int rows, const int columns, string computerSymbol){
    cout << "\t\t\t .I played, your turn ..." <<endl;
    int boardSize = rows*columns;
    //Count the empty positions in the board and store it in C
    int C = howManyEmptySpotsInBoard(board,boardSize);
    //Build an new array named Arr of size C.
    int* Arr = new int[C];
    //Store empty positions indices from the board into the Arr[C]
    for (int i=0, j=0; i<boardSize; i++) {
        if (board[i] != 'X' && board[i] != 'O'){
            Arr[j] = i;
            j++;
        }
    }
    //Generate a random number named r = rand()% C
    int r = rand()% C;
    //Get the index of this from Arr. like this Arr[r] = index
    int index = Arr[r];
    //Make this move by board[index] = symbol.
    board[index] = computerSymbol[0]; //Since we are storing one character instead of a string.
    delete[] Arr;
}

// Utility
// Returns the number of empty indices in the board
int howManyEmptySpotsInBoard(char* board, const int boardSize){
    int c = 0;
    for (int i=0; i<boardSize; i++) {
        if (board[i]!='X' && board[i]!='O')
            c++;
    }
    return c;
}

void playUser(char* board, const int rows, const int columns, string userSymbol){
    int boardSize = rows*columns;
    bool  badindex = true;
    int input;
    int index;
    do {
        //Get the user input
        cout << "\t\t>Pick a position 1-" << boardSize << ": ";
        cin >> input;
        index = input - 1;
        if(index<0 || index>=boardSize){ // Checks if input is out of range
            continue;
        }else{
            //Count the empty positions in the board and store it in C
            int C = howManyEmptySpotsInBoard(board,boardSize);
            //Build an new array named Arr of size C.
            int* Arr = new int[C];
            //Store empty positions indices from the board into the Arr[C]
            for (int i=0, j=0; i<boardSize; i++) {
                if (board[i]!='X' && board[i]!='O'){
                    Arr[j] = i;
                    j++;
                }
            }
            //Check if input is in the array
            for (int i=0; i<C; i++) {
                if (Arr[i] == index ) {
                    //GOOD INDEX
                    badindex = false;
                }
            }
            delete[] Arr;
        }
    }while (badindex);
    //Make this move by board[index] = symbol.
    board[index] = userSymbol[0]; //Since we are storing one character instead of a string.
}

 //We check if Player is winner if completed a row || Column || Diagonal (if any)
 bool isPlayerWinner(char* arr, int Row, int Column, string playerTurn){
     string player;
     if (playerTurn == "Y") {
         player = "YOU";
     }else{
         player = "THE COMPUTER";
     }
     if (completedRow(arr,Row,Column,player)){
         return true;
     }else if (completedColumn(arr,Row,Column,player)){
         return true;
     }else if (completedDiagonal(arr,Row,Column,player)){
         return true;
     }else if(boardIsFull(arr, Row, Column)){
         return true;
     }else{
         return false;
     }
 }

 bool completedRow(char* arr, int Row, int Column, string player){
     for (int i=1; i<=Row; i++) { //i is the ith Row example (first Row, Second, Third ....)
         int index=getStartingIndexOfRow(Row,Column,i);
         char prev = arr[index];
         for (int j=index+1, i=0; i<Column; j++, i++) { // the i makes sure this loop runs Column times starting from 0.
             if(prev == '\0' || prev != arr[j]){
                 break;
             }
             if (i==Column-1){
                 cout << "ROW Number : " << index << "completed by player "<< player <<endl;
                 return true; // wins a row;
             }
         }
     }
     return false;
 }


bool completedColumn(char* arr, int Row, int Column, string player){
    for (int j=0; j<Column; j++) {
        char prev = arr[j];
        for (int i=1; i<Row; i++) {
            if(arr[(i*Column)+j] == '\0' || arr[(i*Column)+j] != prev){
                break; //  the inner loope
            }
            if(i==Row-1){
                //winner column
                cout << "COLUMN number :" << j+1 << " : completed by "<< player << endl;
                return true;
            }
        }
        //if loop reached this point it
    }
    return false;
}

bool completedDiagonal(char* arr, int Row, int Column, string player){
    if (MatrixIsnByn(Row, Column)) {
        int c = Row; // c = Row = Column
        
        char TopLeft_prev = arr[0];
        for(int i=1; i<c; i++){      //first Diagonal
            if(TopLeft_prev == '\0' || arr[i*(c+1)] != TopLeft_prev){
                break;
            }
            if(i==c-1){
                cout <<"First Diagonal completed by player "<< player <<endl;
                return true;
            }
        }
        
        char TopRight_prev = arr[c-1];
        for (int i=2; i<=c; i++){    //Second Diagonal
            if(TopRight_prev == '\0' || arr[i*(c-1)]!=TopRight_prev){
                break;
            }
            if(i==c){
                cout <<"Second Diagonal completed by player "<< player <<endl;
                return true;
            }
        }
    }else{
        cout << "ERROR : No Diagonals possible" <<endl;
    }
    return false;
}


//Simple Welcome message
void welcomeMessage(){
    cout << endl;
    cout << "\t\t\t\t\t WELCOME TO TIC TAC TOE ! " <<endl<<endl;
}
void goodByMessage(){
    cout << "THANK YOU FOR PLAYING TIC TAC TOE" <<endl;
}
void wanToPlayMore(bool& wantToPlay){
    string input;
    cout << "IF you want to continue playing enter Y/N: ";
    cin  >> input;
    cout << endl;
    if (input == "Y") {
        wantToPlay = true;
    }else{
        wantToPlay = false;
    }
}

void setGameVariables(string& userSymbol, string& computerSymbol, string& player , int& Row, int& Column){
    cout << "Please Choose the size of your board : "<<endl;
    cout << "\t\t\t> Enter Row: ";
    cin >> Row;
    cout << "\t\t\t> Enter Colums: ";
    cin >> Column;
    cout <<endl;
    cout << "\t\t\t> Pick a Symbol 'X' or 'O' : ";
    cin >> userSymbol;
    cout << "\t\t\t> Who starts 'I' or 'Y': ";
    cin >> player;
    cout << "\t\t\t> Pick a number from 1 to "<< Row*Column << ":" << endl;
    cout <<endl;
    if(userSymbol == "X"){
        computerSymbol = "O";
    }else if(userSymbol == "O"){
        computerSymbol = "X";
    }else{
        cout << "INVELID SYMBOL" <<endl;
    }
}


//Creates the Tic Tac Toe 2D array dinamiclly by asking for the numbers of Rows and Colums
void createGameBoard(char* & board, const int Row, const int Column){
    board = new char[Row*Column];
}



//Fills the TicTacToe board with random binaries 0 and 1 for testing X = 1 and O = 0.
void fillBoard(char* arr, const int Row, const int Column){
    for (int i=0; i< Row*Column; i++) {
        //arr[i] = rand()%10;
        //arr[i] = round((double) rand() / (RAND_MAX));
        arr[i] = i+1; // ASCII code for white space
    }
}

//Displays an Array based on the specified Rows and Columns
void displayBoard(char* arr, const int Row, const int Column){
    int boardSize = Row*Column;
    for (int i=0; i<boardSize; i++){
        if (i==0 || i%Column == 0) {
            drawLine(Column);
            cout <<"\t\t\t|";
        }
        cout << setw(2);
        if (arr[i]=='\0') {
            cout << "   ";
        }else{
            cout <<arr[i]<<setw(2);
        }
        cout << "|";
    }
    drawLine(Column);
    cout <<endl<<endl;
}

void drawLine(int N){
    cout<<endl;
    cout << "\t\t\t";
    for (int i=0; i<N; i++) {
        cout << " ---";
    }
    cout<<endl;
}


//Returns the starting index of the ith Row (think of a 2D table with Rows and Columns) but stored in a linear array.
//Returns -1 if failed
int getStartingIndexOfRow(const int Row, const int Column, const int ithRow){
    if (ithRow == 1)
        return 0;
    else if(ithRow<=0 || ithRow>Row)
        return -1; //the ith row doesn't exist
    else
        return ( (ithRow-1) * Column);
}

//Displays the ith row of a matrix stored in an array.
void displayIthRow(char* arr, const int Row, const int Column, const int ithRow){
    cout << "ROW " << ithRow << " : ";
    int index=getStartingIndexOfRow(Row,Column,ithRow);
    for (int j=index, i=0; i<Column; j++, i++) {
        cout << " "<< arr[j] << "";
    }
    cout<<endl;
}

//Displays all rows of any matrix stored as a one dimention array
void displayAllRow(char* arr, const int Row, const int Column){
    for (int i=1; i<=Row; i++) {
        displayIthRow(arr,Row,Column,i);
    }
}

//To get the nth column we only need to know the indicesof the very first column. then we increment all of them ColumnTH times.
//How to get the indexes of the first column?
//We already know that 0 is the very first index of the veru first column. We need the vertical walk over Column 1.
// Consider C = number of Columns, and that the array is stored as [30,64,43,34,72,85,45,18,76,57,12,24}
//THE MATRIX IN OUR IMAGINATION IS: 4X3
// 30|64|43| Indices 0 | 1 | 2 |   The Columns are of indices 0 > 1 ...>2 So as  0*C = 0*3 = 0 and we only increment for the rest   =+1 > 1+1 = 2 ..
// 34|72|85|         3 | 4 | 5 |   MATRIX 4X3 = RXC           3 > 4 ...>5        1*C = 1*3 = 3                                      =+1 > 3+1 = 4
// 45|18|76|         6 | 7 | 8 |   C = Number of Columns = 3  6 > 7 ...>8        2*C = 2*3 = 6                                      =+1 > 6+1 = 7
// 57|12|24|         9 |10 | 11|   R = Number of Rows = 4     9 > 10...>11       3*C = 3*3 = 9                                      =+1 > 9+1 = 10
void getFirstColumnIndices(char* arr, const int Row, const int Column){
    for (int i=0; i<Row; i++) {
        cout << arr[i*Column] << " ";
    }
    cout <<endl;
}

//To get all incedes of the matrix
void displayAllColumnIndices(char* arr, const int Row, const int Column){
    for (int j=0; j<Column; j++) {
        cout << "COLUMN " << j+1 << " : ";
        for (int i=0; i<Row; i++) {
            cout << arr[(i*Column)+j] << " ";
        }
        cout <<endl;
    }
}
/*
 How to get the array of diagonal: THERE IS A PATTERN
 First the Matrix needs to be N x N Matrix
 
 0 1             00      ,    03                                 |   01      ,       02                                          c=2
 2 3             0*(c+1) ,   1(c+1)                              |   1*(c-1) ,    2*(c-1)
 
 0 1 2           00      ,    04     ,   08                      |  02       ,       04      ,       06                          c=3
 3 4 5           0*4     ,   1*4     ,  2*4                      | 1*2       ,       2*2     ,       3*2
 6 7 8           0*(c+1) , 1*(c+1)   , 2*(c+1)                   | 1*(c-1)   ,      2*(c-1)  ,       3*(c-1)
 
 0  1  2  3     00      ,   05      ,   10      ,   15          |   3       ,       6       ,         9       ,     12          c=4
 4  5  6  7     0*(c+1) , 1*(c+1)   , 2*(c+1)   ,   3*(c+1)     | 1*(c-1)   ,      2*(c-1)  ,       3*(c-1)   ,     4*(c-1)
 8  9 10 11
 12 13 14 15
 
 00 01 02 03 04  00,06,12,18,24  | 04,08,12,16,20   5
 05 06 07 08 09
 10 11 12 13 14  0*(c+1),1*(c+1),2*(c+1),3*(c+1),4*(c+1) | 1*(c-1),2*(c-1),3*(c-1),4*(c-1),5*(c-1)   => TRUE
 15 16 17 18 19
 20 21 22 23 24
 */
bool MatrixIsnByn(const int Row, const int Column){
    return (Row==Column);
}

void displayAllDiagonals(char* arr, const int Row, const int Column){
    if (MatrixIsnByn(Row, Column)) {
        int c = Row; // c = Row = Column
        cout << "First Diagonal: " ;
        for(int i=0; i<c; i++)//first Diagonal
            cout << arr[i*(c+1)] <<" ";
        cout << endl << "Second Diagonal: ";
        for (int i=1; i<=c; i++)
            cout << arr[i*(c-1)]<< " ";
        cout<<endl;
    }else{
        cout << "No Diagonals possible" <<endl;
    }
}




