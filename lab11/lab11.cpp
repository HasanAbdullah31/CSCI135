/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 11

  This program processes data whose size is not known statically. The processing
will be on the same dataset as lab 10. This program assumes that the user does
not input a decimal number or a combination of numbers and non-numbers.
*/

#include "lab11.h"

int main() {
  
  Node* world;
  readFile(world);   //task0
  cout << "This program will output the countries that had" << endl
       << "2015 populations between M and N (inclusive):" << endl;
  //I assumed the user would not input a number > INT_MAX
  cout << "Enter M:" << endl;
  int m; cin >> m;
  while (m < 0 || cin.fail()) {   //population can't be negative or > INT_MAX
    cout << "Invalid input! M must be an integer greater than or equal to 0.\n";
    cin.clear();
    cin.ignore(999,'\n');
    cin >> m;
  }
  cout << "Enter N:" << endl;
  int n; cin >> n;
  while (n < m || cin.fail()) {   //n must be >= m and <= INT_MAX
    cout << "Invalid input! N must be greater than or equal to " << m << ".\n";
    cin.clear();
    cin.ignore(999,'\n');
    cin >> n;
  }
  int size; printCountries(m,n,size,world);
  /* TESTING (the following is a table of inputs and outputs):
     m         n         output (i.e. list of countries):
     0         0         [None]
     0         1000      Holy See.
     0         799       [None]
     800       800       Holy See.
     801       1000      [None]
     800       2000      Tokelau, Niue, Holy See.
     801       2000      Tokelau, Niue.
     2000      10000     Tuvalu, Saint Pierre and Miquelon, Falkland Islands
                         (Malvinas), Montserrat, Saint Helena.
     10000     20000     Wallis and Futuna Islands, Nauru, Anguilla.
     20000     30000     Cook Islands, Palau, Caribbean Netherlands.
     1000000   2000000   Trinidad and Tobago, Latvia, Estonia, Cyprus, Bahrain,
                         Timor-Leste, Guinea-Bissau, Gambia, Swaziland, Gabon,
                         Mauritius.
     7500000   10000000  Papua New Guinea, Honduras, Switzerland, Austria,
                         Serbia, Sweden, Hungary, Belarus, United Arab Emirates,
                         Jordan, Israel, Azerbaijan, Tajikistan.
     100000000 200000000 Mexico, Russian Federation, Philippines, Pakistan,
                         Bangladesh, Japan, Nigeria.
     200000000 500000000 United States of America, Brazil, Indonesia.
     500000000 1000000000 [None]
     1000000000 2000000000 India, China.
     0          2000000000 [all 229 countries in the file]
     -The following was done here to get the same data:
      string* task1 = printCountries(m,n,size,world);
      for (int i = 0; i < size; i++) { cout << task1[i] << endl; }
      This means that printCountries returned the array, as intended.
  */
  return 0;
}
