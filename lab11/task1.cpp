/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 11 - Task 1

  This function returns a pointer to the 1st element of an array with the names
of countries with 2015 populations between m and n inclusive, and prints the
resulting list of countries. It also updates the size appropriately.
*/

#include "lab11.h"

//precond: Node* world; readFile(world); n >= m >= 0; int size;
//*world is not passed by reference, so retains its value after function call
string* printCountries(int m, int n, int &size, Node* world) {
  double M = (double)m/1000.00;   //file has populations in 1000s
  double N = (double)n/1000.00;   //e.g. 1,234,567 would be 1,234.567 in file
  size = 0;   //size of the array initialized to 0 (empty)
  Node* ogworld = world;   //stores original address of world
  while(ogworld != NULL) {   //traverse the list
    if (M <= ogworld->country.pop2015 && ogworld->country.pop2015 <= N) {
      size++;   //if pop2015 is b/w M and N (inclusive), increase size by 1
    }
    ogworld = ogworld->next;   //go to the next node through link
  }
  //assert: size == # of countries with pop2015 b/w m and n; ogworld == NULL
  static string* countries;   //function returns static pointer to the array
  try {
    countries = new string[size];   //allocate memory for array of size strings
  }   //new returns the address of the 1st element of the array
  catch (bad_alloc& ba) {   //if allocation fails
    cout << "Out of heap memory!" << endl;
    exit(1);
  }
  size = 0;   //reset for next while loop (same as above while loop)
  while(world != NULL) { //traverse the list a 2nd time, using world this time
    if (M <= world->country.pop2015 && world->country.pop2015 <= N) {
      countries[size] = world->country.name;
      size++;   //for next element in array
    }
    world = world->next;
  }
  //assert: size == # of countries with pop2015 b/w m and n; world == NULL
  if (size == 0) {
    cout << "There are no countries with 2015 populations between "
         << m << " and " << n << "." << endl;
  }
  else {
    cout << "The countries with 2015 populations between "
         << m << " and " << n << " are:" << endl;
    for (int i = 0; i < size; i++) {
      cout << countries[i] << endl;   //print the countries
    }
  }
  //assert: countries == the address of the 1st element of array we want
  return countries; //"return array" by returning static pointer to 1st element
/* The user can do the following to access the array somewhere else:
   Node* world; readFile(world); int size,m,n; //initialize m and n properly
   string* array = printCountries(m,n,size,world); //side effect: size adjusted
   for (int i = 0; i < size; i++) { cout << array[i] << endl; } */
}
