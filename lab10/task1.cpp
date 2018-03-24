/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 10 - Task 1

  This function prints the countries with the 3 largest growth rates between
1950 and 2015. It also stores the indices of these 3 countries in first,second,
and third of World myWorld. The function assumes that there are at least 3
countries and that growth rate refers to (pop2015-pop1950)/pop1950.
*/

#include "lab10.h"

void printTop3GR(World& myWorld) {
  double first = -100, second = -101, third = -102; //temps to compare with
  for (int i = 0; i < MAXCOUNTRIES; i++) {
    //growth rate b/w 1950 and 2015 is given by the following equation
    double GR = (myWorld.countries[i].pop2015-myWorld.countries[i].pop1950)
                /myWorld.countries[i].pop1950;
    myWorld.countries[i].GR = GR;   //store GR in respective country (task2)
    if (GR >= first) {
      first = GR; myWorld.first = i;
    }
  }
  //assert: first is highest GR; myWorld.first is index of that country
  //also, myWorld.countries[].GR contains the GRs for each country
  for (int j = 0; j < MAXCOUNTRIES; j++) {
    double GR = myWorld.countries[j].GR;
    if (GR >= second && GR < first) {
      second = GR; myWorld.second = j;
    }
  }
  //assert: second is 2nd highest GR; myWorld.second is index of that country
  for (int k = 0; k < MAXCOUNTRIES; k++) {
    double GR = myWorld.countries[k].GR;
    if (GR >= third && GR < second) {
      third = GR; myWorld.third = k;
    }
  }
  //assert: third is 3rd highest GR; myWorld.third is index of that country
  int f = myWorld.first, s = myWorld.second, t = myWorld.third;
  cout << " The fastest growing country is"<<myWorld.countries[f].name
       << ", which grew by "<<first*100.00<<"%\n between 1950 and 2015."<<endl;
  cout << " The 2nd fastest growing country is"<<myWorld.countries[s].name
       << ", which grew by "<<second*100.00<<"%\n between 1950 and 2015."<<endl;
  cout << " The 3rd fastest growing country is"<<myWorld.countries[t].name
       << ", which grew by "<<third*100.00<<"%\n between 1950 and 2015."<<endl;
  return;
}
