/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Program 3 - Header File for ADT#2

  This is the .h file for the ADT of election results input file "elect12.csv".
*/

#ifndef ELECTIONRESULTS_H
#define ELECTIONRESULTS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <stdlib.h>   //for exit function
#include "ElectoralVotes.h"   //needed for totalev function
using namespace std;

typedef unsigned int uI;
enum Candidate { Obama, Romney };   //needed for statistic functions

class ElectionResults {   /* pv stands for popular vote(s) */
public:
  //inline default constructor:
  ElectionResults(){pvObama.push_back(0);pvRomney.push_back(0);
    pvOther.push_back(0);pvState.push_back(0);state.push_back("");}
  //constructor that takes the object name and filename to initialize members:
  ElectionResults(ElectionResults &er, string file);
  //overloaded file input function; friend b/c it has to access private members:
  friend istream &operator >>(istream &input, ElectionResults &er);
  //since there is a >> function, we should have a << function as well:
  friend ostream &operator <<(ostream &output, ElectionResults &er);
  //inline accessor functions for private data members:
  int get_pvObama(uI i){assert(i>=0&&i<pvObama.size());return pvObama[i];}
  int get_pvRomney(uI i){assert(i>=0&&i<pvRomney.size());return pvRomney[i];}
  int get_pvOther(uI i){assert(i>=0&&i<pvOther.size());return pvOther[i];}
  int get_pvState(uI i){assert(i>=0&&i<pvState.size());return pvState[i];}
  string get_state(uI i){assert(i>=0&&i<state.size());return state[i];}
  uI pvObama_size(){return pvObama.size();}
  uI pvRomney_size(){return pvRomney.size();}
  uI pvOther_size(){return pvOther.size();}
  uI pvState_size(){return pvState.size();}
  uI state_size(){return state.size();}
  //inline mutator functions for private data members:
  void set_pvObama(int insertMe){pvObama.push_back(insertMe);}
  void set_pvRomney(int insertMe){pvRomney.push_back(insertMe);}
  void set_pvOther(int insertMe){pvOther.push_back(insertMe);}
  void set_pvState(int insertMe){pvState.push_back(insertMe);}
  void set_state(string insertMe){state.push_back(insertMe);}
  void change_pvObama(uI i,int j){assert(i>=0&&i<pvObama.size());pvObama[i]=j;}
  void change_pvRomney(uI i,int j){assert(i>=0&&i<pvRomney.size());pvRomney[i]=j;}
  void change_pvOther(uI i,int j){assert(i>=0&&i<pvOther.size());pvOther[i]=j;}
  void change_pvState(uI i,int j){assert(i>=0&&i<pvState.size());pvState[i]=j;}
  void change_state(uI i,string j){assert(i>=0&&i<state.size());state[i]=j;}
  //functions that calculate various statistics:
  int totalpvState();
  int totalpv(enum Candidate cand);
  int totalev(enum Candidate cand, ElectoralVotes ev);
  double percpv(enum Candidate cand);   //total % pv
  double percpv(enum Candidate cand, int i);   //% pv in state[i]
  double pvmargin(enum Candidate cand);
  double avgmargin(enum Candidate cand);
  double bestpv(enum Candidate cand); //doubles (pun intended) as mutator funct.
  //side effect of bestpv: private member beststate<Candidate> set appropriately
  string beststate(enum Candidate cand);   //basically an accessor funct.
private:   //information in each column of the file
  vector<int>    pvObama;
  vector<int>    pvRomney;
  vector<int>    pvOther;
  vector<int>    pvState;
  vector<string> state;
  string beststateObama;   /* bestpv function stores values here;  */
  string beststateRomney;  /* beststate function returns the value */
};

#endif /* ELECTIONRESULTS_H */
