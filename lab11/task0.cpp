/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 11 - Task 0

  This function reads from population.csv and stores in a linked list of nodes.
*/

#include "lab11.h"

void readFile(Node* &world) {   //pass pointer by reference to change it
  ifstream ifstr;
  ifstr.open("population.csv");
  //variables for the data columns in population.csv
  double pop1950, pop1970, pop1990, pop2010, pop2015; string name;
  world = NULL;   //initialize as empty list
  //population.csv columns in the following order; getline for spaces in name
  while ((ifstr >> pop1950 >> pop1970 >> pop1990 >> pop2010 >> pop2015) &&
	 getline(ifstr,name)) { //while more data exists, read line from file
    Node* N = new Node;   //create a new Node N (note that N = new Node)
    if (N == NULL) {   //in case new was not successful
      cout << "Out of heap memory!" << endl;
      exit(1);
    }
    //store line data into N; -> is the same as (*N).<country or next>...
    N->country.pop1950 = pop1950;
    N->country.pop1970 = pop1970;
    N->country.pop1990 = pop1990;
    N->country.pop2010 = pop2010;
    N->country.pop2015 = pop2015;
    N->country.name = name;
    N->next = world;   //store the address of pointer world in pointer next
    world = N;   //transfer address of N to world
  }
  ifstr.close();
  return;
}
