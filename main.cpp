#include <iostream>
#include <string>
#include <utility>

#include "maze.h"
#include "mazeUtils.h"

using namespace std;

/**
 * @brief Prompts the user for a search algorithm and validates the input
 * @param input The search algorithm input from the user
 * @return The validated search algorithm (either "BFS" or "DFS")
 */
string inputSearchAlg(string& input) {
    cin.get();
    while(input != "BFS" && input != "DFS") {
        cout << "Invalid input: try 'BFS' or 'DFS': ";
        getline(cin, input);
    }
    return input;
}

int main() {
  // const output string
  string BAR = "\n-----------------------------------------------------\n";

  cout << endl << "---------- Welcome to The A-Maze-ing Race! ----------" <<  endl << endl;
  string file;
  cout << "Write path to your maze file:";
  cin >> file;

  // load the input file
  Maze* map = loadMap(file);
  cout << BAR << endl << "Loading " << file << "..." << endl << BAR << endl;

  // display for user search method input
  string search;
  cout << "Choose a search algorithm:" << endl;
  cout << "Breadth First Search ---- (BFS)" << endl;
  cout << "Depth First Search ------ (DFS)" << endl;
  cout << ">";
  cin >> search;
  search = inputSearchAlg(search);

  // get output file from user
  string outfile;
  cout << BAR <<  endl << "What is the name of the output file?";
  cin >> outfile;

  // display the input map
  cout << BAR << endl << "Input map:" << endl;
  map->displayMap();
  cout << BAR;

  // perform the search alg
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

  // render the answer and get the solutions string for display
  string outputMaze = renderAnswer(map, solution);

  // output solution map
  cout << outputMaze;
  cout << endl << "----------------------" << endl;
  map->displayStats();
  cout << "----------------------" << endl;

  // output to file
  writeOutputToFile(outfile, outputMaze);
  cout << "Writen to " << outfile << BAR;

  return 0;
}
