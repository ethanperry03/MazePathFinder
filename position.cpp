#include "position.h"
#include <stdexcept>
#include <string>

using namespace std;

Position::Position(int x, int y) {
    this->xPos = x;
    this->yPos = y;
    // default value is false, since setWall() converts it to true
    this->wall = false;
}

int Position::getX()  {
    return this->xPos;
}

int Position::getY() {
    return this->yPos;
}

void Position::setWall()  {
    this->wall = true;
}

bool Position::isWall()  {
    return this->wall;
}

string Position::to_string()  {
    return std::to_string(this->xPos) + ',' + std::to_string(this->yPos);
}
