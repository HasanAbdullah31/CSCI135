/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 3

  This program displays various shapes using asterisks, based on the length 
parameter inputs from the user. This program assumes that the user does not 
input a decimal value (e.g. 1.23) or a combination of numbers and non-numbers.
*/

#include <iostream>
#include <cmath>   //for using square root in task 5
using namespace std;

int main () {

//1: Draw a w-wide h-high rectangular frame, using asterisks.
cout << "This program will display a rectangular frame." << endl;
 
 int w, h;   //width w and height h
 cout << "Input the width of the frame:" << endl;
 cin >> w;
 while (w < 3 || cin.fail()) {   //width must be 3 or greater for a frame
   cin.clear();
   cin.ignore(999, '\n');
   cout << "Invalid input! Width must be greater than or equal to 3." << endl;
   cin >> w;
 }
 cout << "Input the height of the frame:" << endl;
 cin >> h;
 while (h < 3 || cin.fail()) {   //height must be 3 or greater for a frame
   cin.clear();
   cin.ignore(999, '\n');
   cout << "Invalid input! Height must be greater than or equal to 3." << endl;
   cin >> h;
 }

 for (int i = 1; i <= w; i++)   //1st line of frame has w amount of *'s
 {
   cout << "*";
 }
 cout << endl;   //go to 2nd line
 
 for (int i = 1; i <= h - 2; i++)   //2nd line to 2nd-to-last line
 {
   cout << "*";   //1st * in these lines (makes the left frame)
   for (int j = 1; j <= w - 2; j++)
   {
     cout << " ";   //spaces after 1st * and before 2nd *
   }
   cout << "*" << endl;   //2nd * in these lines (makes the right frame)
 }
 
 for (int i = 1; i <= w; i++)   //last line of frame has w amount of *'s
 {
   cout << "*";
 }
 cout << endl;   //go to next task

//2: Draw an X where each stroke has length asterisks.
cout << "This program will display an X." << endl;

 int length;
 cout << "Input the length of each stroke of the X:" << endl;
 cin >> length;   //X has a center, so length must be odd and >= 3
 while (length < 3 || length % 2 != 1 || cin.fail()) {
   cin.clear();
   cin.ignore(999, '\n');
   cout << "Invalid input! Length must be greater than or equal to 3," << endl
	<< "and must be an odd integer." << endl;
   cin >> length;
 }
 
 for (int i = 0; i <= length / 2; i++)   //1st line (line 0) to middle line
 {
   for (int j = 1; j <= i; j++)   //# of starting spaces == line #
   {
     cout << " ";   //1st line, or line 0, has 0 starting spaces
   }
   cout << "*";   //1st * in these lines; middle line is complete now
   if (i < length / 2)   //when i == middle line, skip to else
   {
     for (int k = 1; k <= length - 2 * (i + 1); k++) //spaces b/w 1st and 2nd *
     {
       cout << " ";   //this applies to 1st line to line above middle line
     }
     cout << "*" << endl;
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
   cout << "*";   //1st * in these lines
     for (int k = 1; k <= length - 2 * i; k++)   //spaces b/w 1st and 2nd *'s
     {
       cout << " ";
     }
     cout << "*" << endl;   //2nd *, then go to next line and repeat
 }

//3: Draw the lower triangular part of a square, given the side length.
cout << "This program will display the lower triangular part of a square."
     << endl;

 int side;
 cout << "Input the side length of the square:" << endl;
 cin >> side;
 while (side < 2 || cin.fail()) {   //side length 2 is minimum for triangle
   cin.clear();
   cin.ignore(999, '\n');
   cout << "Invalid input! Length must be greater than or equal to 2." << endl;
   cin >> side;
 }

 for (int i = 1; i <= side; i++)   //line 1 to line side
 {
   for (int j = 1; j <= i; j++)   //# of *'s == line #
   {
     cout << "*";
   }
   cout << endl;   //go to next line and repeat
 }

//4: Draw the upper triangular part of a square, given the side length.
cout << "This program will display the upper triangular part of a square."
     << endl;
 
 int side2;   //side2 to differ from task 3 variable
 cout << "Input the side length of the square:" << endl;
 cin >> side2;
 while (side2 < 2 || cin.fail()) {   //same as before
   cin.clear();
   cin.ignore(999, '\n');
   cout << "Invalid input! Length must be greater than or equal to 2." << endl;
   cin >> side2;
 }

 for (int i = 1; i <= side2; i++)   //same as above
 {
   for (int j = 1; j <= i - 1; j++)   //# of spaces == line # - 1
   {
     cout << " ";
   }
     for (int k = 1; k <= side2 - (i - 1); k++)   //fill in rest of line with *
     {
       cout << "*";
     }
     cout << endl;   //repeat for each line
 }

//5: Given a radius, draw a circle with that radius.
cout << "This program will display a circle." << endl;

 int radius;
 cout << "Input the radius of the circle:" << endl;
 cin >> radius;
 while (radius < 1 || cin.fail()) {   //radius must be 1 or greater
   cin.clear();
   cin.ignore(999, '\n');
   cout << "Invalid input! Radius must be greater than or equal to 1." << endl;
   cin >> radius;
 }

 for (int y = radius; y >= -1 * radius; y--)   //top y to bottom y in graph
 {
   for (int x = -1 * radius; x <= radius; x++)   //left x to right x in graph
   {
     int distance = sqrt (x * x + y * y);   //distance to center (0,0)
     if (distance < radius)
     {   //circle has *'s when x^2 + y^2 < r^2
       cout << "*";   //for small values of r, the circle looks like a square
     }   //for large values of r, it looks like an ellipse
       else
       {
       cout << " ";
       }
   }
   cout << endl;   //repeat for next line
 }

 return 0;

}
