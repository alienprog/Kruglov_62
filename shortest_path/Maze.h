#pragma once
#include <vector>
#include "Cell.h"

class Maze {
private:
    int rows;
    int cols;
    std::vector<std::vector<Cell>> grid;

public:
    Maze();
    Maze(int r, int c);

    bool isValidCell(int row, int col) const;
    bool isPassable(int row, int col) const;

    void reset();

    Cell& getCell(int row, int col);
    const Cell& getCell(int row, int col) const;

    int getRows() const;
    int getCols() const;
};