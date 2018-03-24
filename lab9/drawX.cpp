/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 9 - drawX

  This function draws an X where each stroke has length asterisks.
*/

#include <iostream>
#include "lab9.h"   //for drawPixel
using namespace std;

void drawX(int length) {
  for (int i = 0; i <= length / 2; i++)   //1st line (line 0) to middle line
  {
    for (int j = 1; j <= i; j++)   //# of starting spaces == line #
    {
    cout << " ";   //1st line, or line 0, has 0 starting spaces
    }
    drawPixel('*');   //1st * in these lines; middle line is complete now
    if (i < length / 2)   //when i == middle line, skip to else
    {
      for (int k = 1; k <= length - 2 * (i + 1); k++) //spaces b/w 1st and 2nd *
      {
      cout << " ";   //this applies to 1st line to line above middle line
      }
      drawPixel('*');
      cout << endl;   //go to next line
    }
    else   //for middle line
    {
    cout << endl;
    }
  }

  for (int i = length / 2; i >= 1; i--)   //row # decreases downwards
  {   //from middle + 1 line to last line; this will be opposite of above
    for (int j = 1; j <= i - 1; j++)   //# of spaces before 1st *
    {
    cout << " ";
    }
    drawPixel('*');   //1st * in these lines
    for (int k = 1; k <= length - 2 * i; k++)   //spaces b/w 1st and 2nd *'s
    {
    cout << " ";
    }
    drawPixel('*');
    cout << endl;   //2nd *, then go to next line and repeat
  }
}
