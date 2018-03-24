
#include "state.h"

void sample(state &s, int &x, int &y) {
  x = rand() % s.w;
  y = rand() % s.h;
}

void init(state &s, int width, int height, int diamonds) {
  s.w = width;
  s.h = height;
  
  // initialize the map
  s.map.resize(width);
  for(int i = 0; i<width; ++i) {
    s.map[i].resize(height);
    for(int j = 0; j<height; ++j) {
      s.map[i][j] = EMPTY;
    }
  }

  // add diamonds
  int n = diamonds;
  while(n > 0) {
    int x, y;
    sample(s, x, y);
    if (s.map[x][y] == EMPTY) {
      s.map[x][y] = DIAMOND;
      n--;
    }
  }
  s.initial_diamonds = diamonds;
  s.time = 0;
  s.score = 0;

  s.play = true;

  // add player
  while(true) {
    int x, y;
    sample(s, x, y);
    if (s.map[x][y] == EMPTY) {
      s.x = x;
      s.y = y;
      break;
    }
  }
}

void perform_action(state &s, action a) {

  s.time++;
  
  int dx = 0, dy = 0;
  switch (a) {
    case UP: dy += 1; break;
    case DOWN: dy -= 1; break;
    case RIGHT: dx += 1; break;
    case LEFT: dx -= 1; break;
  }
  
  int nx = s.x + dx;
  int ny = s.y + dy;
  if (nx >= 0 && nx < s.w && ny >= 0 && ny < s.h) {
    s.x = nx;
    s.y = ny;

    if (s.map[nx][ny] == DIAMOND) {
      s.map[nx][ny] = EMPTY;
      s.score++;
    }
  }
}

// Fisher-Yates shuffle
void shuffle_in_place(std::vector<loc> &v) {
  int i = v.size();
  while(i > 1) {
    i -= 1;
    int j = rand()%(i);
    // swap ith and jth elements
    loc t = v[i];
    v[i] = v[j];
    v[j] = t;
  }
}

void find_all_diamonds(state &s, std::vector<loc> &v){
  v.resize(0);
  for(int i = 0; i<s.w; ++i) {
    for(int j = 0; j<s.h; ++j) {
      if (s.map[i][j] == DIAMOND) {
        loc loc = {i,j};
        v.push_back(loc);
      }
    }
  }
  shuffle_in_place(v);
}

void update(state &s, std::ostream &gamelog) { 
  // don't do anything if the game has finished
  if (s.score >= s.initial_diamonds) return;

  // do robot's logic
  std::vector<loc> v;
  find_all_diamonds(s, v);
  loc pl = {s.x, s.y};
  action a = choose_next_step(s.w, s.h, pl, v, gamelog);
  perform_action(s, a);
}

