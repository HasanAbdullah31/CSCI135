/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 10 - Task 0

  This function initializes World myWorld with the data from population.csv.
*/

#include "lab10.h"   //for fstream library and structs

void readFile(World& myWorld) {   //pass by reference to change myWorld
  ifstream ifstr;
  ifstr.open("population.csv");
  //variables for the data columns in population.csv
  double pop1950, pop1970, pop1990, pop2010, pop2015; string name;
  int i = 0;   //countries[i]; from countries[0] to countries[MAXCOUNTRIES-1]
  //population.csv columns in the following order; getline for spaces in name
  while ((ifstr >> pop1950 >> pop1970 >> pop1990 >> pop2010 >> pop2015) &&
	 getline(ifstr,name)) {
    myWorld.countries[i].pop1950 = pop1950;
    myWorld.countries[i].pop1970 = pop1970;
    myWorld.countries[i].pop1990 = pop1990;
    myWorld.countries[i].pop2010 = pop2010;
    myWorld.countries[i].pop2015 = pop2015;
    myWorld.countries[i].name = name;
    i++;   //next iteration is next line (if not eof)
  }
  ifstr.close();
  return;
}
