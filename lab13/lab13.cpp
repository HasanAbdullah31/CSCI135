/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 13

  This program uses recursive functions to identify if a string is a palindrome.
*/

#include <iostream>
#include <string>
using namespace std;

int mylength(string x);   //Task 1
//postcond: returns length of x [same as x.length() or x.size()] by recursion

bool isPalindrome(string x);   //Task 0; precond: Task 1
//postcond: returns true if x is a palindrome, else returns false

int main () {

  string x;
  cout << "Enter a sentence:" << endl;
  cin >> x;
  if (isPalindrome(x))
    cout << "Your sentence is a palindrome." << endl;
  else
    cout << "Your sentence is not a palindrome." << endl;
  /* TESTING:
     x:                      isPalindrome:
     a                       Yes.
     aa                      Yes.
     ab                      No.
     ba                      No.
     aaa                     Yes.
     aba                     Yes.
     bab                     Yes.
     abb                     No.
     bba                     No.
     amanaplanacanalpanama   Yes. */
  return 0;
}

//base case: if x is an empty string, return length == 0; while x is not empty,
//return the string with 1 less character and increment length by 1
int mylength(string x) {
  if (x == "") {
    return 0;
  }
  else {   //x has more characters
    return 1+mylength(x.substr(1));   //return x with 1 less character
  }
}

//x has length n: isPalindrome(x) = (x[0]==x[n-1]) AND isPalindrome(x[1..n-2])
bool isPalindrome(string x) {
  int length = mylength(x);
  if (length <= 1) {   //base case: all strings of length 1 are palindromes
    return true;
  }
  else if ( x.at(0) == x.at(mylength(x)-1) ) {
    x = x.substr(1,length-2);
    return isPalindrome(x);
  }
  else {   //if at any point opposite elements in x are not ==
    return false;
  }
}
