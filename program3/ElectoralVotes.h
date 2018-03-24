/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Program 3 - Header File for ADT#1

  This is the .h file for the ADT of electoral vote input file "ev10.csv".
*/

#ifndef ELECTORALVOTES_H
#define ELECTORALVOTES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <stdlib.h>   //for exit function
using namespace std;

typedef unsigned int uI;

class ElectoralVotes {   /* ev stands for electoral vote(s) */
public:
  //inline default constructor:
  ElectoralVotes(){evState.push_back(0);state.push_back("");}
  //constructor that takes the object name and filename to initialize members:
  ElectoralVotes(ElectoralVotes &ev, string file);
  //overloaded file input function; friend b/c it has to access private members:
  friend istream &operator >>(istream &input, ElectoralVotes &ev);
  //since there is a >> function, we should have a << function as well:
  friend ostream &operator <<(ostream &output, ElectoralVotes &ev);
  //inline accessor functions for private data members:
  int get_evState(uI i){assert(i>=0&&i<evState.size());return evState[i];}
  string get_state(uI i){assert(i>=0&&i<state.size());return state[i];}
  uI evState_size(){return evState.size();}
  uI state_size(){return state.size();}
  //inline mutator functions for private data members:
  void set_evState(int insertMe){evState.push_back(insertMe);}
  void set_state(string insertMe){state.push_back(insertMe);}
  void change_evState(uI i,int j){assert(i>=0&&i<evState.size());evState[i]=j;}
  void change_state(uI i,string j){assert(i>=0&&i<state.size());state[i]=j;}
private:   //information in each column of the file
  vector<int>    evState;
  vector<string> state;
};

#endif /* ELECTORALVOTES_H */
