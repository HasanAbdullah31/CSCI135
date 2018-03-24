/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 11 - Header File

  This file contains the libraries, definitions, and functions used in this lab.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>   //for exit (used in heap memory checking)
#include <new>   //for bad_alloc (used in task1.cpp)
using namespace std;

struct CountryData {
  double pop1950;
  double pop1970;
  double pop1990;
  double pop2010;
  double pop2015;
  string name;
};
struct Node {
  CountryData country;
  Node *      next;
};

extern void readFile(Node* &world); //task0.cpp
extern string* printCountries(int m, int n, int &size, Node* world); //task1.cpp
