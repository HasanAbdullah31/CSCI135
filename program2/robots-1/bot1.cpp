/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Program 2 - Task 1

  This program makes the robot collect all diamonds, given a vector of the
diamonds' locations. This program assumes that there are a total of 10 diamonds,
and that the dimensions of the map are 40*20.
*/

#include <cstdlib>
#include <iostream>
#include <cmath>   //for pow, sqrt, and abs functions
#include "bot1.h"
using namespace std;

static loc target; //will contain the shortest distances from robot to a diamond
struct Distances {   //distances from robot to each diamond (10 total)
  loc    xy[10];   //x and y distances
  double z[10];   //hypotenuse distances
} dist;

//initializes global variables if needed; not needed here
void init_robot(int w, int h, loc robot, ostream &log) {
  log << "Task 1: Automated diamond gathering" << endl;
}

//precond: dist is defined as above; dm is vector of 10 loc elements
loc shortestDistance(Distances &dist, loc robot, vector<loc> dm);
//postcond: dist contains a sorted list of z, and xy list corresponds to it;
//returns the x,y distances from robot's current location to closest diamond

/* Algorithm Explanation: Before the robot collects a diamond, it:
   1)Calculates the distances from itself to each remaining diamond
    [the horizontal (x), vertical (y), and hypotenuse (z) distances]
   2)Moves to the nearest diamond using a combination of LEFT/RIGHT and UP/DOWN
    [the diamond with shortest z distance using its x and y distances]
   3)repeat 1) and 2) until all diamonds are collected */
action choose_next_step(int w, int h, loc robot, vector<loc> dm, ostream &log) {
  /* IMPORTANT: static variables are not re-initialized on re-enter!!! */
  static vector<loc> ogdm = dm; //ogdm stays same, dm changes after each return
  static int dmcounter = 0; //program ends when robot collects all 10 diamonds
  while (dmcounter < 10) {
    static int C = 0;
    if (C == 0) {
      target = shortestDistance(dist,robot,ogdm); //executed once per iteration
      C++; //after return to this function, the if block is not executed again
    }
    //return exits function, so do ++ before returning action
    static int i = 0;
    if (target.x >= 0) { //diamond's x location is right from or = to robot's x
      while (i < target.x) {
	//if target.x == 0 (robot is on same column as diamond), don't move
	i++; return RIGHT;   //move target.x units right
      }
    }
    else if (target.x < 0) {   //diamond's x location is left from robot's x
      while (i < abs(target.x)) {
	i++; return LEFT;   //move target.x units left
      }
    }
    static int j = 0;
    if (target.y >= 0) {   //diamond's y location is up from or = to robot's y
      while (j < target.y) {
	//if target.y == 0 (robot is on same row as diamond), don't move
	j++; return UP;   //move target.y units up
      }
    }
    else if (target.y < 0) {   //diamond's y location is down from robot's y
      while (j < abs(target.y)) {
	j++; return DOWN;   //move target.y units down
      }
    }
    dmcounter++;   //assert: number of diamonds collected increases by 1
    //"remove" the location of the diamond the robot just collected from ogdm
    static int k = 0;
    for ( ; k < 10; k++) {   //assert: k was initialized to 0
      if (robot.x == ogdm[k].x && robot.y == ogdm[k].y) {
        ogdm[k].x = 99; ogdm[k].y = 99;
      } //next time shortestDistance is called, this diamond will be at the end
    }   //b/c largest x,y distances are 39,19; 99,99 is off map
    C = 0; i = 0; j = 0; k = 0;   //reset variables for next iteration
  }
}

loc shortestDistance(Distances &dist, loc robot, vector<loc> dm) {
  for (int a = 0; a < 10; a++) {   //distances from robot to each diamond
    dist.xy[a].x = dm[a].x - robot.x;
    dist.xy[a].y = dm[a].y - robot.y;
    dist.z[a] = sqrt( pow(dist.xy[a].x,2)+pow(dist.xy[a].y,2) );
  }
  for (int i = 0; i < 10; i++) {   //selection sort
    int min = i;   //stores the min. indexes
    for (int j = i+1; j < 10; j++) {
      if (dist.z[j] < dist.z[min])
	min = j;
    }
    //sort the hypotenuse (z) array from smallest to largest
    double temp1 = dist.z[min];
    dist.z[min] = dist.z[i]; dist.z[i] = temp1;
    //sort the xy array to correspond to the hypotenuse (z) array
    loc temp2 = dist.xy[min];
    dist.xy[min] = dist.xy[i]; dist.xy[i] = temp2;
  }
  return dist.xy[0];   //x,y distances from robot to closest diamond
}
