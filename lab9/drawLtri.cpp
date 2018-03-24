/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 9 - drawLtri

  This function draws the lower triangular part of a square, given side length.
*/

#include <iostream>
#include "lab9.h"   //for drawPixel
using namespace std;

void drawLtri(int side) {
 for (int i = 1; i <= side; i++)   //line 1 to line side
 {
   for (int j = 1; j <= i; j++)   //# of *'s == line #
   {
   drawPixel('*');
   }
   cout << endl;   //go to next line and repeat
 }
}
