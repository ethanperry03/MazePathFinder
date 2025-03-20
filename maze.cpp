#include <stdexcept>
#include <iostream>

/* STL libraries needed */
#include <stack>
#include <queue>
#include <unordered_map>
#include <vector>

/* library for reverse function */
#include <algorithm>
/* there is a function called "reverse" in this library that can reverse the elements of a vector
 * call it as follows:
 * reverse(v.begin(), v.end()); // this reverses the order of the elements in vector v
 */

#include "maze.h"
#include "myDictionary.h"

using namespace std;

Maze::Maze(int width, int height) {
    this->width = width;
    this->height = height;
    this->nodesVisited = 0;
    this->pathLength = 0;

    // Allocate memory for the 2D grid
    positions = new Position**[height]; // Rows (y)
    for (int y = 0; y < height; y++) {
        positions[y] = new Position*[width]; // Columns (x)
        for (int x = 0; x < width; x++) {
            positions[y][x] = new Position(x, y); // Create Position object
        }
    }
}

Maze::~Maze() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            delete positions[y][x]; // Delete each Position object
        }
        delete[] positions[y]; // Delete each row
    }
    delete[] positions; // Delete the array of rows
}

int Maze::getWidth() {
    return this->width;
}

int Maze::getHeight() {
    return this->height;
}

bool Maze::isWall(int x, int y) {
    return positions[y][x]->isWall();
}

void Maze::setWall(int x, int y) {
    positions[y][x]->setWall();
}

vector<Position*> Maze::solveBreadthFirst() {
  // declare unordered map to hash visited nodes
  MyDictionary visited;
  // queue of nodes to be visited
  queue<Position*> toBeVisited;
  // vector storing the path to be taken
  vector<Position*> path;

  //  mark starting node (0,0) as visited in the dict and make value itself
  visited.insert(positions[0][0]->to_string(), positions[0][0]);

  //  add start to the queue of to be visited
  toBeVisited.push(positions[0][0]);

  // declare the current node Position variable
  Position* curr;
  // store the destination position
  Position* dest = positions[this->height-1][this->width-1];

  // vector of neighbors of curr
  vector<Position*> neighbors;

  // string storing the to_string of position
  string key;

  //  while queue is not empty
  while(!toBeVisited.empty()) {
      //curr = queue.enqueue
      curr = toBeVisited.front();
      toBeVisited.pop();
      // increase number of nodes visited
      this->nodesVisited++;
      // if curr == destination (w, h)
      if(curr->to_string() == dest->to_string()) {
          // reverse built list of prev pointers
          path = buildPath(visited, dest);
          // return that path
          return path;
      }
      else {
          // get all of the neighbors of curr
          neighbors = getNeighbors(curr);
          for(Position* neighbor: neighbors) {
              key = neighbor->to_string();
              // if neighbor has not been visited before
              if(visited.isUnique(key)) {
                  // insert neighbor into dict and make curr as it's previous
                  visited.insert(key, curr);
                  // add the neighbor to the queue
                  toBeVisited.push(neighbor);
              }
          }
      }
  }
  // return empty vector if no path is found
  return vector<Position*>();
}

vector<Position*> Maze::solveDepthFirst() {
    // declare unordered map to hash visited nodes
    MyDictionary visited;
    // queue of nodes to be visited
    stack<Position*> toBeVisited;
    // vector storing the path to be taken
    vector<Position*> path;

    //  mark starting node (0,0) as visited in the dict and make value itself
    visited.insert(positions[0][0]->to_string(), positions[0][0]);

    //  add start to the queue of to be visited
    toBeVisited.push(positions[0][0]);

    // declare the current node Position variable
    Position* curr;
    // store the destination position
    Position* dest = positions[this->height-1][this->width-1];

    // vector of neighbors of curr
    vector<Position*> neighbors;

    // string storing the to_string of position
    string key;

    //  while queue is not empty
    while(!toBeVisited.empty()) {
        //curr = queue.enqueue
        curr = toBeVisited.top();
        toBeVisited.pop();
        // increase number of nodes visited
        this->nodesVisited++;
        // if curr == destination (w, h)
        if(curr->to_string() == dest->to_string()) {
            // reverse built list of prev pointers
            path = buildPath(visited, dest);
            // return that path
            return path;
        }
        else {
            // get all of the neighbors of curr
            neighbors = getNeighbors(curr);
            for(Position* neighbor: neighbors) {
                key = neighbor->to_string();
                // if neighbor has not been visited before
                if(visited.isUnique(key)) {
                    // insert neighbor into dict and make curr as it's previous
                    visited.insert(key, curr);
                    // add the neighbor to the queue
                    toBeVisited.push(neighbor);
                }
            }
        }
    }
    // return empty vector if no path is found
    return vector<Position*>();
}

vector<Position*> Maze::buildPath(MyDictionary& visited, Position* dest) {
    vector<Position*> path;
    Position* curr = dest;

    while(curr != visited[curr->to_string()]){
        // push the current position onto the vector
        path.push_back(curr);
        // update curr to point to the previous position from the dict
        curr = visited[curr->to_string()];
        // increment path length
        this->pathLength++;
    }
    path.push_back(curr);

    // flip the path to go from start to end
    reverse(path.begin(), path.end());
    return path;
}

vector<Position*> Maze::getNeighbors(Position* position) {
    vector<Position*> neighbors;
    int x = position->getX();
    int y = position->getY();

    // if you are not on the border and neighbor is not a wall

    // top
    if(y > 0 && !positions[y-1][x]->isWall()){
        neighbors.push_back(positions[y-1][x]);
    }
    // left
    if(x > 0 && !positions[y][x-1]->isWall()) {
        neighbors.push_back(positions[y][x - 1]);
    }
    // right
    if(x < this->width-1 && !positions[y][x+1]->isWall()){
        neighbors.push_back(positions[y][x+1]);
    }
    // down
    if(y < this->height-1 && !positions[y+1][x]->isWall()){
        neighbors.push_back(positions[y+1][x]);
    }
    return neighbors;
}

void Maze::displayNeighbors(int x, int y) {
    vector<Position*> neighbors = getNeighbors(positions[y][x]);
    for(Position* n: neighbors) {
        cout << "(" << n->getX() << ", " << n->getY() << ") - " << n->isWall() << endl;
    }
}

void Maze::displayMap() {
    for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            if (positions[i][j]->isWall()) {
                cout << "#";
            } else {
                cout << ".";
            }
        }
        cout << endl;
    }
}

void Maze::displayStats() {
    cout << "Path Length: " << this->pathLength << endl;
    cout << "# of Nodes Visited: " << this->nodesVisited << endl;
}
