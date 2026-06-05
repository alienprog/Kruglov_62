#include "PathFinder.h"
PathFinder::PathFinder(Maze& m, int sr, int sc, int er, int ec)
    : maze(&m),
    startRow(sr),
    startCol(sc),
    endRow(er),
    endCol(ec) {
}

std::vector<Cell*> PathFinder::findPath() {
    return std::vector<Cell*>();
}