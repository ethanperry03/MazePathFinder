#include <iostream>
#include <string>
#include <utility>

#include "maze.h"
#include "mazeUtils.h"

using namespace std;

int main() {
//  cout << "Welcome to The A-Maze-ing Race." << endl;
//  string map;
//  cout << "where is your maze file? ";
//  cin >> map;
//
//  string search;
//  cout << "Which search algorithm to use (BFS or DFS)? ";
//  cin >> search;
//
//  string outfile;
//  cout << "What is the name of the output file?";
//  cin >> outfile;

    // TODO: implement CTOR and DTOR, then test this code
    Maze* map = loadMap("../maps/example1.map");
    map->displayMap();

  
  // TODO: 1. write code to read in the map and handle potential errors 
  //       2. display the map to the terminal 
  //       3. call appropriate functions to solve the maze 
  //       4. display the solution path to the terminal 
  //       5. write the solution to the output file.
  //       4. output the path length and # of visited nodes 
  return 0;
}
