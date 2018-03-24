/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 10

  This program calls the functions defined in tasks 0,1, and 2.
*/

#include "lab10.h"

int main() {
  World myWorld;
  readFile(myWorld);   //task0
  printTop3GR(myWorld);   //task1
  printNegativeGR(myWorld);   //task2
  return 0;
}
