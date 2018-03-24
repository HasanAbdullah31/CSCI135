/*
Author: Hasan Abdullah
Course: {135,136}
Instructor: Gilbert Pajela
Assignment: Lab 1 - Tasks 1 & 2

This program outputs: 1) a greeting to the instructor based on the time of day
and 2) the time to arrive at home based on expected minutes to get home.
*/

#include <iostream>
#include <ctime>   //for ctime library
#include <iomanip>   //to format minute output in TASK 2
using namespace std;

int main() {
  
  //TASK 1
  
  int sun_hours;   //1st input
  int sun_minutes;   //2nd input
  cout << "Enter the hours part of today's sunset time (4-9):" << endl;
  cin >> sun_hours;   //assume user enters legal value
  cout << "Enter the minutes part of today's sunset time (0-59):" << endl;
  cin >> sun_minutes;   //same assumption
  
  time_t t;
  struct tm *now;
  t = time(0);   //get current time
  now = localtime(&t);   //adjust for local timezone
  int hour = now->tm_hour;   //retrieve current hour
  int min = now->tm_min;   //retrieve current min
  
  if (hour < 12) {   //midnight-noon
    cout << "Good morning Gilbert Pajela." << endl;
  }
  else if (hour > 12 && hour < 12 + sun_hours) {   //noon-sunset limits
    cout << "Good afternoon Gilbert Pajela." << endl;
  }
  else if (hour == 12 + sun_hours && min < sun_minutes) {   //sunset hour &
    cout << "Good afternoon Gilbert Pajela." << endl;       //minutes max.
  }
  else if (hour == 12 + sun_hours && min > sun_minutes) {   //sunset hour &
    cout << "Good evening Gilbert Pajela." << endl;        //minutes min.
  }
  else if (hour > 12 + sun_hours) {   //sunset-midnight ends here
    cout << "Good evening Gilbert Pajela." << endl;
  }
  
/*
TEST CASES FOR TASK 1:
At 19:29, I input 7 hours and 30 minutes as sunset time. This was to test the
"Good afternoon" output at closest sunset max. time. The same was done at 19:31
to test the "Good evening" output at closest min. time. "Good morning" output
works before 12:00, "Good afternoon" output works between 12:00 and mentioned
maximum, and "Good evening" output works between mentioned minimum and 24:00.
*/
  
  //TASK 2 starts here; ctime int hour and int min are used here too
  
  int home_minutes;   //input
  
  cout << "How many minutes from now do you expect to be home?" << endl;
  cin >> home_minutes;
  
  int arrive_minute = min + home_minutes % 60;   //minute output
  int arrive_hour = hour + home_minutes / 60;   //hour output
  
  if (arrive_minute >= 60) {   //avoid minute output >= 60; e.g. 12:60
    arrive_hour = arrive_hour + arrive_minute / 60;   //e.g. 12:60 has 13 hours
    arrive_minute = arrive_minute % 60;   //e.g. 12:60 has 0 minutes
  }   //e.g. now 12:60 becomes 13:00
  cout << "You will get home at " << setfill ('0') << setw (2) <<
    arrive_hour << ":" << setfill ('0') << setw (2) <<   //e.g. '0:0'->'00:00'
    arrive_minute << endl;
  
  return 0;
  
}   //end of int main ()

/*
TEST CASES FOR TASK 2:
At 00:05, I input the following and received the following outputs:
-Input = 54 -> Output = 00:59; minute output < 60, works.
-Input = 55 -> Output = 01:00; minute output == 60, works.
-Input = 56 -> Output = 01:01; minute output > 60, works.
-Input = 120 -> Output = 02:05; same as above.
-Input = 150 -> Output = 02:35; same as above.
-Input = 1434 -> Output = 23:59; works again.
-Input = 1435 -> Output = 24:00; max. time on 24-hr clock reached.
-Input = 1436 -> Output = 24:01; this means next day at 00:01. I assumed the
user would understand this so I didn't bother to adjust the program.
*/
