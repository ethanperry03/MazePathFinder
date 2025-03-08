/* This is a bunch of tests for your maze lab.
   It tests whether your Maze class allows mazes to
   be loaded properly by the loadMap function, and
   it verifies that all the mazes are (mostly) correctly
   solved by your program.
   IMPORTANT: these tests are not so extensive as to test
              everything about your program. It is possible
              for a program to pass all the tests, but still
              contain bugs, so make sure you also test your
              program yourself carefully.
*/

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include "maze.h"
#include "mazeUtils.h"

using namespace std;

#include <cmath>
#include <sstream>

#define INIT(s) good=0,bad=0;testNum++; cout << "Starting Test " << s << "." << endl;
#define CHECK_EQUAL(a,b) if (a==b) good++; else { bad++; cout << "  *** Test " << good+bad << " failed." << endl; }
#define CHECK(b) if (b) good++; else { bad++; cout << "  *** Test " << good+bad << " failed." << endl; }
#define CHECK_THROW(c,a) try {c; bad++; cout << "  *** Test " << good+bad << " failed." << endl;} catch (exception& e) {good++;}
#define PRINT_RESULT(s) cout << "  " << s << ": " << good << "/" << good+bad << " passed." << endl; if (bad == 0) allClear++; else cout << " *** " << bad << " test failed." << endl;

int testNum=0,allClear=0;
int good=0, bad=0;

/**
 * Verifies that two positions are adjacent.
 */
void checkAdjacent(Position *p1, Position *p2) {
    int dx = abs(p1->getX() - p2->getX());
    int dy = abs(p1->getY() - p2->getY());
    if (dx + dy != 1) {
        stringstream ss;
        ss << "Positions are not adjacent (" << p1->getX() << "," << p1->getY()
           << ") vs. (" << p2->getX() << "," << p2->getY() << ")";
        CHECK_EQUAL("Positions are adjacent", ss.str());
    }
}

/**
 * Verifies the provided answer under the assumption that the maze has at
 * least one answer.
 */
void validateAnswer(Maze *maze, vector<Position *> answer) {
    CHECK(!answer.empty());
    if (answer.empty()) {
        return;
    }
    for (int i = 0; i < answer.size() - 1; i++) {
        checkAdjacent(answer[i], answer[i+1]);
    }
    for (int i = 0; i < answer.size(); i++) {
        Position *p = answer[i];
        CHECK_EQUAL(false, maze->isWall(p->getX(), p->getY()));
    }
    Position *start = answer[0];
    CHECK_EQUAL(0, start->getX());
    CHECK_EQUAL(0, start->getY());
    Position *end = answer[answer.size() - 1];
    CHECK_EQUAL(maze->getWidth() - 1, end->getX());
    CHECK_EQUAL(maze->getHeight() - 1, end->getY());
}

void loads_properly() {
    // This test verifies that the Maze implementation loads properly.
    // The load_map function does the real work, but it's possible that the
    // Maze code didn't store the information correctly.
    INIT("loads_properly");
    Maze *maze = loadMap("example1.map");
    CHECK_EQUAL(5, maze->getWidth());
    CHECK_EQUAL(3, maze->getHeight());
    if (maze->getWidth() != 5 || maze->getHeight() != 3) {
        return;
    }
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 5; x++) {
            bool shouldBeWall = ((x == 1 && y == 0) || (x == 1 && y == 1) ||
                                 (x == 3 && y == 0) || (x == 3 && y == 2));
            CHECK_EQUAL(shouldBeWall, maze->isWall(x, y));
        }
    }
    delete maze;
    PRINT_RESULT("loads_properly");
}

void testMapPossible(string name, int breadthAnswerSize) {
    INIT(name);
    Maze *maze = loadMap(name + ".map");
    vector<Position *> answer = maze->solveBreadthFirst();
    if (!answer.empty()) {
        validateAnswer(maze, answer);
        CHECK_EQUAL(breadthAnswerSize, answer.size());
    } else {
        CHECK_EQUAL("solution", "no solution provided");
    }
    delete maze;

    maze = loadMap(name + ".map");
    answer = maze->solveDepthFirst();
    if (!answer.empty()) {
        validateAnswer(maze, answer);
    } else {
        CHECK_EQUAL("solution", "no solution provided");
    }
    delete maze;
    PRINT_RESULT(name);
}

void testMapImpossible(string name) {
    INIT(name);
    Maze *maze = loadMap(name + ".map");
    vector<Position *> answer = maze->solveBreadthFirst();
    CHECK(answer.empty());
    delete maze;

    maze = loadMap(name + ".map");
    answer = maze->solveDepthFirst();
    CHECK(answer.empty());
    delete maze;
    PRINT_RESULT(name);
}

void easyPossibleIn3() { testMapPossible("easy", 3); }

void example1PossibleIn9() { testMapPossible("example1", 9); }

void example2PossibleIn14() { testMapPossible("example2", 14); }

void example3PossibleIn11() { testMapPossible("example3", 11); }

void example4PossibleIn15() { testMapPossible("example4", 15); }

void example5PossibleIn17() { testMapPossible("example5", 17); }

void impossible1Impossible() { testMapImpossible("impossible1"); }

void impossible2Impossible() { testMapImpossible("impossible2"); }

void impossible3Impossible() { testMapImpossible("impossible3"); }

void cyclePossibleIn9() { testMapPossible("cycle", 9); }

void big1PossibleIn175() { testMapPossible("big1", 175); }

void big2PossibleIn439() { testMapPossible("big2", 439); }

void big3PossibleIn1056() { testMapPossible("big3", 1056); }

void impossible4Impossible() { testMapImpossible("impossible4"); }

void depthCheck1PossibleIn8() { testMapPossible("depthCheck1", 8); }

void depthCheck2PossibleIn8() { testMapPossible("depthCheck2", 8); }

void actuallyDepthFirst() {
    // The above tests establish (with high confidence) that the Maze is
    // using breadth-first search when we ask it to (because, on some of these
    // maps, the length of the depth-first search is longer than the shortest
    // path for any consistent ordering of node explorations).  But we don't
    // have a good way of making sure that the Maze is performing a
    // depth-first search.  Here, we'll accomplish that by creating two
    // different mazes; the first coincides with the shortest path if we
    // consider going right first and the second coincides if we go down first.
    // If the Maze class picks a consistent ordering, then at least one of
    // these mazes should yield a depth-first traversal which does not
    // match the breadth-first traversal.
    INIT("actuallyDepthFirst");
    Maze *depth1 = loadMap("depthCheck1.map");
    vector<Position *> answer1 = depth1->solveDepthFirst();
    if (answer1.empty()) {
        delete depth1;
        CHECK_EQUAL("depthCheck1.map is solvable", "no solution");
        return;
    }
    Maze *depth2 = loadMap("depthCheck2.map");
    vector<Position *> answer2 = depth2->solveDepthFirst();
    delete depth1;
    delete depth2;
    if (answer1.empty()) {
        CHECK_EQUAL("depthCheck2.map is solvable", "no solution");
        return;
    }
    CHECK(answer1.size() > 8 || answer2.size() > 8);
    PRINT_RESULT("actuallyDepthFirst");
}

int main() {
    loads_properly();
    easyPossibleIn3();
    example1PossibleIn9();
    example2PossibleIn14();
    example3PossibleIn11();
    example4PossibleIn15();
    example5PossibleIn17();
    impossible1Impossible();
    impossible2Impossible();
    impossible3Impossible();
    cyclePossibleIn9();
    big1PossibleIn175();
    big2PossibleIn439();
    big3PossibleIn1056();
    impossible4Impossible();
    depthCheck1PossibleIn8();
    depthCheck2PossibleIn8();
    actuallyDepthFirst();

    cout << "***** SUMMARY *****" << endl;
    cout << allClear << " / " << testNum << " tests passed." << endl;

    return 0;
}
