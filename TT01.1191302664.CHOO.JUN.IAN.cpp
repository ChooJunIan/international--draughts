/**********|**********|**********|
Program: TT01.1191302664.CHOO.JUN.IAN.cpp
Course: Data Structures and Algorithms
Year: 2019/20 Trimester 2
Name: CHOO JUN IAN
ID: 1191302664
Lecture Section: TCP1101
Tutorial Section: TT01
Email: ianchoo2000@gmail.com
Phone: 013-6296810
**********|**********|**********/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
using namespace std;

void newGame(); //assigns value to the array.
void mainMenu();//opens up the main menu with the option to play a New Game or Exit
void setBoard(int [10][10], int&, int&); // sets up the checkers board.
void playerOne(int [10][10], int&, int&);//shows the menu for the player 1's next step of action
void playerTwo(int [10][10], int&, int&);//shows the menu for the player 2's next step of action
void playerOneMove(int [10][10], int&, int&); // indicate player 1's turn
void playerTwoMove(int [10][10], int&, int&); // indicate player 2's turn
void saveFilePlayerOne(int [10][10], int&, int&); //to save the current board game for player 1
void saveFilePlayerTwo(int [10][10], int&, int&); //to save the current board game for player 2
void loadFilePlayerOne(int [10][10], int&, int&); //to load the save file of player 1
void loadFilePlayerTwo(int [10][10], int&, int&); //to load the save file of player 2
void checkCrown(int[10][10]);//check for crown pieces
void clearScreen(); //to clear the screen.

int main()
{
  mainMenu();
  return 0;
}

//*****************************************************************************
void newGame() //when this function is called, a new game will start. A 2D array will be assigned the following values shown for each row and column.
{
    int board[10][10] = {{3,2,3,2,3,2,3,2,3,2}, {2,3,2,3,2,3,2,3,2,3}, {3,2,3,2,3,2,3,2,3,2}, {2,3,2,3,2,3,2,3,2,3}, {3,4,3,4,3,4,3,4,3,4}, {4,3,4,3,4,3,4,3,4,3},
                        {3,1,3,1,3,1,3,1,3,1}, {1,3,1,3,1,3,1,3,1,3}, {3,1,3,1,3,1,3,1,3,1}, {1,3,1,3,1,3,1,3,1,3}};

    int countA = 0; // initialize the number of checker pieces on the baord
    int countB = 0;

    setBoard(board, countA, countB);// sets the board

    playerOne(board, countA, countB);// goes to player 1
}

//*****************************************************************************
void setBoard(int currentBoard[10][10], int& countA, int& countB)//sets up the checkers board
{
    clearScreen(); //clears the top part of the screen (ie: the menu selection) to show only the board.

    cout << "   |---+---+---+---+---+---+---+---+---+---|" << endl; //the first line of the board

    for (int row = 0; row < 10; row++) //the nested loop to form the internal parts of the board
      {
        int outNumber = row+1;
        if (row<9)
        cout << outNumber << "  |";
        else
        cout << outNumber << " |";
        for (int col = 0; col <10 ; col++)
         {
            if(currentBoard[row][col] == 1)
            cout << " a |" ;
            else if(currentBoard[row][col] == 2)
            cout << " b |" ;
            else if(currentBoard[row][col] == 3)
            cout << "   |" ;
            else if(currentBoard[row][col] == 4)
            cout << " # |" ;
            else if(currentBoard[row][col] == 5)
            cout << " A |" ;
            else if(currentBoard[row][col] == 6)
            cout << " B |";
         }
         cout << endl << "   |---+---+---+---+---+---+---+---+---+---|" << endl;
      }
      cout <<"     a   b   c   d   e   f   g   h   i   j" << endl; //the alphabets at the bottom of the board

      countA = 0; //keeps count of the number of checker pieces on the board
      countB = 0;
      bool winCondition = false; //to check for any win condition
      for(int i = 0; i < 10; i++)
      {
        for(int j = 0; j < 10; j++)
        {

          if(currentBoard[i][j] == 1 || currentBoard[i][j] == 5)
          countA++;
          else if(currentBoard[i][j] == 2 || currentBoard[i][j] == 6)
          countB++;
        }
      }

      if(countA == 0)//player 1 condition
      {
        cout << "Player 1 has run out of checker pieces!" << endl;
        winCondition = true;
      }
      else if(countB == 0)//player 2 condition
      {
        cout << "Player 2 has run out of checker pieces!" << endl;
        winCondition = true;
      }

      while(winCondition == true)
      {
        if(countA == 0)
        {
          cout << "The WINNER is Player 2!!!" << endl;
          cout << endl;
          mainMenu();
        }
        else if(countB == 0)
        {
          cout << "The WINNER is player 1!!!" << endl;
          cout << endl;
          mainMenu();
        }
      }
}

//*****************************************************************************
void playerOne(int currentBoard[10][10], int& countA, int& countB)//shows the menu for the player 1's next step of action
{
  int option;
  cout << "Player 1 chess piece number(A/a): " << countA << endl;
  cout << "Player 2 chess piece number(B/b): " << countB << endl;
  cout << "Player 1, choose your option: " << endl;
  cout << "1. Move  2. Save Game  3. Load Game  4. Exit Game" << endl;
  cin >> option;

  while(option < 1 || option > 4)
  {
    cout << "Please insert a number between 1 to 4 ONLY" << endl;
    cin >> option;
    cout << endl;
  }

  switch(option){
    case 1:
    playerOneMove(currentBoard, countA, countB);//indicate player 1's turn
    case 2:
    saveFilePlayerOne(currentBoard, countA, countB);//to save the current board game for player 1
    break;
    case 3:
    loadFilePlayerOne(currentBoard, countA, countB);//to load the save file of player 1
    break;
    case 4:
    mainMenu();
  }
}

//*****************************************************************************
void playerOneMove(int playBoard[10][10], int& countA, int& countB)//indicate player 1's turn
{
    int pickRow, moveRow, currentRow; //coordinates of the row, seen by the player on the board
    char pickCol, moveCol, currentCol; // coordinates of the column, seen by the player on the board
    cout << "Player 1, make your move " << endl;
    cout << "Choose your chess piece. EG: 7b " << endl;
    cin >> pickRow >> pickCol;
    cout << endl;
    pickRow = pickRow - 1; //corresponds to the actual value of the row in array
    pickCol = static_cast<int>(pickCol) - 97; //corresponds to the actual value of the column in array

    while (playBoard[pickRow][pickCol]!=1 && playBoard[pickRow][pickCol] != 5) //to prevent selection of any pieces other than 'a' or 'A'
    {
      cout << "Invalid move - You can only pick checker piece 'a' or 'A'." << endl;
      cout << "Choose another checker piece. " <<endl;
      cin >> pickRow >> pickCol;
      pickRow = pickRow - 1;
      pickCol = static_cast<int>(pickCol) - 97;
    }

    if(playBoard[pickRow][pickCol]==1)//to check the validity of the movement of checker piece 'a'
    {
      while ((playBoard[pickRow-1][pickCol+1]!=4 && playBoard[pickRow-1][pickCol-1]!=4) && (playBoard[pickRow-2][pickCol+2]!=4 && playBoard[pickRow-2][pickCol-2]!=4)) //to prevent selection of pieces that are 'a', but cannot be moved to any new destination.
      {
        cout << "Invalid move - You can only pick checker piece that is not stuck." << endl;
        cout << "Choose another checker piece. " <<endl;
        cin >> pickRow >> pickCol;
        pickRow = pickRow - 1;
        pickCol = static_cast<int>(pickCol) - 97;
      }
    }

    else if(playBoard[pickRow][pickCol]==5)//to check the validity of the movement of the checker piece 'A'
    {
      while(playBoard[pickRow-1][pickCol-1]==1 && playBoard[pickRow-1][pickCol+1]==1 && playBoard[pickRow+1][pickCol-1]==1 && playBoard[pickRow+1][pickCol+1]==1)//the specific 'A' piece cannot be moved if the next piece in all 4 direction are checker pieces 'a'
      {
        cout << "Invalid move - You can only pick checker piece that is not stuck." << endl;
        cout << "Choose another checker piece. " <<endl;
        cin >> pickRow >> pickCol;
        pickRow = pickRow - 1;
        pickCol = static_cast<int>(pickCol) - 97;
      }
    }


    if(playBoard[pickRow][pickCol]==1)//the movement/capture that involves checker piece 'a'
    {
      cout << "Choose your destination. EG:6a" << endl;
      cin >> moveRow >> moveCol;
      moveRow = moveRow - 1; //corresponds to the actual value of the row in array
      moveCol = static_cast<int>(moveCol) - 97; //corresponds to the actual value of the column in array
      int endMove = 0; //a counter, acts as a way to exit the while loop
      int capMove = 0;

      while (endMove==0)
      {
        if (pickRow-1 == moveRow && pickCol-1 == moveCol) //ensures that the destination of the coordinates picked are diagonally upwards left from the chess piece.
        {
          playBoard[pickRow][pickCol] = 4; //swaps the value of 'a' and '#'
          playBoard[moveRow][moveCol] = 1;
          endMove=1;
        }
        else if (pickRow-1 == moveRow && pickCol+1 == moveCol) //ensures that the destination of the coordinates picked are diagonally upwards right from the chess piece.
        {
          playBoard[pickRow][pickCol] = 4; //swaps the value of 'a' and '#'
          playBoard[moveRow][moveCol] = 1;
          endMove=1;
        }
        else if((pickRow-2 == moveRow && pickCol-2 == moveCol) && (playBoard[pickRow-1][pickCol-1]==2))//capture piece that is diagonally upwards left
        {
          playBoard[pickRow][pickCol] = 4;
          playBoard[pickRow-1][pickCol-1] = 4;
          playBoard[moveRow][moveCol] = 1;
          countB--;
          endMove=1;
          capMove=1;
        }
        else if((pickRow-2 == moveRow && pickCol+2 == moveCol) && (playBoard[pickRow-1][pickCol+1]==2))//capture piece that is diagonally upwards right
        {
          playBoard[pickRow][pickCol] = 4;
          playBoard[pickRow-1][pickCol+1] = 4;
          playBoard[moveRow][moveCol] = 1;
          countB--;
          endMove=1;
          capMove=1;
        }
        else //to catch any invalid inputs of the destination picked to move the chess piece.
        {
          cout << "Invalid input - you cannot choose this location." << endl;
          cout << "Choose your destination. EG:6a" << endl;
          cin >> moveRow >> moveCol;
          moveRow = moveRow - 1;
          moveCol = static_cast<int>(moveCol) - 97;
          endMove=0;
        }
      }

      checkCrown(playBoard);
      setBoard(playBoard, countA, countB);//sets the new board

      while((((playBoard[moveRow-2][moveCol-2]==4) && (playBoard[moveRow-1][moveCol-1]==2)) || ((playBoard[moveRow-2][moveCol+2]==4) && (playBoard[moveRow-1][moveCol+1]==2)))&&(capMove==1))//checks for multi-capture.
      {
          char option;
          cout << "There is/are possible captures that you can make, do you want to do so?\nInput 'Y' for YES or 'N' for NO" << endl;
          cin >> option;
            while (option != 'Y' && option != 'y' && option != 'N' && option != 'n')
            {
                cout << "Please input only 'Y' or 'N'" << endl;
                cin >> option;
            }

            if(option == 'Y' || option == 'y')
            {
              currentRow = moveRow;
              currentCol = moveCol;
              cout << "Choose your destination. EG:6a" << endl;
              cin >> moveRow >> moveCol;
              moveRow = moveRow - 1; //corresponds to the actual value of the row in array
              moveCol = static_cast<int>(moveCol) - 97; //corresponds to the actual value of the column in array
              int endMove = 0; //a counter, acts as a way to exit the while loop
              int capMove = 0;

              if (endMove==0)
              {
                if((currentRow-2 == moveRow && currentCol-2 == moveCol) && (playBoard[currentRow-1][currentCol-1]=2))//capture piece that is diagonally upwards left
                {
                  playBoard[moveRow][moveCol] = 1;
                  playBoard[currentRow][currentCol] = 4;
                  playBoard[moveRow+1][moveCol+1] = 4;
                  countB--;
                  endMove=1;
                  capMove=1;
                }
                else if((currentRow-2 == moveRow && currentCol+2 == moveCol) && (playBoard[currentRow-1][currentCol+1]=2))//capture piece that is diagonally upwards right
                {
                  playBoard[moveRow][moveCol] = 1;
                  playBoard[currentRow][currentCol] = 4;
                  playBoard[moveRow+1][moveCol-1] = 4;
                  countB--;
                  endMove=1;
                  capMove=1;
                }
                else //to catch any invalid inputs of the destination picked to move the chess piece.
                {
                  cout << "Invalid input - you cannot choose this location." << endl;
                  cout << "Choose your destination. EG:6a" << endl;
                  cin >> moveRow >> moveCol;
                  moveRow = moveRow - 1;
                  moveCol = static_cast<int>(moveCol) - 97;
                  endMove=0;
                }

                clearScreen();
                checkCrown(playBoard);
                setBoard(playBoard, countA, countB);//sets the new board

                if(((playBoard[moveRow-2][moveCol-2]==4) && (playBoard[moveRow-1][moveCol-1]==2)) || ((playBoard[moveRow-2][moveCol+2]==4) && (playBoard[moveRow-1][moveCol+1]==2))&&(capMove==1))//checks for multi-capture
                {
                  capMove=0;
                  continue;
                }
                playerTwo(playBoard, countA, countB);
              }
            }

            else if(option == 'N' || option == 'n')
            {
              clearScreen();
              setBoard(playBoard, countA, countB);
              playerTwo(playBoard, countA, countB);
            }
              break;
      }
      playerTwo(playBoard, countA, countB);//goes to player Two's turn
    }
}
//*****************************************************************************
void playerTwo(int currentBoard[10][10], int& countA, int& countB)//shows the menu for the player 2's next step of action
{
  int option;
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      if(currentBoard[i][j] == 'a')
      countA++;
      else if(currentBoard[i][j] == 'b')
      countB++;
    }
  }

  cout << "Player 1 chess piece number(A/a): " << countA << endl;
  cout << "Player 2 chess piece number(B/b): " << countB << endl;
  cout << "Player 2, choose your option: " << endl;
  cout << "1. Move  2. Save Game  3. Load Game  4. Exit Game" << endl;
  cin >> option;

  while(option < 1 || option > 4){
    cout << "Please insert a number between 1 to 4 ONLY" << endl;
    cin >> option;
    cout << endl;
  }

  switch(option){
    case 1:
    playerTwoMove(currentBoard, countA, countB);// indicate player 2's turn
    case 2:
    saveFilePlayerTwo(currentBoard, countA, countB);//to save the current board game for player 2
    break;
    case 3:
    loadFilePlayerTwo(currentBoard, countA, countB);//to load the save file of player 2
    break;
    case 4:
    mainMenu();
    break;
  }
}

//*****************************************************************************
void playerTwoMove(int playBoard[10][10], int& countA, int& countB)// indicate player 2's turn
{
  int pickRow, moveRow, currentRow; //coordinates of the row, seen by the player on the board
  char pickCol, moveCol, currentCol;// coordinates of the column, seen by the player on the board
  cout << "Player 2, make your move " << endl;
  cout << "Choose your chess piece. EG: 4c " << endl;
  cin >> pickRow >> pickCol;
  cout << endl;
  pickRow = pickRow - 1; //corresponds to the actual value of the row in array
  pickCol = static_cast<int>(pickCol) - 97; //corresponds to the actual value of the column in array

  while (playBoard[pickRow][pickCol]!= 2 && playBoard[pickRow][pickCol] != 6) //to prevent selection of any pieces other than 'b' or 'B'
  {
    cout << "Invalid move - You can only pick checker piece 'b' or 'B'." << endl;
    cout << "Choose another checker piece. " <<endl;
    cin >> pickRow >> pickCol;
    pickRow = pickRow - 1;
    pickCol = static_cast<int>(pickCol) - 97;
  }

  if(playBoard[pickRow][pickCol]==2)
  {
    while((playBoard[pickRow+1][pickCol+1]!=4 && playBoard[pickRow+1][pickCol-1]!=4) && (playBoard[pickRow+2][pickCol-2]!=4 && playBoard[pickRow+2][pickCol+2]!=4))//to prevent selection of pieces that are 'b', but cannot be moved to any new destination.
    {
      cout << "Invalid move - You can only pick checker piece that is not stuck." << endl;
      cout << "Choose another checker piece. " <<endl;
      cin >> pickRow >> pickCol;
      pickRow = pickRow - 1;
      pickCol = static_cast<int>(pickCol) - 97;
    }
  }

  else if(playBoard[pickRow][pickCol]==6)
  {
    while(playBoard[pickRow-1][pickCol-1]==2 && playBoard[pickRow-1][pickCol+1]==2 && playBoard[pickRow+1][pickCol-1]==2 && playBoard[pickRow+1][pickCol+1]==2)//the specific 'B' piece cannot be moved if the next piece in all 4 direction are checker pieces 'b'
    {
      cout << "Invalid move - You can only pick checker piece that is not stuck. krappa " << endl;
      cout << "Choose another checker piece. " <<endl;
      cin >> pickRow >> pickCol;
      pickRow = pickRow - 1;
      pickCol = static_cast<int>(pickCol) - 97;
    }
  }


  if(playBoard[pickRow][pickCol]==2)
  {
    cout << "Choose your destination. EG:5b" << endl;
    cin >> moveRow >> moveCol;
    moveRow = moveRow - 1; //corresponds to the actual value of the row in array
    moveCol = static_cast<int>(moveCol) - 97; //corresponds to the actual value of the column in array
    int endMove = 0; //a counter, acts as a way to exit the while loop
    int capMove = 0;

    while (endMove==0)
    {
      if (pickRow+1 == moveRow && pickCol-1 == moveCol) //ensures that the destination of the coordinates picked are diagonally donwards left from the chess piece.
      {
        playBoard[pickRow][pickCol] = 4; //swaps the value of 'b' and '#'
        playBoard[moveRow][moveCol] = 2;
        endMove=1;
      }
      else if (pickRow+1 == moveRow && pickCol+1 == moveCol) //ensures that the destination of the coordinates picked are diagonally downwards right from the chess piece.
      {
        playBoard[pickRow][pickCol] = 4; //swaps the value of 'b' and '#'
        playBoard[moveRow][moveCol] = 2;
        endMove=1;
      }
      else if((pickRow+2 == moveRow && pickCol-2 == moveCol) && (playBoard[pickRow+1][pickCol-1]==1))//capture diagonally downwards left
      {
        playBoard[pickRow][pickCol] = 4;
        playBoard[pickRow+1][pickCol-1] = 4;
        playBoard[moveRow][moveCol] = 2;
        countA--;
        endMove=1;
        capMove=1;
      }
      else if((pickRow+2 == moveRow && pickCol+2 == moveCol) && (playBoard[pickRow+1][pickCol+1]==1))//capture diagonally downwards right
      {
        playBoard[pickRow][pickCol] = 4;
        playBoard[pickRow+1][pickCol+1] = 4;
        playBoard[moveRow][moveCol] = 2;
        countA--;
        endMove=1;
        capMove=1;
      }
      else //to catch any invalid inputs of the destination picked to move the chess piece.
      {
        cout << "Invalid input - you cannot choose this location." << endl;
        cout << "Choose your destination. EG:6a" << endl;
        cin >> moveRow >> moveCol;
        moveRow = moveRow - 1;
        moveCol = static_cast<int>(moveCol) - 97;
        endMove=0;
        capMove=0;
      }
    }

    checkCrown(playBoard);
    setBoard(playBoard, countA, countB);

    while((((playBoard[moveRow+2][moveCol-2]==4) && (playBoard[moveRow+1][moveCol-1]==1)) || ((playBoard[moveRow+2][moveCol+1]==4) && (playBoard[moveRow+1][moveCol+1]==1)))&&(capMove==1))//check for multi-capture
    {
      char option;
      cout << "There is/are possible captures that you can make, do you want to do so?\nInput 'Y' for YES or 'N' for NO" << endl;
      cin >> option;
      while (option != 'Y' && option != 'y' && option != 'N' && option != 'n')
      {
        cout << "Please input only 'Y' or 'N'" << endl;
        cin >> option;
      }

      if(option == 'Y' || option == 'y')
      {
        currentRow = moveRow;
        currentCol = moveCol;
        cout << "Choose your destination. EG:6a" << endl;
        cin >> moveRow >> moveCol;
        moveRow = moveRow - 1; //corresponds to the actual value of the row in array
        moveCol = static_cast<int>(moveCol) - 97; //corresponds to the actual value of the column in array
        int endMove = 0; //a counter, acts as a way to exit the while loop
        int capMove = 0;

        if (endMove==0)
        {
          if((currentRow+2 == moveRow && currentCol-2 == moveCol) && (playBoard[currentRow+1][currentCol-1]=1))//capture piece that is diagonally downwards left
          {
            playBoard[moveRow][moveCol] = 2;
            playBoard[currentRow][currentCol] = 4;
            playBoard[currentRow+1][currentCol-1] = 4;
            countA--;
            endMove=1;
            capMove=1;
          }
          else if((currentRow+2 == moveRow && currentCol+2 == moveCol) && (playBoard[currentRow+1][currentCol+1]=2))//capture piece that is diagonally downwards right
          {
            playBoard[moveRow][moveCol] = 2;
            playBoard[currentRow][currentCol] = 4;
            playBoard[currentRow+1][currentCol+1] = 4;
            countA--;
            endMove=1;
            capMove=1;
          }
          else //to catch any invalid inputs of the destination picked to move the chess piece.
          {
            cout << "Invalid input - you cannot choose this location." << endl;
            cout << "Choose your destination. EG:6a" << endl;
            cin >> moveRow >> moveCol;
            moveRow = moveRow - 1;
            moveCol = static_cast<int>(moveCol) - 97;
            endMove=0;
          }

          checkCrown(playBoard);
          clearScreen();
          setBoard(playBoard, countA, countB);//sets the new board

          if(((playBoard[moveRow+2][moveCol-2]==4) && (playBoard[moveRow+1][moveCol-1]==1)) || ((playBoard[moveRow+2][moveCol+2]==4) && (playBoard[moveRow+1][moveCol+1]==1))&&(capMove==1))
          {
            capMove=0;
            continue;
          }
          playerOne(playBoard, countA, countB);
        }
      }
      else if(option == 'N' || option == 'n')
      {
        clearScreen();
        setBoard(playBoard, countA, countB);
        playerOne(playBoard, countA, countB);
      }
      break;
    }
    playerOne(playBoard, countA, countB);
  }

}

//*****************************************************************************
void mainMenu()//opens up the main menu with the option to play a New Game or Exit
{
  cout << endl;
  int choice;
  cout << "Welcome to International Checkers!" << endl;
  cout << "Select your option" << endl;
  cout << "1. New Game\n2. Exit" << endl;
  cin >> choice;

  while (choice < 1 || choice > 2) //to catch the error for inputting values not 1 or 2
  {
    cout << "Invalid input - Please choose 1 or 2" << endl << endl;
    cin >> choice;
  }

  switch (choice) //menu selection for the game
    {
      case 1:
      newGame();
      break;
      case 2:
      cout << "Bye see you again!" << endl;
      break;
    }
}

//*****************************************************************************
void clearScreen() //clears the screen
{
  system( "cls" );
}

//*****************************************************************************
void saveFilePlayerOne(int playBoard[10][10], int& countA, int& countB)//to save the current board game for player 1
{
  ofstream outputSave;
  outputSave.open("saveFilePlayer1.txt");

  for (int i =0; i < 10; i ++)
  {
    for (int j = 0; j < 10; j++)
    {
      outputSave << playBoard[i][j];
    }
    outputSave << endl;
  }
  outputSave.close();
  cout << "Saved game!" << endl;
  cout << endl;
  playerOne(playBoard, countA, countB);//after saving, goes to player 1's turn
}

//*****************************************************************************
void saveFilePlayerTwo(int playBoard[10][10], int& countA, int& countB)//to save the current board game for player 2
{
  ofstream outputSave;
  outputSave.open("saveFilePlayer2.txt");

  for (int i =0; i < 10; i ++)
  {
    for (int j = 0; j < 10; j++)
    {
      outputSave << playBoard[i][j];
    }
    outputSave << endl;
  }
  outputSave.close();
  cout << "Saved game!" << endl;
  cout << endl;
  playerTwo(playBoard, countA, countB);//after saving, goes to player 2's turn
}

//*****************************************************************************
void loadFilePlayerOne(int playBoard[10][10], int& countA, int& countB)//to load the save file of player 1
{
  ifstream inputLoad;
  inputLoad.open("saveFilePlayer1.txt");

  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; i < 10; i++)
    {
      inputLoad >> playBoard[i][j];
    }
  }
  playerOne(playBoard, countA, countB);
}

//*****************************************************************************
void loadFilePlayerTwo(int playBoard[10][10], int& countA, int& countB)//to load the save file of player 2
{
  ifstream inputLoad;
  inputLoad.open("saveFilePlayer2.txt");

  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; i < 10; i++)
    {
      inputLoad >> playBoard[i][j];
    }
  }
  playerTwo(playBoard, countA, countB);
}

//*****************************************************************************
void checkCrown(int currentBoard[10][10])//check for crown pieces
{
  for(int j = 0; j < 10; j++)
  {
    if(currentBoard[0][j] == 1)
      currentBoard[0][j] = 5;
    else if(currentBoard[9][j] == 2)
      currentBoard[9][j] = 6;
  }
}
