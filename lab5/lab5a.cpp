/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 5 - Tasks 0 & 1 (uses Pass-by-Value Function)

  This program replaces every d in num with d' (standard decimal representation
of a non-negative integer num, and digits d and d'). For example, if num=16762,
d=6, d'=8, the program returns 18782. This program assumes that the user does
not input decimal values or combinations of numbers and non-numbers.
*/

#include <iostream>
using namespace std;

// Precondition: num > 0
// Postcondition: return the number of digits in num
int numDigits(int num);   //prototype
  int numDigits(int num)   //definition
  {
    int digits = 0;
    while (num > 0)   //last iteration is when num is a single digit
    {
      num = num / 10;   //remove right-most digit (single digit becomes 0)
      digits++;   //digits will always be >=1, given precondition
    }
    return digits;
  }

// Precondition: num > 0; 1 <= index <= number of digits in num
// Postcondition: return the index'th digit of num
int getDigit(int num, int index);   //prototype
  int getDigit(int num, int index)   //definition
  {
    int digValue;   //holds value of index'th digit (of num)
    for (int i = numDigits(num); i >= index; i--)   //from last digit to index
    {
      if (num % 10 == 0)   //i.e. when last digit of current num is 0
      {
	digValue = 0;
        num = num / 10;   //remove right-most digit, for when num length >= 2
      }
      else   //i.e. num % 10 != 0, meaning right-most digit is not a 0
      {
	digValue = num % 10;   //digValue is right-most digit
	num = num / 10;   //remove right-most digit, for when num length >= 2
      }
    }   //end of for loop
    return digValue;   //digValue == value of index'th digit
  }   //end of getDigit function

// Precondition: num > 0
// Postcondition: e.g. num=16762, oldDigit=6, newDigit=8 -> returns 18782
int replaceDig(int num, int oldDigit, int newDigit);   //prototype
  int replaceDig(int num, int oldDigit, int newDigit)   //definition
  {
    int newNum = num;   //newNum is changed while num stays the same
    for (int i = numDigits(newNum); i >= 1; i--)   //last digit to first digit
    {
      newNum = replaceDig(num/10,oldDigit,newDigit);   //divide by 10 each time
      int digValue = getDigit(num,i);   //store value of i'th digit (of num)
      if (digValue == oldDigit)
	digValue = newDigit;   //replace oldDigit value with newDigit value
      else   //i.e. value of i'th digit != value of oldDigit
	digValue = digValue;   //keep same value (of i'th digit)
      newNum = newNum * 10 + digValue; //insert 0 at end, replace with digValue
      return newNum;   //newNum changes in for loop (when oldDigit is replaced)
    }
    return newNum;   //newNum is now num with all oldDigit replaced by newDigit
  }

int main () {
  
  int num;   //preconditions of above functions involve num > 0
  cout << "Input an integer that is greater than 0:" << endl;
  cin >> num;
  while (num <=0 || cin.fail()) {
    cin.clear();
    cin.ignore(999, '\n');
    cout << "Invalid input! The integer must be greater than 0." << endl;
    cin >> num;
  }

  int oldDigit;
  cout << "Input the value of the digit that will be replaced:" << endl;
  cin >> oldDigit;   //a digit is b/w 0 and 9 (inclusive)
  while (oldDigit < 0 || oldDigit > 9 || cin.fail()) {
    cin.clear();
    cin.ignore(999, '\n');
    cout << "Invalid input! Digit must be an integer between 0 and 9." << endl;
    cin >> oldDigit;
  }

  int newDigit;
  cout << "Input the value of the digit that will replace that digit:" << endl;
  cin >> newDigit;
  while (newDigit < 0 || newDigit > 9 || cin.fail()) {
    cin.clear();
    cin.ignore(999, '\n');
    cout << "Invalid input! Digit must be an integer between 0 and 9." << endl;
    cin >> newDigit;
  }

  cout << "The new integer is: " << replaceDig(num,oldDigit,newDigit) << endl;

return 0;

}

/*
  TESTING:
  - For oldDigit, I assumed that the user would input a digit present in num.
  - For newDigit, I assumed that the user would input a different digit.
  - Read the following as a table:
       num: 1 9 10 11 19 90 99 100 100 101 110 111 123 900 909 990 999 16762
  oldDigit: 1 9  0  1  1  9  9   1   1   0   0   1   1   0   9   9   9     6
  newDigit: 0 1  2  3  4  5  6   0   7   8   9   3   0   1   4   1   5     8
    output: 0 1 12 33 49 50 66   0 700 181 119 333  23 911 404 110 555 18782
*/
