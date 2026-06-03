#pragma once

class Cell {
public:
    bool isWall;
    bool visited;
    int distance;
    Cell* parent;
    int x;
    int y;

    Cell();

    void reset();
};