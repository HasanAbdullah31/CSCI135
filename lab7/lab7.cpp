/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 7

  This program makes new image files (task 0) where the original image file is
highlighted/segmented (task 1), is pixelated (task 2), and vertical edges are
detected (task 3).
*/

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>
using namespace std;

const int MAXWIDTH = 196;   //dimensions of city.pgm
const int MAXHEIGHT = 257;

//reads a PGM grayscale format from city.pgm into an array, and updates the
//height/width arguments appropriately (since they are passed by reference)
void readImage(int image[][MAXHEIGHT], int &width, int &height);

//writes the argument image (2-D array) to <file.pgm[PGM grayscale format]>
void writeImage(int image[][MAXHEIGHT], int width, int height, string file);

//task0: copies image to a 2nd array, and calls writeImage (file = "task0.pgm")
void copyImage(int image[][MAXHEIGHT], int width, int height) {
  int copy[width][MAXHEIGHT];   //will be a duplicate (2-D) array of image
  for (int row = 0; row < height; row++)
    for (int col = 0; col < width; col++)
      copy[col][row] = image[col][row];
  //copy will be changed in tasks 1-3 while keeping image the same
  string file = "task0.pgm";   //name of output file
  writeImage(copy,width,height,file);   //write the 2nd array back to file
  return;
}

//task1: makes all pixels below threshold 1 (T1) 0 and all pixels above T2 255
//(in duplicate array) and outputs to file "task1.pgm" using writeImage
void highlight(int image[][MAXHEIGHT], int width, int height, int t1, int t2);

//task2: makes each n-by-n non-overlapping window contain the avg. of the window
//(in duplicate array) and outputs to file "task2.pgm" using writeImage
void pixelate(int image[][MAXHEIGHT], int width, int height, int n);

//task3: detects vertical edges using a sliding window operator [3x3 window]
//(in duplicate array) and outputs to file "task3.pgm" using writeImage
void vedgeDet(int image[][MAXHEIGHT], int width, int height);

int main() {

  int width = MAXWIDTH, height = MAXHEIGHT;   //dimensions of city.pgm
  int image[width][MAXHEIGHT]; //all functions take 2nd dimension as MAXHEIGHT
  readImage(image,width,height);   //now image contains data from city.pgm

  {   //task0
  cout << "Task 0: A copy of city.pgm was created in task0.pgm." << endl;
  copyImage(image,width,height);
  /* TESTING: The resulting image was the same as the original image. */
  };
  
  {   //task1
  cout << "Task 1: Highlight" << endl;
  int t1,t2;
  cout << "Enter threshold 1 (T1):" << endl;
  //thresholds must be b/w -1 and 256 b/c grayscale values are 0 - 255
  cin >> t1;   //pixels below 0 are invalid, and pixels below 256 (and up) are
  //invalid even though it makes sense, since highest grayscale value == 255
  //if user wants image to be completely black, they can input t1=256,t2=255
  //if user wants image to be completely white, they can input t1=0,t2<0
  while (t1 < 0 || t1 > 256 || cin.fail()) {
    cin.clear();
    cin.ignore(999, '\n');
    cout << "Invalid input! T1 must be >= 0 and <= 256." << endl;
    cin >> t1;
  }   //t1 is now b/w 0 and 256 (inclusive)
  if (t1 == 256) {   //everything (values 0-255) goes to 0 (black)
    cout << "Since T1 is 256, the image will be all black." << endl;
    t2 = 255;   //pixels above 255 are invalid, so highlight ignores t2
  }
  else if (t1 <= 255) {   //i.e. 0 <= t1 <= 255
    cout << "Enter threshold 2 (T2):" << endl;
    cin >> t2;   //pixels above 255 are invalid, and t2 must be >= t1 - 1
    //so the thresholds don't converge (e.g. t1=255,t2=253; 254 in both)
    //t2 can be 255 for when t1 == 255 (values 0-254), so value 255 is unchanged
    //when t1 == 0, t2 can be any value b/c there are no pixels below 0
    while (t2 > 255 || t2 < (t1-1) || cin.fail()) {
      cin.clear();
      cin.ignore(999, '\n');
      cout << "Invalid input! T2 must be >= " << t1-1 << " and <= 255." << endl;
      cin >> t2;
    }   //t2 is now b/w -1 and 255 (inclusive)
    if (t1 == 0 && t2 == -1) {   //everything (values 0-255) goes to 255 (white)
    cout << "Since T1 is 0 and T2 is -1, the image will be all white." << endl;
    }
  }
  highlight(image,width,height,t1,t2);
  /*
    TESTING for Task 1 (read the following as a table):
    t1:   t2:       outImage.pgm description:
    256   skipped   all black.
    255   255       almost all black, with few white specks (value 255s).
    255   254       same as above.
      0   255       original image.
      0     0       almost all white, with a few black specks (value 0s).
      0    -1       all white.
      0   120       light/medium gray areas of original image are white.
    120   255       medium/dark gray areas of original image are black.
  */
  };

  {   //task2
  cout << "Task 2: Pixelate" << endl;
  //n must be b/w 1 and 196 (since city.pgm has width=196 and height=257)
  //b/c window size can't be <1 and can't be >196 (e.g. 197x197 in 196x257)
  int n;
  cout << "Enter the size of the pixelating window (n):" << endl;
  cin >> n;
  while (n < 1 || n > MAXWIDTH || cin.fail()) {
    cin.clear();
    cin.ignore(999, '\n');
    cout << "Invalid input! n must be >= 1 and <= "<<MAXWIDTH<<"."<< endl;
    cin >> n;
  }
  pixelate(image,width,height,n);
  /*
    TESTING for Task 2 (read the following as a table):
     n:   outImage.pgm description:
      1   original image.
    196   top part of image covered by a 196x196 gray square, bottom is same.
     99   top left of image covered by a 99x99 gray square, and right below
          that is a darker 99x99 square; rest of image is the same.
     98   four 98x98 different shaded gray squares on top part of image;
          rest of image (the bottom part) is the same.
      2   image is a bit blurry.
      3   even more blurry.
     10   lots of squares (shades are closely similar to parts in original).
  */
  };

  {   //task3
    cout << "Task 3: Vertical edges in city.pgm were detected and the resulting"
         << endl << "image was created in task3.pgm." << endl;
  vedgeDet(image,width,height);
  /*
    TESTING for Task 3: The resulting image was a v-edge detected image. The
    parts of the image that are vertical lines are white, rest of image black.
  */
  };

  return 0;
}

void highlight(int image[][MAXHEIGHT], int width, int height, int t1, int t2) {
  int copy[width][MAXHEIGHT];   //will be a highlighted 2-D array of image
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      if (image[col][row] < t1){   //all pixels below T1 become 0 (black)
	copy[col][row] = 0;
      }
      else if (image[col][row] > t2){   //all pixels above T2 become 255 (white)
	copy[col][row] = 255;
      }
      else if (image[col][row] >= t1 && image[col][row] <= t2){
	copy[col][row] = image[col][row]; //if not < t1 and not > t2, keep same
      }
    }
  }
  string file = "task1.pgm";   //name of output file
  writeImage(copy,width,height,file);   //write the 2nd array back to file
  return;
}

void pixelate(int image[][MAXHEIGHT], int width, int height, int n) {
  int copy[width][MAXHEIGHT];   //will be a pixelated 2-D array of image
  for (int row = 0; row < height; row++)
    for (int col = 0; col < width; col++)
      copy[col][row] = image[col][row];   //for parts of image w/o windows
  //number of horizontal windows and number of vertical windows
  int num_hwindows = width/n, num_vwindows = height/n;
  int row = 0, col = 0;
  //top window->bottom window, repeat for each column (if there are more)
  for (int hwindows = 0; hwindows < num_hwindows; hwindows++) {
    for (int vwindows = 0; vwindows < num_vwindows; vwindows++) {
      int ogrow = row, ogcol = col;   //original (og) values for both
      int sum = 0;   //sum of all pixels in window
      //vertical and horizontal size of each window is n
      for (row; row < ogrow+n; row++) {
	for (col; col < ogcol+n; col++) {
	  sum += image[col][row];
	}
	col = ogcol;   //reset col to its og value for next row in window
      }   //finished going through the current n-by-n window
      row = ogrow;   //now both col and row are their og values
      //each pixel in window is average of all pixels in the window
      int avg = (int)((double)sum/(double)(n*n));
      assert(avg >= 0 && avg <= 255);   //grayscale values are b/w 0 and 255
      for (row; row < ogrow+n; row++) {
	for (col; col < ogcol+n; col++) {
	  copy[col][row] = avg;
	}
	col = ogcol;
      }
    }   //loop repeats for all vert. windows in current vert. window column
    row = 0, col += n;   //repeat vwindows loop for next vert. window column
  }   //stop when next window cannot fit width of image (e.g. when n=100,
  //[100x100 window] there is only 1 window horizontally since width=196)
  string file = "task2.pgm";   //name of output file
  writeImage(copy,width,height,file);   //write the 2nd array back to file
  return;
}

void vedgeDet(int image[][MAXHEIGHT], int width, int height) {
  int copy[width][MAXHEIGHT];   //will be a v-edge detected 2-D array of image
  //the left/right columns and top/bottom rows of image are ignored
  for (int r = 0; r < height; r++)
    for (int c = 0; c < width; c++)
      copy[c][r] = image[c][r];
  //the 3x3 windows cannot exceed the boundaries of the image
  int num_hwindows = width-2, num_vwindows = height-2, row = 0, col = 0;
  //top window->bottom window, repeat for each column (if there are more)
  while (col < num_hwindows) {
    while (row < num_vwindows) {
      //original (og) values for both [top left of the 3x3 window]
      int ogrow = row, ogcol = col, sum;
      //vertical and horizontal size of each window is 3
      for (row; row < ogrow+3; row++) {
	for (col; col < ogcol+3; col++) {
	  if (row == ogrow+1 && col == ogcol+1){ //the center of the 3x3 window
	  /* a b c -> an example of a 3x3 window
             d e f -> e takes on the value of (c+2f+i)-(a+2d+g)
             g h i -> a is image[ogcol][ogrow] */
	  sum = ((image[ogcol+2][ogrow]+2*image[ogcol+2][ogrow+1]
	  +image[ogcol+2][ogrow+2])-(image[ogcol][ogrow]+2*image[ogcol][ogrow+1]
	  +image[ogcol][ogrow+2]));
	  if (sum < 0) sum = 0;   //grayscale values are b/w 0 and 255
	  if (sum > 255) sum = 255;
	  copy[col][row] = sum;   //i.e. e = (c+2f+i)-(a+2d+g)
	  }
	}
	col = ogcol;   //reset col to its og value for next row in window
      }   //finished going through the current 3x3 window
      row = ogrow+1, col = ogcol;   //repeat loop for next window down
    }   //when 3x3 window is at bottom, go to first row of next column
    row = 0, col += 1;
  }   //stop when next window cannot fit width of image
  string file = "task3.pgm";   //name of output file
  writeImage(copy,width,height,file);   //write the 2nd array back to file
  return;
}

void readImage(int image[][MAXHEIGHT], int &width, int &height) {
  char c;
  ifstream instr;
  instr.open("city.pgm");
  
  // read the header P2
  instr >> c;  assert(c == 'P');
  instr >> c;  assert(c == '2');

  // skip the comments (if any)
  while ((instr>>ws).peek() == '#') { instr.ignore(4096, '\n'); }

  instr >> width;
  instr >> height;

  assert(width <= MAXWIDTH);
  assert(height <= MAXHEIGHT);
  int max;
  instr >> max;
  assert(max == 255);

  for (int row = 0; row < height; row++)
    for (int col = 0; col < width; col++)
      instr >> image[col][row];
  instr.close();
  return;
}

void writeImage(int image[][MAXHEIGHT], int width, int height, string file) {
  ofstream ostr;
  ostr.open(file.c_str());   //name of output file specified in argument file
  if (ostr.fail()) {
    cout << "Unable to write file\n";
    exit(1);
  };
  
  // print the header
  ostr << "P2" << endl;
  // width, height
  ostr << width << ' ';
  ostr << height << endl;
  ostr << 255 << endl;

  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      assert(image[col][row] < 256);
      assert(image[col][row] >= 0);
      ostr << image[col][row] << ' ';
      // lines should be no longer than 70 characters
      if ((col+1)%16 == 0) ostr << endl;
    }
    ostr << endl;
  }
  ostr.close();
  return;
}
