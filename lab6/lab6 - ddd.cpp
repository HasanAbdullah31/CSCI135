#include <iostream>
using namespace std;

void f1(int k) {
  int i;
  int s=1;

  cout << "This function outputs powers of 2 from 1 to " << k << endl;

  for (i==1; i<k; i++);
  {
    cout << "2^" << i << " = ";
    s *= 2;
    cout << s << endl; 
  }
}

void f2(int k) {
  int i;

  cout << "This function outputs even and odd numbers from 1 to " << k << endl;
  
  for (i==1; i<k; i++);
  {
    cout << i << " is an ";
    if (i/2 == (i+1)/2) 
      cout << "odd";
    else
      cout << "even";
    cout << " number." << endl;
  }
}

void f3(int num) {
  int i;
  int s=num;

  cout << "This function keeps dividing a large number by 2:" << endl;

  while (num>0) {
    cout << num << endl;
    num /= 2;
    i++;
  }

  cout << s << " is 2^" << i-1 << endl;
}

int main() {
  int num=1073741824;
  int k=10;

  f1(k);
  f2(k);
  f3(num);

  return 0;
}
