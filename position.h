#ifndef PRGASST02_POSITION_H
#define PRGASST02_POSITION_H

#include <cstdlib>
#include <string>

using std::string;

/**
 * This class represents data about a single position in a maze.  It
 * includes data for both the maze itself as well as the task of finding
 * a path through the maze.
 */
class Position {
public:
  /**
   * Creates a new position representing the space at (x,y) in a maze.
   * This space is assumed to have no wall until we learn otherwise.
   */
  Position(int x, int y);

  /* return X/Y coordinate of current position */
  int getX();
  int getY();

  /* Mark current position as a wall */
  void setWall();
  /* Return true if current position is a wall, and false otherwise */
  bool isWall();
  /* Returns an unambiguous string representation of the coordinates */
  string to_string();

protected:
  /** The X coordinate of this position. */
  int xPos;
  /** The Y coordinate of this position. */
  int yPos;
  /** true if this position contains a wall; false if it does not. */
  bool wall;
};

#endif // PRGASST02_POSITION_H
