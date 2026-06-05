#include "Maze.h"

Maze::Maze()
    : rows(0),
    cols(0) {
}

Maze::Maze(int r, int c)
    : rows(r),
    cols(c),
    grid(r, std::vector<Cell>(c)) {
}

bool Maze::isValidCell(int row, int col) const {
    return false;
}

bool Maze::isPassable(int row, int col) const {
    return false;
}

void Maze::reset() {
}

Cell& Maze::getCell(int row, int col) {
    return grid[row][col];
}

const Cell& Maze::getCell(int row, int col) const {
    return grid[row][col];
}

int Maze::getRows() const {
    return rows;
}

int Maze::getCols() const {
    return cols;
}