/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Program 3

  This is an object oriented implementation of Program 1, which reads 2 files
  and outputs various statistics. This program assumes that the two major
  candidates placed first and second in every state and that the two input files
  are consistent.
*/

#include "ElectoralVotes.h"
#include "ElectionResults.h"

int main(int argc, char* argv[]) {
  
  //create objects er and ev that contain all data from respective file
  ElectionResults er(er,"elect12.csv");
  ElectoralVotes ev(ev,"ev10.csv");
  int totalevObama = er.totalev(Obama,ev);   //call totalev function
  int totalevRomney = er.totalev(Romney,ev);   //same as above, but for Romney
  if (totalevObama > totalevRomney) {   //if Obama won
    cout << "Obama won the national election with " << er.percpv(Obama)
	 << "% of the popular vote and a margin of " << er.pvmargin(Obama)
	 << " points." << endl;
    cout << "Obama received " << totalevObama << " electoral votes." << endl;
    cout << "Obama had an unweighted average victory margin of "
	 << er.avgmargin(Obama) << " points." << endl;
    cout << "Obama's best state was " << er.beststate(Obama)
         << ", where he won by " << er.bestpv(Obama) << " points." << endl;
    //<person>'s worst state is <person2>'s best state
    cout << "Obama's worst state was " << er.beststate(Romney)
	 << ", where he lost by " << er.bestpv(Romney) << " points." << endl;
  }
  else if (totalevObama < totalevRomney) {   //if Romney won
    cout << "Romney won the national election with " << er.percpv(Romney)
	 << "% of the popular vote and a margin of " << er.pvmargin(Romney)
	 << " points." << endl;
    cout << "Romney received " << totalevRomney << " electoral votes." << endl;
    cout << "Romney had an unweighted average victory margin of "
	 << er.avgmargin(Romney) << " points." << endl;
    cout << "Romney's best state was " << er.beststate(Romney)
	 << ", where he won by " << er.bestpv(Romney) << " points." << endl;
    cout << "Romney's worst state was " << er.beststate(Obama)
	 << ", where he lost by " << er.bestpv(Obama) << " points." << endl;
  }
  else if (totalevObama == totalevRomney) {   //in the case of a tie
    cout << "The election resulted in a tie!" << endl;
    cout<<"Both candidates received "<<totalevObama<<" electoral votes."<< endl;
    //display both candidate's unweighted avgmargin, best and worst states
    cout << "Obama had an unweighted average victory margin of "
	 << er.avgmargin(Obama) << " points." << endl;
    cout << "Romney had an unweighted average victory margin of "
	 << er.avgmargin(Romney) << " points." << endl;
    cout << "Obama's best state was " << er.beststate(Obama)
	 << ", where he won by " << er.bestpv(Obama) << " points." << endl;
    cout << "Romney's best state was " << er.beststate(Romney)
	 << ", where he won by " << er.bestpv(Romney) << " points." << endl;
    cout << "Obama's worst state was " << er.beststate(Romney)
	 << ", where he lost by " << er.bestpv(Romney) << " points." << endl;
    cout << "Romney's worst state was " << er.beststate(Obama)
	 << ", where he lost by " << er.bestpv(Obama) << " points." << endl;
  }
  
  return 0;
}

/*
  TESTING:
  This program assumes that the two major candidates placed first and second
  in every state and that the two input files are consistent (both contain the
  same states). I assumed that the input files have valid data as well.
  The program output correct results (same as in program 1) for when:
  - Obama won, in the two original input files
  - Romney won (use small-elect12 and small-ev10 files from discussion board)
  - there's a tie (totalevRomney=er.totalev(Obama,ev); keep totalevObama same)
*/
