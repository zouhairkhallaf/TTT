//
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
void gameSettings(string& symbol , string& player , int& Row, int&Column);
char* createDynamicArray(const int Row, const int Column);
template <typename ItemType>
void fillBoard(ItemType* arr, const int Row, const int Column);
template <typename ItemType>
void displayBoard(ItemType* board, const int Row, const int Column);
int getStartingIndexOfRow(const int Row, const int Column, const int ithRow);
template <typename ItemType>
void displayIthRow(ItemType* arr, const int Row, const int Column, const int ithRow);
template <typename ItemType>
void displayAllRow(ItemType* arr, const int Row, const int Column);
template <typename ItemType>
void getFirstColumnIndices(ItemType* arr, const int Row, const int Column);
template <typename ItemType>
void displayAllColumnIndices(ItemType* arr, const int Row, const int Column);
bool MatrixIsnByn(const int Row, const int Column);
template <typename ItemType>
void displayAllDiagonals(ItemType* arr, const int Row, const int Column);
template <typename ItemType>
bool isPlayerWinner(ItemType* arr, int Row, int Column, int playerNumber);
template <typename ItemType>
bool completedRow(ItemType* arr, int Row, int Column, int playerNumber);
bool validMove(char* arr, string input, string symbol);



int main(int argc, const char * argv[]) {
    string symbol;
    string input;
    string player;
    string move;
    bool gameOn = true;
    int R=0;
    int C=0;
    
    welcomeMessage();
    char* board = createDynamicArray(R, C);
    gameSettings(symbol,player,R,C);
    

    
    
    cout << "\t NEW GAME " <<endl<<endl;

    while (gameOn){
    //Loog Starts here
        
    if(symbol == "I"){
        cout << "\t\t\t\t Goo ahead and make a move, your turn" <<endl;
        //Do nothing
    }else if(symbol == "Y"){
        //Computer Plays and board will display the first move
        cout << "\t\t\t\t I start ... It's My turn" <<endl;
        computerPlay();
    }
        
        
    displayBoard(board, R, C);
    cout <<endl;
    cin  >> move;
        if (validMove(board, move, symbol)) {

            
            
            makeMove();
            if (isWinner()) {
                gameOn = false;
            }
        }else{
            cout << "Not A valid Move Try another position again"<<endl;
            continue;
        }
    }
    
    //ROWS
    //displayAllRow(board, R,C);
    
    //COLUMS
    //getFirstColumnIndices(board, R,C);
    //displayAllColumnIndices(board, R,C);
    //displayAllDiagonals(board, R,C);
    
    return 0;
}

//randomly Picks an empty index and places the symbol
void computerPlay(char* arr, string symbol, int Row, int Column){
    //Make a new array holding indecies that are empty
    vector<int> temp;
    for (int i=0; i<Row*Column; i++) { // stores the empty locations in a vector
        if (arr[i]==32) {
            temp.push_back(i);
        }
    }
}


bool validMove(char* arr, string input){
    return (arr[stoi(input)]==32);
}

bool makeMove(char* arr, string input, char symbol){
    arr[stoi(input)] = symbol;
}
//Simple Welcome message
void welcomeMessage(){
    cout << endl;
    cout << "\t\t\t\t\t WELCOME TO TIC TAC TOE ! " <<endl<<endl;
}

void gameSettings(string& symbol , string& player , int& Row, int& Column){
    cout << "Please Choose the size of your board : "<<endl;
    cout << "\t\t\t> Enter Row: ";
    cin >> Row;
    cout << "\t\t\t> Enter Colums: ";
    cin >> Column;
    cout <<endl;
    cout << "Please pick the symbol your would like to use"<<endl;
    cout << "\t\t\t> Enter 'X' or 'O' : ";
    cin >> symbol;
    cout << "Please pick the player you wish to start "<<endl;
    cout << "\t\t\t> Enter 'I' or 'Y': ";
    cin >> player;
    cout << "Please pick a number from 1 to "<< Row*Column << " to place the position in the board" << endl;
    cout <<endl;
}


//Creates the Tic Tac Toe 2D array dinamiclly by asking for the numbers of Rows and Colums
char* createDynamicArray(const int Row, const int Column){
    char* arr = new char[Row*Column];
    return arr;
}


//Fills the TicTacToe board with random binaries 0 and 1 for testing X = 1 and O = 0.
template <typename ItemType>
void fillBoard(ItemType* arr, const int Row, const int Column){
    srand (time(NULL));
    for (int i=0; i< Row*Column; i++) {
        //arr[i] = rand()%10;
        //arr[i] = round((double) rand() / (RAND_MAX));
        arr[i] = 32; // ASCII code for white space
    }
}
 
//Displays an Array based on the specified Rows and Columns
template <typename ItemType>
void displayBoard(ItemType* arr, const int Row, const int Column){
    for (int i=0, c=1 ; i<Row*Column; i++, c++) {
        cout<<"\t"<<arr[i] << " \t|";
        if ( c % Column == 0 ) {
            cout<<endl;
            cout<<"\t----------------------------"<<endl;
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
template <typename ItemType>
void displayIthRow(ItemType* arr, const int Row, const int Column, const int ithRow){
    cout << "ROW " << ithRow << " : ";
    int index=getStartingIndexOfRow(Row,Column,ithRow);
    for (int j=index, i=0; i<Column; j++, i++) {
            cout << " "<< arr[j] << "";
    }
    cout<<endl;
}

//Displays all rows of any matrix stored as a one dimention array
template <typename ItemType>
void displayAllRow(ItemType* arr, const int Row, const int Column){
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
template <typename ItemType>
void getFirstColumnIndices(ItemType* arr, const int Row, const int Column){
    for (int i=0; i<Row; i++) {
        cout << arr[i*Column] << " ";
    }
    cout <<endl;
}

//To get all incedes of the matrix
template <typename ItemType>
void displayAllColumnIndices(ItemType* arr, const int Row, const int Column){
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

template <typename ItemType>
void displayAllDiagonals(ItemType* arr, const int Row, const int Column){
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

//We check if Player is winner if completed a row || Column || Diagonal (if any)
template <typename ItemType>
bool isPlayerWinner(ItemType* arr, int Row, int Column, int playerNumber){
    //return (completedRow(arr)||completedColumn(arr)||completedDiagonal(arr));
    return completedRow(arr,Row,Column,playerNumber);
}

template <typename ItemType>
bool completedRow(ItemType* arr, int Row, int Column, int playerNumber){
    for (int i=1; i<=Row; i++) { //i is the ith Row example (first Row, Second, Third ....)
        int index=getStartingIndexOfRow(Row,Column,i);
        ItemType prev = arr[index];
        for (int j=index, i=0; i<Column; j++, i++) {
            if(prev != arr[j]){
                break;
            }else{
                cout << " PLAYER "<< playerNumber <<" WINNER IN ROW "<< i << endl;
            }
        }
    }
}



