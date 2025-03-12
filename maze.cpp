#include <stdexcept>
#include <iostream>

/* STL libraries needed */
#include <stack>
#include <queue>
#include <vector>

/* library for reverse function */
#include <algorithm>
/* there is a function called "reverse" in this library that can reverse the elements of a vector
 * call it as follows:
 * reverse(v.begin(), v.end()); // this reverses the order of the elements in vector v
 */

#include "maze.h"
//#include "myDictionary.h"

using namespace std;

Maze::Maze(int width, int height) {
    this->width = width;
    this->height = height;

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
  /* you will need an unordered_map to store the previous of each position */
  /* the keys for this map are the to_string of a position object
   * the associated value should be a pointer to the Position from which
   * you saw the key
   */
  throw runtime_error("Not yet implemented: Maze::solveBreadthFirst");
}

vector<Position*> Maze::solveDepthFirst() {
  /* you will need an unordered_map to store the previous of each position */
  /* the keys for this map are the to_string of a position object
   * the associated value should be a pointer to the Position from which
   * you saw the key
   */
  throw runtime_error("Not yet implemented: Maze::solveDepthFirst");
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
            cout << "(" << j << ", " << i << ") ";
            if (positions[i][j]->isWall()) {
                cout << "#";
            } else {
                cout << ".";
            }
            cout << endl;
        }
        cout << endl;
    }
}
