/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 2

  This program uses the Verhulst Formula to output a table of years and 
  populations based on input parameters. Specifically, the user inputs:
  - p_0: initial population (at initial year 0);
  - k: number of years to display in output (1 to k years);
  - M: carrying capacity;
  - g: rate of population growth;
  - h: minimum loss rate.
  The output is a table of years (1 to k on table's left side) and populations 
  (corresponding to the respective years, on table's right side) calculated by 
  the Verhulst Formula: formula = ((1 + g - h) * p_0) - (g * p_0 * p_0 / M).
*/

#include <iostream>
#include <iomanip>   //to format the output (table with adjusted whitespace)
using namespace std;

int main () {
  int p_0, k, M;   //populations and years are integers
  float g, h;   //rates can have decimals, so float is good for g and h

  /*
    Error checking during the inputs:
    For the g and h inputs, I assumed the user would follow directions and 
    input the rate as a percentage. I also assumed the user would not input 
    a combination of numbers and non-numbers (e.g. 123abc), or decimal values 
    for p_0, k, and M (e.g. 1.111).
  */
  
  cout << "Enter the initial population:" << endl;
  cin >> p_0;   //p_0 cannot be negative or a non-number
  while (p_0 < 0 || cin.fail()) {
    cout << "Invalid input! Initial population must be 0 or greater." << endl;
    cin.clear();   //clear error flags
    cin.ignore(999, '\n');   //discard previous input
    cin >> p_0;
  }
  
  cout << "Enter the number of years you want displayed in the output:" << endl;
  cin >> k;   //k cannot be negative, 0, or a non-number
  while (k <= 0 || cin.fail()) {
    cout << "Invalid input! Number of years must be greater than 0." << endl;
    cin.clear();
    cin.ignore(999, '\n');
    cin >> k;
  }
  
  cout << "Enter the carrying capacity:" << endl;
  cin >> M;   //M cannot be negative, 0 (to avoid / by 0), or a non-number
  while (M <= 0 || cin.fail()) {
    cout << "Invalid input! Carrying capacity must be greater than 0." << endl;
    cin.clear();
    cin.ignore(999, '\n');
    cin >> M;
  }
  
  cout << "Enter the rate of population growth (as a percentage):" << endl;
  cin >> g;   //g cannot be negative or a non-number
  while (g < 0 || cin.fail()) {
    cout << "Invalid input! Rate of pop. growth must be 0 or greater." << endl;
    cin.clear();
    cin.ignore(999, '\n');
    cin >> g;
  }
  g = g / 100.00;   //convert % to decimal
  
  cout << "Enter the minimum loss rate (as a percentage):" << endl;
  cin >> h;   //h cannot be negative, over 100, or a non-number
  while (h < 0 || h > 100 || cin.fail()) {
    cout << "Invalid input! Min. loss rate must be between 0 and 100." << endl;
    cin.clear();
    cin.ignore(999, '\n');
    cin >> h;
  }
  h = h / 100.00;   //convert % to decimal
  
  for (int i = 1; i <= k; i++) {   //repeat formula for 1 to k years
    int formula = ((1 + g - h) * p_0) - (g * p_0 * p_0 / M);
    cout << setfill (' ') << setw (15) << left << i << formula << endl;
    p_0 = formula;   //e.g. value of p_0 becomes value of p_1 (recursion)
  }
  
  return 0;
  
}

/*
TEST CASES:
-I tested the 3 parameter sets given at the bottom of http://www.resnet.wm.edu/
~jxshix/math410/Verhulst.html in my program and the outputs were correct.
-I also tested my program for appropriate input error checking:
   - p_0: I input '-1' and 'abc' and got the error message each time.
   - k: I input '-1', '0', and 'abc' and got the error message each time.
   - M: Same as above.
   - g: Same thing as for p_0.
   - h: I input '-1', '101', and 'abc' and got the error message each time.
   - After the error messages for each input, I input valid values for each 
   input. The final output was correct.
-Finally, I identified critical values of g that led to oscillating and chaotic 
behavior (where: p_0 = 10; k = 20; M = 100; h = 20).
   -g value that starts oscillating behavior:
      - 203; starting at k = 11, population oscillates regularly b/w 91 and 89.
      - at g = 202, pop. oscillates from k = 3 to k = 13, but levels off after.
   -g value that starts chaotic behavior:
      - 280; starting at k = 3, pop. decreases and increases at irregular rates.
      - at g = 279, chaotic b/w k = 3 and k = 11, but regular oscillation after.
*/
