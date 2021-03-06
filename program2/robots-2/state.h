
#ifndef STATE_H
#define STATE_H

#include <cstdlib>
#include <iostream>
#include <vector>

#include "bot2.h"
#include "outstream.h"

struct state {
  // dimensions
  int w;
  int h;
  // map
  std::vector <std::vector<tile> > map;
  std::vector <std::vector<bool> > explored;
  int initial_diamonds;
  int time;
  int score;

  // player
  int x;
  int y;

  // UI
  bool play;
};

void init(state &s, int width, int height, int diamonds);

void update(state &s, std::ostream &gamelog);

#endif
