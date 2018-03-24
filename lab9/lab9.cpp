/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 9

  This program displays various shapes using asterisks, based on the length
parameter inputs from the user. This program assumes that the user does not
input a decimal value (e.g. 1.23), combination of numbers and non-numbers, or
a string (for the first input of each iteration).
*/

#include <iostream>
#include "lab9.h"   //header file for function prototypes
using namespace std;

int main () {
  for (int i = 0; i < 3; i++) {   //so user can select up to 3 shapes
  cout << "Input a character (r,x, or l):" << endl;
  //I assumed the user input a different character each time
  char c; cin >> c;
  while ((c != 'r' && c != 'x' && c != 'l') || cin.fail()) {
    cin.clear();
    cin.ignore(999,'\n');
    cout << "Invalid input! Character must be r,x, or l." << endl;
    cin >> c;
  }
  
  switch (c) {
    case 'r':   //Rect
    {
    //Draw a w-wide h-high rectangular frame, using asterisks.
    cout << "This program will display a rectangular frame." << endl;
    cout << "Input the width of the frame:" << endl;
    int w; cin >> w;
    while (w < 3 || cin.fail()) {   //width must be 3 or greater for a frame
      cin.clear();
      cin.ignore(999, '\n');
      cout << "Invalid input! Width must be greater than or equal to 3."<<endl;
      cin >> w;
    }
    cout << "Input the height of the frame:" << endl;
    int h; cin >> h;
    while (h < 3 || cin.fail()) {   //height must be 3 or greater for a frame
      cin.clear();
      cin.ignore(999, '\n');
      cout << "Invalid input! Height must be greater than or equal to 3."<<endl;
      cin >> h;
    }
    drawRect(w,h);
    } break;   //end of case 'r' (rectangle)
    
    case 'x':   //X
    {
    //Draw an X where each stroke has length asterisks.
    cout << "This program will display an X." << endl;
    cout << "Input the length of each stroke of the X:" << endl;
    int length; cin >> length; //X has a center, so length must be odd and >= 3
    while (length < 3 || length % 2 != 1 || cin.fail()) {
      cin.clear();
      cin.ignore(999, '\n');
      cout << "Invalid input! Length must be greater than or equal to 3,"<<endl
	   << "and must be an odd integer." << endl;
      cin >> length;
    }
    drawX(length);
    } break;   //end of case 'x' (X)
    
    case 'l':   //Ltri
    {
    //Draw the lower triangular part of a square, given the side length.
    cout << "This program will display the lower triangular part of a square."
         << endl;
    cout << "Input the side length of the square:" << endl;
    int side; cin >> side;
    while (side < 2 || cin.fail()) {   //side length 2 is minimum for triangle
      cin.clear();
      cin.ignore(999, '\n');
      cout << "Invalid input! Length must be greater than or equal to 2."<<endl;
      cin >> side;
    }
    drawLtri(side);
    } break;   //end of case 'l' (Ltri)
  }   //end of switch
  }   //end of for loop; stops after 3 iterations
  return 0;
}

/* TESTING:
   -If one of the argument object files is not included during compilation,
    the compilation fails due to 'undefined reference to <someFunction>'
   -if no files are changed, make lab9 does nothing; when at least one file is
    changed, make recompiles all the files (e.g. modifying drawPixel.cpp causes
    make to recompile drawPixel,drawRect,drawX,drawLtri, and lab9)
   -The following is a table of inputs and outputs (when running lab9.exe):
    char:  width:  height:  length:  side:  output:
        l                                2  left triangle with side length 2
        l                                3  left triangle with side length 3
        l                               12  left triangle with side length 12
        r      3        3                   3x3 rectangular frame
        r      3       12                   3x12 rectangular frame
        r     12        3                   12x3 rectangular frame
        x                        3          X with stroke length 3
        x                        7          X with stroke length 7
        x                       13          X with stroke length 13
   -Illegal cases were handled as well: when inputting a character other than
    r,x, or l, the program displayed an error message and reprompted */
