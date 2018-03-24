/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Program 1 - Task 0

  This program analyzes election results to help come up with a winning strategy
for a presidential candidate. Specifically, it reads 2 files and outputs the
national results, including the average margin of victory for the winner, and
the states where he/she had the best and worst winning margins. This program
assumes that the two major candidates placed first and second in every state and
that the two input files are consistent (both contain the same states).
*/

#include <iostream>
#include <fstream>
using namespace std;

int main () {

  ifstream elect12, ev10;
  elect12.open("elect12.csv");   //contains popular vote (pv) info.
  ev10.open("ev10.csv");   //contains electoral vote (ev) info.

  //variables for elect12 file
  int pvObama, pvRomney, pvOther, pvState;   //pv is popular vote per state
  string state12;   //state abbreviation per state for elect12 file

  //variables for ev10 file
  int evState;   //ev is electoral vote per state
  string state10;   //state abbreviation per state for ev10 file

  //variables for calculations/results
  int totalpvObama = 0, totalpvRomney = 0;   //each state adds to totalpv
  int totalpvState = 0;   //each state adds to totalpvState
  double avgmarginObama = 0, avgmarginRomney = 0;//unweighted avg. marginvictory
  int numStates = 0;   //counter for total # of states (i.e. total # of rows)
  int evObama = 0, evRomney = 0;   //each state adds to total ev
  string bestObama, bestRomney;   //best states for each
  double pvbestObama = -100, pvbestRomney = -100; //point difference per state

  //each row in elect12 file is read in the following order
  while (elect12 >> pvObama >> pvRomney >> pvOther >> pvState >> state12) {
    //totalpv<person or state> == sum of pv<person or state> from all states
    totalpvObama += pvObama;
    totalpvRomney += pvRomney;
    totalpvState += pvState;
    //pv<person> - pv<person2> == marginvictory<person> in <state>
    //avgmargin<person> += (marginvictory<person>/pv<state>)
    //after outer while loop ends, avgmargin<person>/numStates for total avg.
    avgmarginObama += (((double)(pvObama-pvRomney))/(double)pvState);
    avgmarginRomney += (((double)(pvRomney-pvObama))/(double)pvState);
    numStates++;   //each row adds 1 to numStates
    //percentpv<person> in <state> == (pv<person>/pv<state>)*100
    double percentpvObama = ((double)pvObama/(double)pvState)*100.00;
    double percentpvRomney = ((double)pvRomney/(double)pvState)*100.00;
    //pvbest<person> is <state> where <person> has highest point difference
    double pointsObama = percentpvObama - percentpvRomney;
    double pointsRomney = percentpvRomney - percentpvObama;
    if (pvbestObama < pointsObama) {   //if higher point difference is found
      pvbestObama = pointsObama;   //pvbest holds highest point difference
      bestObama = state12;   //state12 is the state abbreviation at end of row
    }
    if (pvbestRomney < pointsRomney) {   //same as above
      pvbestRomney = pointsRomney;
      bestRomney = state12;
    }
    //scan through ev10 file for each row of elect12 file
    //each row in ev10 file is read in the following order
    while (ev10 >> evState >> state10) {
      //the candidate with higher % of pv in a state gets all of that state's ev
      if ((percentpvObama > percentpvRomney) && (state12 == state10))
	evObama += evState;
      else if ((percentpvObama < percentpvRomney) && (state12 == state10))
	evRomney += evState;
    }   //end of inner while loop
    //elect12's rows sorted by state abbreviation, ev10's rows sorted by ev
    //i.e. rows don't correspond to same states, so close and re-open ev10
    ev10.close();
    ev10.open("ev10.csv");
  }   //end of elect12 file, and ev10 is newly open (at start of first line)
  elect12.close();
  ev10.close();
  //now we have: int totalpvObama,totalpvRomney,totalpvState,numStates,
  //(still int) evObama,evRomney; double avgmarginObama,avgmarginRomney,
  //(still double) pvbestObama,pvbestRomney; string bestObama,bestRomney;
  //all of these except avgmarginObama and avgmarginRomney are complete

  //%pv<person> == (totalpv<person>/totalpvState)*100
  double percpvObama = ((double)totalpvObama/(double)totalpvState)*100.00;
  double percpvRomney = ((double)totalpvRomney/(double)totalpvState)*100.00;
  //pvmargin<person> == ((totalpv<person>-totalpv<person2>)/totalpvState)*100
  double pvdiffObama = (double)(totalpvObama - totalpvRomney);   //difference
  double pvdiffRomney = (double)(totalpvRomney - totalpvObama);   //difference
  double pvmarginObama = (pvdiffObama / totalpvState) * 100.00;
  double pvmarginRomney = (pvdiffRomney / totalpvState) * 100.00;
  //avgmargin<person>*100/numStates for total avg. as a %
  avgmarginObama *= 100.00/(double)numStates;
  avgmarginRomney *= 100.00/(double)numStates;

  //first line to cout includes: winner, % pv of winner, and pvmargin of winner,
  //second line is winner's ev, third line is winner's unweighted avgmargin,
  //fourth and fifth lines are best and worst states (and pv points in each)
  if (evObama > evRomney) {   //if Obama won
    cout << "Obama won the national election with " << percpvObama
	 << "% of the popular vote and a margin of " << pvmarginObama
	 << " points." << endl;
    cout << "Obama received " << evObama << " electoral votes." << endl;
    cout << "Obama had an unweighted average victory margin of "
	 << avgmarginObama << " points." << endl;
    cout << "Obama's best state was " << bestObama << ", where he won by "
	 << pvbestObama << " points." << endl;
    //<person>'s worst state is <person2>'s best state
    cout << "Obama's worst state was " << bestRomney << ", where he lost by "
	 << pvbestRomney << " points." << endl;
  }
  else if (evObama < evRomney) {   //if Romney won
    cout << "Romney won the national election with " << percpvRomney
	 << "% of the popular vote and a margin of " << pvmarginRomney
	 << " points." << endl;
    cout << "Romney received " << evRomney << " electoral votes." << endl;
    cout << "Romney had an unweighted average victory margin of "
	 << avgmarginRomney << " points." << endl;
    cout << "Romney's best state was " << bestRomney << ", where he won by "
	 << pvbestRomney << " points." << endl;
    cout << "Romney's worst state was " << bestObama << ", where he lost by "
	 << pvbestObama << " points." << endl;
  }
  else if (evObama == evRomney) {   //in the case of a tie
    cout << "The election resulted in a tie!" << endl;
    cout << "Both candidates received "<<evObama<<" electoral votes." << endl;
    //display both candidate's unweighted avgmargin, best and worst states
    cout << "Obama had an unweighted average victory margin of "
	 << avgmarginObama << " points." << endl;
    cout << "Romney had an unweighted average victory margin of "
	 << avgmarginRomney << " points." << endl;
    cout << "Obama's best state was " << bestObama << ", where he won by "
	 << pvbestObama << " points." << endl;
    cout << "Romney's best state was " << bestRomney << ", where he won by "
	 << pvbestRomney << " points." << endl;
    cout << "Obama's worst state was " << bestRomney << ", where he lost by "
	 << pvbestRomney << " points." << endl;
    cout << "Romney's worst state was " << bestObama << ", where he lost by "
	 << pvbestObama << " points." << endl;
  }

  return 0;

}

/*
  TESTING:
  This program assumes that the two major candidates placed first and second
  in every state and that the two input files are consistent (both contain the
  same states). I assumed that the input files have valid data as well.
  The program output correct results for when:
  - Obama won, in the two original input files
  - Romney won, in the small-elect12 and small-ev10 files from discussion board
  - there is a tie, in my modified file attached in submission
*/
