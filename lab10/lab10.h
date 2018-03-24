/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 10 - Header File

  This file contains the libraries, definitions, and functions used in this lab.
*/

#include <iostream>
#include <fstream>
using namespace std;

const int MAXCOUNTRIES = 229;   //number of countries in population.csv

//format of population.csv: Columns 1-5: populations (in 1000s) of country in
//1950,1970,1990,2010,2015 (respectively); Column 6: name of country
struct Country {
  double pop1950;
  double pop1970;
  double pop1990;
  double pop2010;
  double pop2015;
  string name;
  double GR;   //growth rate b/w 1950 and 2015 (see tasks 1 and 2)
};
struct World {
  //1st,2nd,3rd: indices of countries with 3 largest growth rates (task1)
  int     first, second, third;
  Country countries[MAXCOUNTRIES];
};

extern void readFile(World& myWorld);   //in task0.cpp
extern void printTop3GR(World& myWorld);   //in task1.cpp
extern void printNegativeGR(World& myWorld);   //in task2.cpp
