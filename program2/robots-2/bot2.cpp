/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Program 2 - Task 2

  This program makes the robot collect all diamonds and explore the map, given a
2-D vector that contains the entire map of the area. This program assumes that
there are a total of 10 diamonds, and that the dimensions of the map are 40*20.
*/

#include <cstdlib>
#include <iostream>
#include <cmath>   //for pow, sqrt, and abs functions
#include "bot2.h"
using namespace std;

static loc target; //will contain the shortest distances from robot to a diamond
struct Distances {   //distances from robot to each diamond (10 total)
  loc    dm[10];   //will hold the locations of the diamonds
  loc    xy[10];   //x and y distances
  double z[10];   //hypotenuse distances
} dist;

//initialize robot's target to closest corner of the map
void init_robot(int w, int h, loc robot, ostream &log) { //w = 40, h = 20
  log << "Task 2: Exploring new mining areas" << endl;
  /* robot's scanner explores 4 units in each direction, but not at corners */
  //if robot is in top left quadrant of map, go to top left corner (3,16)
  if (robot.x <= (w-1)/2 && robot.y > (h-1)/2) {
    target.x = 3 - robot.x; target.y = (h-4) - robot.y;
  }
  //if robot is in bottom left quadrant, go to bottom left corner (3,3)
  else if (robot.x <= (w-1)/2 && robot.y <= (h-1)/2) {
    target.x = 3 - robot.x; target.y = 3 - robot.y;
  }
  //if robot is in top right quadrant, go to top right corner (36,16)
  else if (robot.x > (w-1)/2 && robot.y > (h-1)/2) {
    target.x = (w-4) - robot.x; target.y = (h-4) - robot.y;
  }
  //if robot is in bottom right quadrant, go to bottom right corner (36,3)
  else if (robot.x > (w-1)/2 && robot.y <= (h-1)/2) {
    target.x = (w-4) - robot.x; target.y = 3 - robot.y;
  }
}

void locateDiamonds(int w, int h, Distances &dist,
		    const vector< vector<tile> > map);
//postcond: dm filled with the locations of remaining diamonds on map
//if a diamond was collected before, its location is ignored [set to (99,99)]

loc shortestPath(Distances &dist, loc robot);
//postcond: dist contains a sorted list of z, and xy list corresponds to it;
//returns the x,y distances from robot's current location to closest diamond

void changeTarget(int w, int h, loc robot, int ry1, int ty1, int ry2, int ty2);
//postcond: target.x becomes +-(w-7) [depending on robot's x coordinate]
//if robot.y == ry1, target.y = ty1; else if robot.y == ry2, target.y = ty2

//precond: i and j are both static and initialized to 0
action goToTarget(int &i, int &j, loc target);
//returns LEFT/RIGHT target.x times and UP/DOWN target.y times; i and j updated

/* Algorithm Explanation:
   1)Robot goes to the nearest corner [(3,16),(3,3),(36,16), or (36,3)]
   2)Zigzags across the map; stops when it has explored the entire map
   3)Locates all remaining diamonds on the map
   4)Robot collects each diamond using the following procedure:
     1)Calculate the distances from itself to each remaining diamond
     2)Move to the nearest diamond using a combination of LEFT/RIGHT and UP/DOWN
     3)repeat 1) and 2) until all diamonds are collected */
action choose_next_step(int w, int h, loc robot,
			const vector< vector<tile> > map, ostream &log) {
  /* IMPORTANT: static variables are not re-initialized on re-enter */
  /* return exits function, so do ++ before returning action */
  /* change runtime of blocks with ctr and check variables */
  static int i = 0, j = 0;   //iterator variables for robot movements
  // 1) move robot to nearest corner as defined in init_robot
  static const int numMoves1 = abs(target.x)+abs(target.y);
  static int ctr1 = 0;
  while (ctr1 < numMoves1) {
    ctr1++; return goToTarget(i,j,target);
  } //assert: robot's location is either (3,16), (3,3), (36,16), or (36,3)
  
  // 2) move robot to other side (if on LEFT, go RIGHT; if on RIGHT, go LEFT)
  static bool check2 = true;
  if (check2 == true) {
    //if on bottom corner, move scanner up 4 units; if top, move down 4 units
    changeTarget(w,h,robot,3,4,h-4,-4);
    i = 0; j = 0;   //reset iterators for next path
    check2 = false;   //execute this block only on first enter
  }
  static const int numMoves2 = abs(target.x)+abs(target.y);
  static int ctr2 = 0;
  while (ctr2 < numMoves2) {
    ctr2++; return goToTarget(i,j,target);
  } //assert: robot's location is either (36,12), (36,7), (3,12), or (3,7)
  
  // 3) same as 2) except robot.y conditions moved +- 4 units
  static bool check3 = true;
  if (check3 == true) {
    changeTarget(w,h,robot,7,4,h-8,-4);
    i = 0; j = 0; check3 = false;
  }
  static const int numMoves3 = abs(target.x)+abs(target.y);
  static int ctr3 = 0;
  while (ctr3 < numMoves3) {
    ctr3++; return goToTarget(i,j,target);
  } //assert: robot's location is either (3,8), (3,11), (36,8), or (36,11)
  
  // 4) same as 3) except target.y moved +- 1 unit for extra scanner space
  static bool check4 = true;
  if (check4 == true) {
    changeTarget(w,h,robot,11,5,h-12,-5);
    i = 0; j = 0; check4 = false;
  }
  static const int numMoves4 = abs(target.x)+abs(target.y);
  static int ctr4 = 0;
  while (ctr4 < numMoves4) {
    ctr4++; return goToTarget(i,j,target);
  } //assert: robot's location is either (36,3), (36,16), (3,3), or (3,16)
  
  // 5) move robot to other side (i.e. target.x = +-(w-7); target.y = 0)
  static bool check5 = true;
  if (check5 == true) {
    changeTarget(w,h,robot,3,0,h-4,0);
    i = 0; j = 0; check5 = false;
  }
  static const int numMoves5 = abs(target.x)+abs(target.y);
  static int ctr5 = 0;
  while (ctr5 < numMoves5) {
    ctr5++; return goToTarget(i,j,target);
  } //assert: the entire map has been explored

  // 6) locate all remaining diamonds on the map
  static bool check6 = true;
  if (check6 == true) {
    locateDiamonds(w,h,dist,map);
    i = 0; j = 0; check6 = false;
  }
  // 7) collect the remaining diamond(s) [now we just repeat task 1's code]
  static int dmcounter = 0; //program ends when robot collects all 10 diamonds
  static int moves;   //the number of moves from robot to closest diamond
  while (dmcounter < 10) {
    static int C = 0;
    if (C == 0) {   //executed once per iteration
      target = shortestPath(dist,robot);
      moves = abs(target.x)+abs(target.y);
      C++; //after return to this function, the if block is not executed again
    }
    while (abs(i)+abs(j) < moves) { //abs(i)+abs(j) starts at 0, ends at moves-1
      return goToTarget(i,j,target);
    }
    dmcounter++;   //assert: number of diamonds collected increases by 1
    //"remove" the location of the diamond the robot just collected from dist.dm
    static int k = 0;
    for ( ; k < 10; k++) {   //assert: k was initialized to 0
      if (robot.x == dist.dm[k].x && robot.y == dist.dm[k].y) {
        dist.dm[k].x = 99; dist.dm[k].y = 99;
      }   //next time shortestPath is called, this diamond will be at the end
    }     //b/c largest x,y distances are 39,19; 99,99 is off map
    C = 0; i = 0; j = 0; k = 0;   //reset variables for next iteration
  }
}

void locateDiamonds(int w, int h, Distances &dist,
		    const vector< vector<tile> > map) {
  //Each element map[x][y] can be either of {EMPTY, DIAMOND, UNEXPLORED}
  int ctr = 0;
  for (int col = 0; col < h; col++) {
    for (int row = 0; row < w; row++) {
      if (map[row][col] == DIAMOND) {
	dist.dm[ctr].x = row;
	dist.dm[ctr].y = col;
	ctr++;
      }
    }
  }
  /* assert: ctr <= 10, but not necessarily == 10 (i.e. robot may have collected
     a diamond before calling this function); so ignore the collected diamonds
     by setting their coordinates off map (99,99) */
  for (int i = ctr; i < 10; i++) {
    dist.dm[i].x = 99;
    dist.dm[i].y = 99;
  }
  return;
}

loc shortestPath(Distances &dist, loc robot) {
  for (int a = 0; a < 10; a++) {   //distances from robot to each diamond
    dist.xy[a].x = dist.dm[a].x - robot.x;
    dist.xy[a].y = dist.dm[a].y - robot.y;
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

void changeTarget(int w, int h, loc robot, int ry1, int ty1, int ry2, int ty2) {
  //if on left corner, go to right corner, and vice versa
  if (robot.x == 3) {
    target.x = w - 7;
  }
  else if (robot.x == w-4) {
    target.x = 7 - w;
  }
  //if on ry1, move scanner ty1 units; if on ry2, move scanner ty2 units
  if (robot.y == ry1) {
    target.y = ty1;
  }
  else if (robot.y == ry2) {
    target.y = ty2;
  }
  return;
}

action goToTarget(int &i, int &j, loc target) {
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
}
