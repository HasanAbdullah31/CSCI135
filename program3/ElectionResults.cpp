/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Program 3 - ADT#2 Definitions

  These are function definitions for the class ElectionResults.
*/

#include "ElectionResults.h"

//friend keyword only used in prototype; no :: b/c this is NOT a member function
istream &operator >>(istream &input, ElectionResults &er) {
  if (input.peek() == EOF) return input;   //skip last empty line
  int pvOb, pvRo, pvOt, pvSt; string st;
  input >> pvOb; er.set_pvObama(pvOb);
  input >> pvRo; er.set_pvRomney(pvRo);
  input >> pvOt; er.set_pvOther(pvOt);
  input >> pvSt; er.set_pvState(pvSt);
  input >> st;   er.set_state(st);
  input.ignore(999,'\n');   //ignore newline character
  if (input.fail()) { cout << "Invalid data format!" << endl; exit(1); }
  return input;   //for multiple >> operators
}

ostream &operator <<(ostream &output, ElectionResults &er) {
  //assume that all data members have the same size
  for (uI i = 0; i < er.pvObama_size(); i++) {
    output << er.get_pvObama(i) << '\t';
    output << er.get_pvRomney(i) << '\t';
    output << er.get_pvOther(i) << '\t';
    output << er.get_pvState(i) << '\t';
    output << er.get_state(i) << endl;
  }
  return output;
}

ElectionResults::ElectionResults(ElectionResults &er, string file) {
  //e.g. would declare as: ElectionResults objectName(objectName,"elect12.csv");
  ifstream ifstr;
  ifstr.open(file.c_str());   //name of input file specified in argument file
  if (ifstr.fail()) {
    cout << "File not found!" << endl;
    exit(1);
  }
  while (!ifstr.eof()) {
    ifstr >> er;   //let friend function >> do the work
  }
  ifstr.close();
}

int ElectionResults::totalpvState() {
  int totalpvState = 0;
  for (uI i = 0; i < pvState.size(); i++) totalpvState += pvState[i];
  return totalpvState;
}

int ElectionResults::totalpv(enum Candidate cand) {
  //totalpv<person or state> == sum of pv<person or state> from all states
  int totalpv = 0;
  if (cand == Obama)
    for (uI i = 0; i < pvObama.size(); i++) totalpv += pvObama[i];
  else if (cand == Romney)
    for (uI i = 0; i < pvRomney.size(); i++) totalpv += pvRomney[i];
  return totalpv;
}

int ElectionResults::totalev(enum Candidate cand, ElectoralVotes ev) {
  //the candidate with higher % of pv in a state gets all of that state's ev
  //assumes state.size() == pvObama.size() == pvRomney.size()
  int totalev = 0;
  if (cand == Obama) {
    for (uI i = 0; i < pvObama.size(); i++) {
      if (percpv(Obama,i) > percpv(Romney,i)) {   //relies on percpv function
        for (uI j = 0; j < ev.state_size(); j++) { //get funct. from other class
	  //since both files are sorted differently, find the state that's ==
	  if (state[i] == ev.get_state(j)) totalev += ev.get_evState(j);
        }
      }
    }
  }
  else if (cand == Romney) {
    for (uI i = 0; i < pvRomney.size(); i++) {
      if (percpv(Romney,i) > percpv(Obama,i)) {
        for (uI j = 0; j < ev.state_size(); j++) {
	  if (state[i] == ev.get_state(j)) totalev += ev.get_evState(j);
        }
      }
    }
  }
  return totalev;
}

double ElectionResults::percpv(enum Candidate cand) {
  if (cand == Obama)       return ((double)totalpv(Obama)/totalpvState())*100;
  else if (cand == Romney) return ((double)totalpv(Romney)/totalpvState())*100;
}

double ElectionResults::percpv(enum Candidate cand, int i) { //assumes sizes ==
  if (cand==Obama)       return ((double)pvObama[i]/(double)pvState[i])*100.00;
  else if (cand==Romney) return ((double)pvRomney[i]/(double)pvState[i])*100.00;
}

double ElectionResults::pvmargin(enum Candidate cand) {
  //pvmargin<person> == ((totalpv<person>-totalpv<person2>)/totalpvState)*100
  if (cand == Obama)
    return ((double)totalpv(Obama)-(double)totalpv(Romney))*100/totalpvState();
  else if (cand == Romney)
    return ((double)totalpv(Romney)-(double)totalpv(Obama))*100/totalpvState();
}

double ElectionResults::avgmargin(enum Candidate cand) {
  //pv<person> - pv<person2> == marginvictory<person> in <state>
  //avgmargin<person> += (marginvictory<person>/pv<state>)
  double avgmargin = 0;   //unweighted avg. margin of victory
  if (cand == Obama) {
    for (uI i = 0; i < state.size(); i++)   //assumes sizes are ==
      avgmargin += ( ((double)(pvObama[i]-pvRomney[i]))/(double)pvState[i] );
  }
  else if (cand == Romney) {
    for (uI i = 0; i < state.size(); i++)
      avgmargin += ( ((double)(pvRomney[i]-pvObama[i]))/(double)pvState[i] );
  }
  //divide by number of states, then *100 for total avg. as a %
  avgmargin *= 100.00/(double)state.size();
  return avgmargin;
}

double ElectionResults::bestpv(enum Candidate cand) {
  double bestpv = -100, points;   //point difference per state
  //pvbest<person> is <state> where <person> has highest point difference
  if (cand == Obama) {
    for (uI i = 0; i < state.size(); i++) {
      points = percpv(Obama,i) - percpv(Romney,i);
      //if higher point difference found; bestpv holds highest point difference
      //side effect: private member beststate<cand> set appropriately
      if (bestpv < points) { bestpv = points; beststateObama = state[i]; }
    }
  }
  else if (cand == Romney) {
    for (uI i = 0; i < state.size(); i++) {
      points = percpv(Romney,i) - percpv(Obama,i);
      if (bestpv < points) { bestpv = points; beststateRomney = state[i]; }
    }
  }
  return bestpv;
}

string ElectionResults::beststate(enum Candidate cand) {
  //side eff. of bestpv(cand): private member beststate<cand> set appropriately
  //if bestpv(cand) not called, beststate<cand> is empty (default init.)
  if (cand == Obama) {
    if (beststateObama == "") bestpv(Obama);
    return beststateObama;
  }
  else if (cand == Romney) {
    if (beststateRomney == "") bestpv(Romney);
    return beststateRomney;
  }
}
