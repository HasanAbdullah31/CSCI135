/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Program 1 - Task 1

  This program analyzes election results to help come up with a winning strategy
for a presidential candidate. Specifically, it prompts the user to input the
numer of states in the region and each of the state codes (one at a time), and
then outputs the winner of the popular vote and the percentage points between
him and the loser in that region. This program assumes that the two major
candidates placed first and second in every state and that the user does not
input a combination of numbers and non-numbers.
*/

#include <iostream>
#include <fstream>
using namespace std;

int main () {

  ifstream elect12;
  elect12.open("elect12.csv");   //contains popular vote (pv) info.

  //variables for elect12 file
  int pvObama, pvRomney, pvOther, pvState;   //pv is popular vote per state
  string state;   //state abbreviation per state

  //prompt for number of states in region (must be >=1)
  int numStates;
  cout << "Input the number of states in the region:" << endl;
  cin >> numStates;
  while (numStates < 1 || cin.fail()) {
    cin.clear();
    cin.ignore(999, '\n');
    cout << "Invalid input! Number of states must be 1 or greater." << endl;
    cin >> numStates;
  }

  //variables for calculations/results
  int pvdiffObama = 0, pvdiffRomney = 0;   //sum of pv differences per state
  int totalpvState = 0;   //each state (that == codeState) adds to totalpvState

  //prompt for each of the state codes one at a time
  //the user will not necessarily enter them in sorted order
  //if illegal state is entered, cout error message and reprompt
  //program assumes that the user inputs distinct states (and uses caps lock)
  for (int i = 1; i <= numStates; i++)   //total # of stateCode == numStates
  {
    string stateCode;
    cout << "Enter state code:" << endl;
    cin >> stateCode;
    string temp = " ";   //temp used to check if stateCode is in file
    //each row in elect12 file is read in the following order
    while (elect12 >> pvObama >> pvRomney >> pvOther >> pvState >> state)
    {
      if (stateCode == state)
        temp = state;
    }   //if stateCode is in file, temp should = stateCode; else temp stays " "
    elect12.close();   //in case end of file is reached
    elect12.open("elect12.csv");   //re-open for next elect12 stream
    if (temp == " ")   //i.e. stateCode isn't in the file
    {
      i = 0;   //reset loop iteration, since stateCode is invalid input
      pvdiffObama = 0, pvdiffRomney = 0, totalpvState = 0;   //reset values
      cout << stateCode << " is not a legal state." << endl;
      cin.clear();
      cin.ignore(999, '\n');   //ignore the invalid input
      cout << "Re-enter all the state codes." << endl;
    }
    else if (temp == stateCode)   //i.e. stateCode is in the file
    {
      //read file for row where stateCode == state
      while (elect12 >> pvObama >> pvRomney >> pvOther >> pvState >> state)
      {
	if (stateCode == state)
	{
	pvdiffObama += (pvObama - pvRomney);
	pvdiffRomney += (pvRomney - pvObama);
	totalpvState += pvState;
	}
      }
    }
    elect12.close();
    elect12.open("elect12.csv");   //re-open for next iteration in for loop
  }   //end of for loop; if stateCode isn't in file, loop is reset (i = 1)
  //at end of last iteration of for loop, elect12 file is open
  elect12.close();
  //now we have: int pvdiffObama,pvdiffRomney,totalpvState;

  //pvpoints<candidate>=(pvdiff<person>/totalpvState)*100
  double pvpointsObama = ((double)pvdiffObama/(double)totalpvState)*100.00;
  double pvpointsRomney = ((double)pvdiffRomney/(double)totalpvState)*100.00;
  if (pvpointsObama > pvpointsRomney)   //if Obama has more pvpoints
  {
    cout << "Obama won the popular vote by " << pvpointsObama
	 << " points in the region." << endl;
  }
  else if (pvpointsObama < pvpointsRomney)   //if Romney has more pvpoints
  {
    cout << "Romney won the popular vote by " << pvpointsRomney
	 << " points in the region." << endl;
  }
  //Task 1 instructions does not mention the case when there is a tie

  return 0;

}

/*
  TESTING:
  This program assumes that the two major candidates placed first and second
  in every state and that the user does not input a combination of numbers and
  non-numbers. I also assumed that the input files have valid data.
  The program output correct results for when (read as a table):
  numStates:   stateCode(s):   winner:   points:
           1             CA      Obama   23.1186
           1             UT     Romney   48.0409
           2          NY,NJ      Obama     24.65
           2          WY,AL     Romney   24.1846
           5 DE,CO,FL,CT,DC      Obama   6.04904
           5 IN,IL,ID,HI,GA      Obama   2.25072
  -also worked for the example with small-elect12 file in discussion board
  -i.e. output correct result when numStates = 5; stateCodes= A,F,B,C,D;
  -when the user inputs a legal state, an illegal state, then a different legal
   state, the program outputs the correct result (e.g. when the user inputs
   numStates = 2, stateCodes = NY,hello,NJ, the output is Obama and 24.65).
*/
