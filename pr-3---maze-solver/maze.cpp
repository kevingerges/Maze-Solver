/*
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;


int maze_search(char**, int, int);




// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
    int rows, cols, result;
    char** mymaze=NULL;
    
    const char* invalid_char_message = "Error, invalid character.";
    const char* invalid_maze_message = "Invalid maze.";
    const char* no_path_message = "No path could be found!";

    if(argc < 2)
    {
        cout << "Please provide a maze input file" << endl;
        return 1;
    }

    mymaze = read_maze(argv[1], &rows, &cols); // <---TASK: COMPLETE THIS FOR CHECKPOINT 
  
  


    result = maze_search(mymaze, rows, cols);



    
    
     for(int i=0; i< rows;i++){   // iterating through every row 
     for (int j =0; j < cols; j++){  // iterating through every row 
       if (mymaze[i][j] != '.' && mymaze[i][j] != '#' && mymaze[i][j] != 'S' && mymaze[i][j] != 'F' ){ // checking for errors and edge cases   
         cout << invalid_char_message << endl;
       }        
     }
     }
     if (result == 1){ // if result equals to return 1 then print the print maze 
    print_maze(mymaze, rows, cols);
    }
    if (result == 0){ // if result equals to return 1 then print the following message
      cout << no_path_message << endl;
    }
    else if  (result == -1){ // if result equals to return 1 then print the following message  
      cout << invalid_maze_message << endl;
    }


    

    

 for (int i=0; i < rows; i++) { // deallocating our 2d array
      delete[] mymaze[i];
   }
   delete[] mymaze; // deallocating our 2d array
    return 0;
   

}


int maze_search(char** maze, int rows, int cols)
{

    Queue q(rows*cols);  // intiazling the queue to the max size
    Location s;  // creating Location start
    s.row = 0;  // assigning it to zero
    s.col = 0;  // assigning it to zero

    Location f; // creating Location finish
    f.row = 0; // assigning it to zero
    f.col = 0; // assigning it to zero
  
    bool** explore = new bool*[rows]; // creating our explore 2d array

    for (int i=0; i < rows; i++) { // creating our explore 2d array
       explore[i] = new bool[cols];  
    }

   for(int i=0; i< rows;i++){ // setting our explore 2d array to false
     for (int j =0; j < cols; j++){
       explore[i][j] = false;

     }
   }

    int s_found = 0; // initializing  variables to decide when to break for s found 
    int f_found = 0;  // initializing  variables to decide when to break for f found



   for(int i = 0; i < rows;i++){ // iterating through every row
     for (int j = 0; j < cols; j++){  // iterating through every col
       if( maze[i][j] == 'S'){ // if we find 'S'
          s.row = i;  //  assigning it the row cordinates
          s.col = j;  //  assigning it the col cordinates
          s_found++; // increment our s found  
       }
      if (maze[i][j] == 'F') // if we find 'F'
       {
         
         f.row = i;   // assigning it the row cordinates
         f.col = j;  //  assigning it the col cordinates
         f_found++; // increment our f found  
       }

     }
   } 



   if (f_found != 1 ) { // checking if f found isn't there
     return -1;     
   }
   if (s_found != 1 ) { // checking if s found isn't there
     return -1;
   }
   

  Location** predecessor = new Location*[rows]; // allocating our 2d array for predecessor

    for (int i=0; i < rows; i++) {  // allocating our 2d array for predecessor
       predecessor[i] = new Location[cols];  
    }

     for (int i=0; i < rows; i++) { // iterating through rows
       for (int j =0; j < cols; j++){ // iterating through col
       predecessor[i][j].row = -1;   // assigning its row cordinates to -1 
       predecessor[i][j].col = -1;   // assigning its col cordinates to -1 
    }
    }


    
    Location current; // creating a Location variable
    current.row = 0;  // assigning its row cordinates to 0 
    current.col = 0;  // assigning its row cordinates to 0
    
 
    q.add_to_back(s);   // adding it to the queue

   int x = 0; // initializing
    while(! q.is_empty()) // starting BFS
    {

      x++; // increment 

      if (maze[current.row][current.col]== 'F' &&  x != 1 ){ // checking our 
      //maze rows and col for F and check if 
        f.row = current.row; // assigning f row cordinates to current
        f.col = current.col; // assigning f col cordinates to current
        break;
      }
      current = q.remove_from_front(); // removing current from the front 
      
      Location north; // creating new variables for north
      Location east; // creating new variables for east
      Location west; // creating new variables for west
      Location south; // creating new variables for south

      north.row = current.row-1; // assigning north rows 
      north.col = current.col; // assigning north cols 

      east.row = current.row; // assigning east rows 
      east.col = current.col+1; // assigning east cols 

      west.row = current.row; // assigning west rows 
      west.col = current.col-1; // assigning west cols 
 
      south.row = current.row+1; // assigning south rows 
      south.col = current.col; // // assigning south col 

      // checking our north boundaries and all edge cases 
      if ( (north.row  >= 0) && (north.row < rows)  && (north.col  >= 0 ) && (north.col < cols) &&(maze[north.row][north.col] != '#') && (maze[north.row][north.col] != 'S') &&  (explore[north.row][north.col] == false) ) { 
        explore[north.row][north.col] = true; // assigning the explore array to
        // true on both rows an cols
        q.add_to_back(north); // adding it to the queue
        predecessor[north.row][north.col] = current; // assigning the north rows and cols to the current

      }
      // checking our east boundaries and all edge cases 
      if ( (east.row  >= 0 )&& (east.row < rows) && (east.col  >= 0 ) && (east.col < cols) && (maze[east.row][east.col] != '#') && (maze[east.row][east.col] != 'S') &&  (explore[east.row][east.col] == false) ) { 
        explore[east.row][east.col] = true; // assigning the explore array to 
        //true on both rows an cols
        q.add_to_back(east);  // adding it to the queue
        predecessor[east.row][east.col] = current; // assigning the east rows and cols to the current

      }
      // checking our west boundaries and all edge cases 
      if ( (west.row  >= 0) && (west.row < rows) &&(west.col  >= 0 ) && (west.col < cols)&& (maze[west.row ][west.col] != '#') && (maze[west.row][west.col] != 'S') &&  (explore[west.row][west.col] == false) ) { 
        explore[west.row][west.col] = true; // assigning the explore array 
        //to true on both rows an cols
        q.add_to_back(west);  // adding it to the queue
         predecessor[west.row][west.col] = current; // assigning the west rows and cols to the current

      }
        // checking our south boundaries and all edge cases 
      if ( (south.row  >= 0 )&& (south.row < rows) && (south.col  >= 0 ) && (south.col < cols)&&  (maze[south.row][south.col] != '#') && (maze[south.row ][south.col] != 'S') &&  (explore[south.row][south.col] == false) ) { 
        explore[south.row][south.col] = true; // assigning the explore array 
        // to true on both rows an cols
        q.add_to_back(south);  // adding it to the queue
        predecessor[south.row][south.col] = current; // assigning the south 
        // rows and cols to the current

      }
    }



      current.row = f.row; // assigning the current row to f row
      current.col = f.col;  // assigning the current col to f col
     
    // starting our backtracking process
    while ( (predecessor[current.row][current.col].row != -1 ) || (predecessor[current.row][current.col].col != -1) ) 
      
      {
        // if S isn't found
        if( maze[predecessor[current.row][current.col].row][predecessor[current.row][current.col].col] !='S') { 

        
        // backtracking to the shortest path while adding  *
        maze[predecessor[current.row][current.col].row][predecessor[current.row][current.col].col] = '*'; 
        
     
        }
        // changing current to predecessor rows and cols
        current = predecessor[current.row][current.col]; 



      }


     for (int i=0; i < rows; i++) { // deallocating the explore array
      delete[] explore[i];
   }
   delete[] explore;  // deallocating the explore array

   for (int i=0; i < rows; i++) { // deallocating the predecessor array
      delete[] predecessor[i];
   }
   delete[] predecessor;  // deallocating the predecessor array


return 0; 

  



    
}
