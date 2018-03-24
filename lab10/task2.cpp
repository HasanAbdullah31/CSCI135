/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 10 - Task 2

  This function prints the list of countries that had negative growth rates
between 1950 and 2015.
*/

#include "lab10.h"

void printNegativeGR(World& myWorld) {
  cout << " The following countries shrunk between 1950 and 2015:" << endl;
  for (int i = 0; i < MAXCOUNTRIES; i++) {
    if (myWorld.countries[i].GR < 0) {
      cout << myWorld.countries[i].name << endl;
    }
  }
  return;
}
