
#ifndef BOT_H
#define BOT_H

#include <vector>
#include <iostream>

using namespace std;

/* Four actions available to the robot */
enum action {LEFT, RIGHT, UP, DOWN};

/* Location */
struct loc {
  int x;
  int y;
};

/* choose_next_step(w, h, robot, dm, log) 
 * 
 *    Returns the next action to perform: UP, RIGHT, DOWN, or LEFT
 *
 * Arguments:
 * w and h: width and height of the map,
 * robot: location of the robot (Example: robot.x and robot.y are its x and y coordinates),
 * dm: vector of diamonds' locations 
 *    (Example: dm[0].x and dm[0].y are the coordinates of the first diamond)
 */
action choose_next_step(int w, int h, loc robot, vector<loc> dm, ostream &log);


/* init_robot (w, h, robot, log) 
 * 
 * This funciton runs before the robot starts moving. Use it to initialize 
 * global variables if you need them.
 */
void init_robot(int w, int h, loc robot, ostream &log);


#endif
