// zouhair khallaf
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
bool isPlayerWinner(char* arr, int Row, int Column, string playerNumber);
bool completedRow(char* arr, int Row, int Column, int playerNumber);
bool validMove(char* arr, string input, string symbol);
void goodByMessage();
void wanToPlayMore(bool& wantToPlay);
void playGame(char* board, const int rows, const int columns, bool& gameOn, string userSymbol,string computerSymbol, string& playerTurn);
void playComputer(char* board, const int rows, const int columns, string computerSymbol);
void playUser(char* board, const int rows, const int columns, string userSymbol);
//----------------UTILITIES------------------------------------------------------------------
int howManyEmptySpotsInBoard(char* board, const int boardSize);




//----------------------------------------------------------------------------------------MAIN()



int main(int argc, const char * argv[]) {
    srand (time(NULL) );
    string userSymbol,computerSymbol,playerTurn;
    char* board;
    bool gameOn = true, wantToPlay=true;
    int rows=0, columns=0;
    
    welcomeMessage();
    while(wantToPlay){
        createGameBoard(board, rows, columns);
        setGameVariables(userSymbol,computerSymbol,playerTurn,rows,columns);
        cout << "\t GAME ON " <<endl<<endl;
        while(gameOn){
            playGame(board, rows, columns, gameOn,userSymbol,computerSymbol, playerTurn);
            displayBoard(board, rows, columns);
        }
        cout << "\t GAME OVER " <<endl<<endl;
        wanToPlayMore(wantToPlay);
    }
    goodByMessage();

    return 0;
}


//----------------------------------------------------------------------------------------FUNCTIONS (needs house keeping)


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
    cout << "\t\t\t .My Turn" <<endl;
    int boardSize = rows*columns;
    //Count the empty positions in the board and store it in C
    int C = howManyEmptySpotsInBoard(board,boardSize);
    //Build an new array named Arr of size C.
    int* Arr = new int[C];
    //Store empty positions indices from the board into the Arr[C]
    for (int i=0, j=0; i<boardSize; i++) {
        if (board[i] == '\0'){
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
        if (board[i]=='\0')
            c++;
    }
    return c;
}


void playUser(char* board, const int rows, const int columns, string userSymbol){
    cout << "\t\t\t .Your Turn" <<endl;
    int boardSize = rows*columns;
    bool  badindex = true;
    int input;
    do {
        //Get the user input
        cout << "\t\t>Pick a position 1-" << boardSize << ": ";
        cin >> input;
        int index = input - 1;
        if(index<0 || index>=boardSize){ // Checks if input is out of range
            continue;
        }else{
            //Count the empty positions in the board and store it in C
            int C = howManyEmptySpotsInBoard(board,boardSize);
            //Build an new array named Arr of size C.
            int* Arr = new int[C];
            //Store empty positions indices from the board into the Arr[C]
            for (int i=0, j=0; i<boardSize; i++) {
                if (board[i] == '\0'){
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
    board[(int)index] = userSymbol[0]; //Since we are storing one character instead of a string.
}


/*
//We check if Player is winner if completed a row || Column || Diagonal (if any)
bool isPlayerWinner(char* arr, int Row, int Column, string playerNumber){
    //return (completedRow(arr)||completedColumn(arr)||completedDiagonal(arr));
    if (completedRow(arr,Row,Column)){
        cout << "\t\t\t\t> Row "   << Row    << " completed " << endl;
        return true;
    }
    if (completedColumn(arr,Row,Column)){
        cout << "\t\t\t\t> Column "<< Column << " completed " << endl;
        return true;
    }
    if (completedDiagonal()){
        cout << "\t\t\t\t> Diagonal completed " << endl;
        return true;
    }
    
    return false;
}
bool completedRow(string* arr, int Row, int Column){
    for (int i=1; i<=Row; i++) { //i is the ith Row example (first Row, Second, Third ....)
        int index=getStartingIndexOfRow(Row,Column,i);
        string prev = arr[index];
        for (int j=index, i=0; i<Column; j++, i++) {
            if(prev != arr[j]){
                break;
            }else{
                return true; // wins a row;
            }
        }
    }
    return false;
}
*/


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
    cout << "IF you want to continue playing enter YES/NO: ";
    getline(cin,input);
    if (input == "YES") {
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
    cout << "\t\t\t> Pick a Symbol '1' or '2' : ";
    cin >> userSymbol;
    cout << "\t\t\t> Who starts 'I' or 'Y': ";
    cin >> player;
    cout << "\t\t\t> Pick a number from 1 to "<< Row*Column << ":" << endl;
    cout <<endl;
    if(userSymbol == "1"){
        computerSymbol = "2";
    }else if(userSymbol == "2"){
       computerSymbol = "1";
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
        arr[i] = '0'; // ASCII code for white space
    }
}
 
//Displays an Array based on the specified Rows and Columns
void displayBoard(char* arr, const int Row, const int Column){
    for (int i=0, c=1 ; i<Row*Column; i++, c++) {
        cout<<"  " << arr[i]<< "  ";
        if ( c % Column == 0 ) {
            cout<<endl;
            cout<<"  ---------"<<endl;
        }else{
            cout<< " | ";
        }
    }
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




