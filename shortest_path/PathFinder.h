#pragma once
#include <vector>
#include "Maze.h"
#include "Cell.h"

class PathFinder {
private:
    Maze* maze;
    int startRow, startCol;
    int endRow, endCol;
    std::vector<Cell*> path;

public:
    PathFinder(Maze& m, int sr, int sc, int er, int ec);
    std::vector<Cell*> findPath();
};