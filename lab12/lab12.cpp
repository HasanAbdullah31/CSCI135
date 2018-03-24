/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 12

  This program fixes the unexpected results of the incorrect code given, and
allows command line arguments to be passed to main.
*/

#include <iostream>
#include <iomanip>   //to format the output
#include <cstdlib>   //for atoi (needed for C-string to int conversion)
using namespace std;

const int MAXSIZE = 16;
static int values[MAXSIZE];
static int i;  // bad idea to call a global variable i!
void initArray(int[], int);
void printArray(int[]);

// This initializes element arr[i] to val for each array element
void initArray(int arr[], int val)
{
  for (i=MAXSIZE-1; i >= 0; i--)
    arr[i] = val;
  return;
}
/* At first, the i started from MAXSIZE and went down to 0; however, this allows
   initArray to access a memory location that is not defined in the program,
   since values goes from values[0] to values[MAXSIZE-1], not values[MAXSIZE].
   This causes unexpected results when initArray is called in main. */

// This prints the contents of the argument array, with each element printed as
// "index: value" on its own line
// For example, a 4-element array containing {10,11,12,13} would print as:
//   0: 10
//   1: 11
//   2: 12
//   3: 13
void printArray(int arr[])
{
  for (int j = 0; j < MAXSIZE; j++) {
    cout << setw(2) << setfill(' ') << j << ": " << arr[j] << endl;
  }
  return;
};

/* main actually has parameters; argc is number of command line arguments + 1;
   argv is a pointer to an array of arguments (each is a C-string) */
int main(int argc, char * argv[3])
{
  if (argc != 3) {
    cout << "You are only allowed to use 2 arguments." << endl;
    return 1;
  }
  else if (atoi(argv[2]) < 0 || atoi(argv[2]) >= MAXSIZE) {
    cout << "Second argument must be >= 0 and < " << MAXSIZE << ".\n";
    return 1;
  }
  int dummy;
  initArray(values,atoi(argv[1]));
  int *arr2 = values; //arr2 points to the first element of values (alias)
  //change values[<input>] from <someint> to 9; arr2 changes as well (b/c alias)
  values[atoi(argv[2])]=9;
  printArray(values); //print values BEFORE changing arr2, which changes values
  //values[<input>] is also reverted to <someint> (arr2 is an alias of values)
  arr2[atoi(argv[2])]=atoi(argv[1]);
  arr2[1]=8;
  printArray(arr2); /* note that printArray(values) would do the same output
                       because arr2 is an alias of values */
  return 0;
};
