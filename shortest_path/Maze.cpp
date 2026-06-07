#include "Maze.h"

Maze::Maze() : rows(0), cols(0) {}

Maze::Maze(int r, int c) : rows(r), cols(c), grid(r, std::vector<Cell>(c)) {
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            grid[i][j].x = j;
            grid[i][j].y = i;
        }
    }
}

bool Maze::isValidCell(int row, int col) const {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

bool Maze::isPassable(int row, int col) const {
    return isValidCell(row, col) && !grid[row][col].isWall;
}

void Maze::reset() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j].reset();
        }
    }
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