#ifndef PRGASST02_MAZE_H
#define PRGASST02_MAZE_H

#include "position.h"
#include <vector>
#include <unordered_map>

using std::vector;
using namespace std;

class Maze {
public:
  /**
   * Creates a Maze of the specified size.  Initially, all spaces are
   * assumed to contain no walls. The upper-left corner is
   * at position (0,0), with Y increasing toward the bottom edge of the map.
   * This constructor should
   */
  Maze(int width, int height);

  /**
   * Cleans up the memory used by a Maze.
   */
  ~Maze();

  /**
   * Retrieves the width of the map.
   * @return The width of this map.
   */
  int getWidth();

  /**
   * Retrieves the height of the map.
   * @return The height of this map.
   */
  int getHeight();

  /**
   * Determines if a given position contains a wall.
   * @param x The X coordinate of the position.
   * @param y The Y coordinate of the position.
   * @return true if there is wall in that place; false if there is not.
   */
  bool isWall(int x, int y);

  /**
   * Sets the specified location to be a wall.  The upper-left corner is
   * at position (0,0), with Y increasing toward the bottom edge of the map.
   * @param x The X coordinate of the position.
   * @param y The Y coordinate of the position.
   */
  void setWall(int x, int y);

  /**
   * Solves this Maze using a breadth-first search.
   * @return The path of positions which give a correct answer to the
   *         maze.  It is the caller's responsibility to delete this
   *         object.  If no path exists, nullptr will be returned.
   */
  vector<Position*> solveBreadthFirst();

  /**
   * Solves this Maze using a depth-first search.
   * @return The path of positions which give a correct answer to the
   *         maze.  It is the caller's responsibility to delete this
   *         object.  If no path exists, nullptr will be returned.
   */
  vector<Position*> solveDepthFirst();

  /**
   * @brief Display the maze as a grid to the console
   *        Using '#' for walls and '.' for paths
   */
  void displayMap();

  /**
   * @brief Display all neighbors of a position to console
   * @param x The x-coordinate (column) of the position
   * @param y The y-coordinate (row) of the position
   */
  void displayNeighbors(int, int);

  /**
   * @brief Display path length and number of nodes visited statistics
   */
  void displayStats();

protected:
  /**
   * A utility method which creates and returns a vector of the valid neighbors
   * of a given position.  A neighbor is a horizontally or vertically adjacent
   * space which is within the bounds of the map.  For instance, consider the
   * space in the map below marked with an X:
   * <pre>
   *     ..#.
   *     .##X
   *     ....
   * </pre>
   * The X-marked space above has three neighbors: the one above, the one
   * below, and the one to the left.  The space to the right is out of bounds
   * and so would not be included in the returned list. The space to the left
   * also would not be included in the list because it is a wall
   *
   * @param position The position for which neighbors should be found.
   * @return A new list of pointers to this position's neighbors.  The caller
   *         assumes responsibility for deleting this list.
   */
  vector<Position*> getNeighbors(Position* position);

  /** A dynamically-allocated two-dimenstional array of pointers to Position
      objects representing the maze. */
  Position*** positions;

  /**
   * @brief Construct a path from start to destination using visited positions
   * @param visited An unordered map with position strings as keys and previous positions as values
   * @param dest Pointer to the destination Position
   * @return A vector of Position pointers representing the path from start to destination
   */
  vector<Position*> buildPath(unordered_map<string, Position*>&, Position*);

  /** The width and height of this maze. */
  int width;
  int height;
  /** The number of nodes visited during the search. */
  int nodesVisited;
  /** The length of the path found by the search. */
  int pathLength;

};

#endif //PRGASST02_MAZE_H
