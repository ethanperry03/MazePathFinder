#include "maze.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

Maze* loadMap(string filename) {
  ifstream file(filename.c_str());
  if (file.fail()) {
    throw runtime_error("Could not open file: " + filename);
  }
  int width;
  int height;
  file >> width;
  file >> height;
  if (file.fail()) {
    throw runtime_error("Error loading dimensions of map: " + filename);
  }
  Maze* maze = new Maze(width, height);
  try {
    string line;
    for (int i = 0; i < height; i++) {
      file >> line;
      if (file.fail() || line.length() != width) {
        throw runtime_error("Error reading map");
      }
      for (int j = 0; j < width; j++) {
        if (line[j] == '.') {
          // Then this is an open space, which is the default.
        } else if (line[j] == '#') {
          // Then this is a wall.
          maze->setWall(j, i);
        } else {
          string msg = "Unrecognized character in map: ";
          throw runtime_error(msg + line[j]);
        }
      }
    }
  } catch (std::exception &e) {
    delete maze;
    throw e;
  }
  return maze;
}

string renderAnswer(Maze* maze, vector<Position*> solution) {
  stringstream file;
  char* output = new char[maze->getWidth() * maze->getHeight()];
  try {
    for (int y = 0; y < maze->getHeight(); y++) {
      for (int x = 0; x < maze->getWidth(); x++) {
        int idx = x + y * maze->getWidth();
        if (maze->isWall(x, y)) {
          output[idx] = '#';
        } else {
          output[idx] = '.';
        }
      }
    }
    for (int i = 0; i < solution.size(); i++) {
      Position *pos = solution[i];
      output[pos->getX() + pos->getY() * maze->getWidth()] = '@';
    }
    for (int y = 0; y < maze->getHeight(); y++) {
      for (int x = 0; x < maze->getWidth(); x++) {
        int idx = x + y * maze->getWidth();
        file << output[idx];
      }
      file << endl;
    }
    delete[] output;
    return file.str();
  } catch (std::exception &e) {
    delete[] output;
    throw e;
  }
}
