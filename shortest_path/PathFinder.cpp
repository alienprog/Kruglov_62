#include "PathFinder.h"
#include <queue>
#include <algorithm>

PathFinder::PathFinder(Maze& m, int sr, int sc, int er, int ec): maze(&m), startRow(sr), startCol(sc), endRow(er), endCol(ec) {}

std::vector<Cell*> PathFinder::findPath() {
    maze->reset();

    Cell& startCell = maze->getCell(startRow, startCol);
    startCell.visited = true;
    startCell.distance = 0;
    startCell.parent = nullptr;

    std::queue<Cell*> q;
    q.push(&startCell);

    bool found = false;
    Cell* endCell = nullptr;

    const int dx[] = { 0, 0, -1, 1 };
    const int dy[] = { -1, 1, 0, 0 };

    while (!q.empty() && !found) {
        Cell* current = q.front();
        q.pop();

        if (current->x == endCol && current->y == endRow) {
            found = true;
            endCell = current;
        }
        else {
            for (int direction = 0; direction < 4 && !found; ++direction) {
                int nextCol = current->x + dx[direction];
                int nextRow = current->y + dy[direction];

                if (maze->isValidCell(nextRow, nextCol)) {
                    Cell& neighbor = maze->getCell(nextRow, nextCol);

                    if (!neighbor.isWall && !neighbor.visited) {
                        neighbor.visited = true;
                        neighbor.distance = current->distance + 1;
                        neighbor.parent = current;
                        q.push(&neighbor);
                    }
                }
            }
        }
    }

    if (!found) {
        return std::vector<Cell*>();
    }

    std::vector<Cell*> result;
    Cell* current = endCell;

    while (current != nullptr) {
        result.push_back(current);
        current = current->parent;
    }

    std::reverse(result.begin(), result.end());

    path = result;
    return result;
}