#include <iostream>
#include <string>
#include <utility>

#include "maze.h"
#include "mazeUtils.h"

using namespace std;

string inputSearchAlg(string& input) {
    cin.get();
    while(input != "BFS" && input != "DFS") {
        cout << "Invalid input: try 'BFS' or 'DFS': ";
        getline(cin, input);
    }

    return input;
}

int main() {
  cout << "Welcome to The A-Maze-ing Race." << endl;
  string file;
  cout << "where is your maze file? ";
  cin >> file;
//    string file = "example5.map";
  // TODO: remove the file extension line in the mazeUtil
  Maze* map = loadMap(file);

  string search;
  cout << "Which search algorithm to use (BFS or DFS)? ";
  cin >> search;
  search = inputSearchAlg(search);

//  string outfile;
//  cout << "What is the name of the output file?";
//  cin >> outfile;

  cout << "Loading " << file << "..." << endl;
  map->displayMap();

  vector <Position*> solution;
  if(search == "BFS") {
      cout << endl << "Breadth First Searching..." << endl;
      solution = map->solveBreadthFirst();
  }
  else if (search == "DFS") {
      cout << endl << "Depth First Searching..." << endl;
      solution = map->solveDepthFirst();
  }
  else {
      cout << "Invalid search input" << endl;
  }

  cout << renderAnswer(map, solution) << endl;
  map->displayStats();


  // TODO: 1. write code to read in the map and handle potential errors 
  //       2. display the map to the terminal 
  //       3. call appropriate functions to solve the maze 
  //       4. display the solution path to the terminal 
  //       5. write the solution to the output file.
  //       4. output the path length and # of visited nodes

  // TODO: test a bit more, add stats to bottom output, fix input loop with new line, format output more
  return 0;
}
