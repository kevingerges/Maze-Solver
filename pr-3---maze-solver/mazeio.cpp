/*
mazeio.cpp
*/

#include <iostream>
#include <fstream>
#include "mazeio.h"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from the given filename into a
 *  2D dynamically  allocated array.
 *
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem,
 * opening the file or reading in the integer sizes.
 *
 * The first argument is the filename of the maze input.
 *  You should use an ifstream to open and read from this
 *  file.
 *
 * We also pass in two pointers to integers. These are
 * output parameters (i.e. declared by the caller and
 * passed-by-reference for this function to fill in).
 * Fill the integers pointed to by these arguments
 * with the number of rows and columns
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(char* filename, int* rows, int* cols)
{


    ifstream inputf(filename); // reading the file in
   
  if (inputf.fail()){ // if file fails
    return NULL;

  }
  inputf >> *rows >> *cols; // taking in values
  char** arr1 = new char*[*rows]; // allocating 2d array

   for (int i=0; i < *rows; i++) { // allocating 2d array
       arr1[i] = new char[*cols];  
   }

   for (int i=0; i< *rows; i++) { // iterating through each row 
     for (int j=0; j < *cols; j++) { // iterating through each col
       inputf >> arr1[i][j]; // taking in values
     }
   }

 return arr1; //
}


/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols)
{
  cout << rows << " "<< cols << endl;
  
    // *** You complete **** CHECKPOINT
    for( int i=0; i < rows; i++){ // iterating through rows 
      for(int j =0; j < cols ;j++){ // iterating through cols 
        cout << maze[i][j]; // printing out the maze
      }
      cout<<endl;
    }
}

