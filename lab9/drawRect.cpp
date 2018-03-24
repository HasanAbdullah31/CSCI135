/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 9 - drawRect

  This function draws a w-wide h-high rectangular frame, using asterisks.
*/

#include <iostream>
#include "lab9.h"   //for drawPixel
using namespace std;

void drawRect(int w, int h) {
  for (int i = 1; i <= w; i++)   //1st line of frame has w amount of *'s
  {
  drawPixel('*');
  }
  cout << endl;   //go to 2nd line

  for (int i = 1; i <= h - 2; i++)   //2nd line to 2nd-to-last line
  {
    drawPixel('*');   //1st * in these lines (makes the left frame)
    for (int j = 1; j <= w - 2; j++)
    {
    cout << " ";   //spaces after 1st * and before 2nd *
    }
    drawPixel('*');   //2nd * in these lines (makes the right frame)
    cout << endl;   //go to next line
  }

  for (int i = 1; i <= w; i++)   //last line of frame has w amount of *'s
  {
  drawPixel('*');
  }
  cout << endl;   //new line for next output
  return;
}
