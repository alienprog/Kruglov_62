#include "Cell.h"
Cell::Cell()
    : isWall(false), visited(false), distance(0),
    parent(nullptr), x(0), y(0) {
}

void Cell::reset() {
    visited = false;
    distance = 0;
    parent = nullptr;
}