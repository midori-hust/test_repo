#include <iostream>
#include <string>
#include <cstdlib>


// in this example pieces aer described as integer values 
// we will make them constants, so that if at any time we want to change their values we can do so here
// but will still need to recompile

const int pawn = 100;
const int bishop = 305;
const int knight = 300;
const int rook = 500;
const int queen = 900;
const int king = 2000;

// an alternative would be to use string constants or another data type

//now we need a board to put the pieces on and move around on
//the board data type should match the pieces data type
// the board in regular chess is always 8x8, but for speedy legal move generator
//other programs use larger than 8x8 where an 8x8 real board exists in a larger array ie 12x14
// but for simplicity of understanding we will use the simple 8x8

int board[8][8];

// board [rank] [file];
// where rank = 0 - 7 (1 to 8 on a real chess board) and file = 0 - 7 (a - h)

const int startup[8][8] = { rook, knight, bishop, queen, king, bishop, knight, rook, pawn, pawn,pawn,pawn,pawn,pawn,pawn, pawn, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -pawn, -pawn, -pawn, -pawn, -pawn, -pawn, -pawn, -pawn, -rook, -knight, -bishop, -queen, -king, -bishop, -knight, -rook};

// the startup constant contains the standard starting position of all chess games (not variants)
//each side has 8 pieces and 8 pawns / all pawns are on the colours respective ranks
// for black pieces we use -piecetype. (negative)

void setup (void) {
int i, j;
  for (i = 0; i < 8; i++){
      for (j = 0; j < 8; j++){
      board[i][j] = startup[i][j]; //setup starting position
    }
    }

}

//the two for loops run through all the iteratins of the 8x8 array and copy the starting position to the real board.

// next we need a function that will display the board some way either graphics or text
// in this case we will print to the screen a text version of the boards contents

//it is standard in FEN notations and other text of a chess board to express each piece by it's first letter
// except the knight which uses 'N'

// the black pieces are lower case while the white pieces are upper case
// otherwise it is impossible to distinguish black pieces from white pieces

void printb (void){
using namespace std; // this must be here in order to begin using strings.
int a, b;
string piece;
for (a = 7; a > -1; a--){  // we must iterate the ranks down from 7 to 0 otherwise the board will be upside down
cout << endl;
 for (b = 0; b < 8; b++){
 switch (board[a][b]){
 case 0:
 piece = "-";
 break;
 case pawn:
 piece = "P";
 break;
 case knight:
 piece = "N";
 break;
 case bishop:
 piece = "B";
 break;
 case rook:
 piece = "R";
 break;
 case queen:
 piece = "Q";
 break;
 case king:
 piece = "K";
 break;
 case -pawn:
 piece = "p";
 break;
 case -knight:
 piece = "n";
 break;
 case -bishop:
 piece = "b";
 break;
 case -rook:
 piece = "r";
 break;
 case -queen:
 piece = "q";
 break;
 case -king:
 piece = "k";
 break;
 }
  cout << " " << piece << " ";
 }
}

 cout << endl << endl;
}


// every program in win32 console must have a main


int main (void) {

using namespace std;

//we need to tell the user about the program  ..  and how to use it

cout << "welcome to simplechess 1.0!" << endl << "created by Deepglue555" << endl << endl;
cout << "please enter your moves in 4 letter algebraic" << endl << "ie e2e4 in lower case only" << endl;
cout << "commands: exit = quit, abort = quit, print = displays the board," << endl << "new = new game" << endl << endl;

string passd; // this will be the string that contains info from the user
setup(); //we must set up the initial position

while (1){ // a while loop that always loops; except when a break; statement occurs

  getline (cin, passd );  //ask the user to input what he wants the app to do
     if (passd.substr(0, 4) == "exit" || passd.substr(0, 5) == "abort" || passd.substr(0, 4) == "quit")   { //test //for quit or exit statements
      break;
     }
     if (passd.substr(0, 5) == "print")   { // display the board
      printb();
     }
     if (passd.substr(0, 3) == "new")   { // ask for a new game
      setup();
     }
     if (passd.substr(0, 1) >= "a" && passd.substr(0, 1) <= "h" && passd.substr(1, 1) >= "1" && passd.substr(1, 1) <= "8" && passd.substr(2, 1) >= "a" && passd.substr(2, 1) <= "h" && passd.substr(3, 1) >= "1" && passd.substr(3, 1) <= "8")   { // this statement makes sure both squares are on the chess board when executing //a move
      // execute move
      // then display new board position

      int a, b, c, d;


      a = passd[0] - 'a';
      b = passd[1] - '1';
      c = passd[2] - 'a';
      d = passd[3] - '1';

//executes the move if its on the board!
      board[d][c] = board[b][a];
      board[b][a] = 0;

      printb(); //prints out to the screen the updated position after moving the pieces
     }
    }
}
 
