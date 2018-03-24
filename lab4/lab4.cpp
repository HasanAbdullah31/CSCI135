/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 4

  This program computes n choose k in different ways, in order to evaluate each
one's effectiveness/efficiency. This program assumes that all inputs are legal.
For inputs to be legal in n choose k, n>=0 and 0<=k<=n (and all are integers).
*/

#include <iostream>
using namespace std;

int main () {

  //Task 1: compute n choose k using n!/(k!(n-k)!)
  
  {   //start of task 1
  int n, k, nf, kf, n_kf;   //f stands for factorial, n_kf is (n-k)!
  cout << "This program computes n choose k using n!/(k!(n-k)!)." << endl;
  cout << "Input n:" << endl;
  cin >> n;
  cout << "Input k:" << endl;
  cin >> k;

  for (int i = 0; i <= n; i++)
  {
    if (i == 0)
      nf = 1;   //i.e. 0! == 1 for when n == 0 (e.g. 0 choose 0 is 1)
    else
      nf = nf * i;   //n!
  }
  
  for (int i = 0; i <= k; i++)
  {
    if (i == 0)
      kf = 1;   //for when k == 0 (e.g. any value of n choose 0 is 1)
    else
      kf = kf * i;   //k!
  }
  
  for (int i = 0; i <= (n - k); i++)
  {
    if (i == 0)
      n_kf = 1;   //e.g. 5 choose 5 should be 1, but 5!/(5!0!) is undefined
    else
      n_kf = n_kf * i;   //(n-k)!
  }

  cout << n << " choose " << k << " is equal to: " //n choose k == n!/(k!(n-k)!)
       << nf / (kf * n_kf) << endl << endl;   //empty line above task 2

  /* n = 12 is the largest value of n where n choose (n-1) returns the correct
     result. For n >= 13, n choose (n-1) returns incorrect values because the
     max. int value has been exceeded in 13! and higher. In fact, once the max.
     int has been reached, the remaining value in 13! (and higher) is wrapped
     (in bit representation), so the resulting value is incorrect.
  */
  };   //end of task 1; variables n,k,nf, and kf are out of scope here
  
  //Task 2: compute n choose k using n(n-1)(n-2)...(n-k+1)/k!
  
  {   //n,k,nf, and kf are "new" variables in start of task 2
  int n, k, nf, kf;   //same as task 1, but no (n-k)! and n! goes to (n-k+1)
  cout << "This program computes n choose k using n(n-1)...(n-k+1)/k!." << endl;
  cout << "Input n:" << endl;
  cin >> n;
  cout << "Input k:" << endl;
  cin >> k;

  if (k == 0)   //the problem in next loop: n >= n + 1 b/c i starts at n
    nf = 1;   //n choose 0 == 1
  for (int i = n; i >= n - k + 1; i--)   //from n to n-k+1 (i goes down)
  {   //when k == 0, this loop is skipped (e.g. 5 >= 5 - 0 + 1 --> 5 >= 6)
    if (i == n)
      nf = n;   //starting value in n! is n
    else
      nf = nf * i;   //! ends at (n-k+1) rather than at 1
  }
  
  for (int i = 0; i <= k; i++)   //same as in task 1
  {
    if (i == 0)
      kf = 1;
    else
      kf = kf * i;   //k!
  }

  cout << n << " choose " << k << " is equal to: "
       << nf / kf << endl << endl;   //n choose k == n(n-1)(n-2)...(n-k+1)/k!

  /* n = 12 is the largest value of n where n choose (n-1) returns the correct
     result, once again. For n >= 13, n choose (n-1) returns incorrect values
     because the max. int value has been exceeded in 13! and higher (e.g. 13
     choose 12 in this program == 13*12*11*...*(13-12+1)[i.e. 2]/12!). In terms
     of efficiency, this program is better than the program in task 1 because
     it does fewer multiplies, in most cases. Task 1 does (n-1)+(k-1)+(n-k-1)+1=
     2(n-1) multiplies, while task 2 does (k-1)+(k-1)=2(k-1) multiplies.
  */
  };   //end of task 2

  //Task 3: make task 2 program more efficient using C(n,k) == C(n,n-k)
  
  {   //almost everything is the same as in task 2
  int n, k, k2, nf, kf;   //k2 is a substitute variable for k
  cout << "This program computes n choose k using n(n-1)...(n-k+1)/k!" << endl
       << "and the fact that C(n,k) = C(n,n-k)." << endl;
  cout << "Input n:" << endl;
  cin >> n;
  cout << "Input k:" << endl;
  cin >> k;
  k2 = k;   //k2 holds k's value so k2 can be changed later and k stays the same
  
  //the first if statement is basically task 3
  if (k2 > n / 2)   //n choose k is symmetrical (Pascal's triangle) across n/2
    k2 = n - k2;   //e.g. C(5,5) -> C(5,0); C(5,4) -> C(5,1); C(5,3) -> C(5,2)
  if (k2 == 0)   //the problem in next loop: n >= n + 1 b/c i starts at n
    nf = 1;   //n choose 0 == 1
  for (int i = n; i >= n - k2 + 1; i--)   //from n to n-k+1 (i goes down)
  {   //when k == 0, this loop is skipped (e.g. 5 >= 5 - 0 + 1 --> 5 >= 6)
    if (i == n)
      nf = n;   //starting value in n! is n
    else
      nf = nf * i;   //! ends at (n-k+1) rather than at 1
  }
  
  for (int i = 0; i <= k2; i++)
  {
    if (i == 0)
      kf = 1;
    else
      kf = kf * i;   //k!
  }

  //k2 != k b/c it was changed in first for loop; k is original user input
  cout << n << " choose " << k << " is equal to: "   //cout original k
       << nf / kf << endl << endl;   //n choose k == n(n-1)(n-2)...(n-k+1)/k!
  
  };   //end of task 3
  
  //Task 4: compute n choose k using (1+(n-k)/1)(1+(n-k)/2)...(1+(n-k)/k)
  
  {
  int n, k;
  cout << "This program computes n choose k using (1+(n-k)/1)(1+(n-k)/2)"
       << endl << "(1+(n-k)/3)...(1+(n-k)/k)." << endl;
  cout << "Input n:" << endl;
  cin >> n;
  cout << "Input k:" << endl;
  cin >> k;

  double f;   //(1+(n-k)/1)(1+(n-k)/2)...(1+(n-k)/k) results in a decimal value
  for (int i = 0; i <= k; i++)
  {
    if (i == 0)
      f = 1.00;   //n choose 0 == 1+(n-0)/0 is undefined, but should be 1
    else
      f = (1.00 + ((double) (n - k) / (double) i)) * f;
  }

  //f is of type double; when f is a large #, result is in scientific notation
  cout << n << " choose " << k << " is equal to: " << f << endl;
  
  };   //end of task 4
  
  return 0;

}   //end of int main

/*
  TESTING:
 -For C(0,0), C(1,0), C(1,1), C(2,0), C(2,1), C(2,2), C(11,5), C(11,6), C(12,0),
  C(12,12), C(12,1), C(12,11), C(12,5), C(12,6), and C(12,7), all 4 programs
  output the correct results. In other words, it can be inferred that all 4
  programs output correct results for the first 13 rows of Pascal's triangle.
 -Task 1 output correct results for C(33,0) and C(33,33), but for C(34,0) and
  C(34,34), there were 'core dumped' errors. Task 1 output incorrect results for
  C(13,1), C(13,12), C(13,5), C(13,8), C(13,6), and C(13,7). In other words,
  task 1 outputs incorrect results when n>=13 and 1<=k<=(n-1).
 -Task 2 output correct results for C(99999,0) and C(33,33), but for C(34,34),
  there was a 'core dumped' error. For n=13, task 2 output correct results for
  0<=k<=10 or k=13; for n=14 or n=15, the output was correct for 0<=k<=9 (or
  k=14 or k=15 respectively). For n=16, the output was correct for 0<=k<=8 or
  k=16. Despite some errors, task 2 handles more n and k values than task 1.
 -Task 3 output correct results for C(99999,0) and C(99999,99999) (i.e. when
  k=0 or k=n, task 3 has correct outputs and 'core dumped' doesn't occur for the
  most part). The output was also correct for all 0<=k<=n when n=13,14,15, or
  16. However, when n=18 and k=9 or when n=20 and k=10, the output is incorrect.
  So task 3 is more correct than tasks 1 and 2, but not always correct.
 -Task 4 output correct results for C(99999,0) and C(99999,99999). The output
  was also correct for when n=999, and k=1,k=998,k=2,k=997,k=499, and k=500. We
  can assume the other k values would produce correct results as well. Overall,
  task 4 is a lot more correct than task 3, but not super precise due to the
  result being in scientific notation.
*/
