#ifndef PRGASST02_MAZE_H
#define PRGASST02_MAZE_H

#include "position.h"
#include <vector>

using std::vector;

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

  // TODO: put any other fields you need here

};

#endif //PRGASST02_MAZE_H
