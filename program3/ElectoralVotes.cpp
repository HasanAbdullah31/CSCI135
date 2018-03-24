/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Program 3 - ADT#1 Definitions

  These are function definitions for the class ElectoralVotes.
*/

#include "ElectoralVotes.h"

//friend keyword only used in prototype; no :: b/c this is NOT a member function
istream &operator >>(istream &input, ElectoralVotes &ev) {
  if (input.peek() == EOF) return input;   //skip last empty line
  int evSt; string st;
  input >> evSt; ev.set_evState(evSt);
  input >> st; ev.set_state(st);
  input.ignore(999,'\n');   //ignore newline character
  if (input.fail()) { cout << "Invalid data format!" << endl; exit(1); }
  return input;   //for multiple >> operators
}

ostream &operator <<(ostream &output, ElectoralVotes &ev) {
  //assume that all data members have the same size
  for (uI i = 0; i < ev.evState_size(); i++) {
    output << ev.get_evState(i) << '\t';
    output << ev.get_state(i) << endl;
  }
  return output;
}

ElectoralVotes::ElectoralVotes(ElectoralVotes &ev, string file) {
  //e.g. would declare as: ElectoralVotes objectName(objectName,"ev10.csv");
  ifstream ifstr;
  ifstr.open(file.c_str());   //name of input file specified in argument file
  if (ifstr.fail()) {
    cout << "File not found!" << endl;
    exit(1);
  }
  while (!ifstr.eof()) {
    ifstr >> ev;   //let friend function >> do the work
  }
  ifstr.close();
}
