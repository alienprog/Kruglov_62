/**
 * @file Maze.cpp
 * @brief Реализация класса Maze.
 */

#include "Maze.h"

Maze::Maze() : rows(0), cols(0) {}

// Конструктор с указанием размеров для инициализации сетки
Maze::Maze(int r, int c) : rows(r), cols(c), grid(r, std::vector<Cell>(c)) {
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j) {
            grid[i][j].x = j;
            grid[i][j].y = i;
        }
}
// Проверка, находятся ли координаты внутри лабиринта
bool Maze::isValidCell(int row, int col) const {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

// Сброс состояния всех клеток
void Maze::reset() {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            grid[i][j].reset();
}

// Возврат ссылки на клетку для изменения
Cell& Maze::getCell(int row, int col) { return grid[row][col]; }

// Возврат константной ссылки на клетку для чтения
const Cell& Maze::getCell(int row, int col) const { return grid[row][col]; }

// Возврат количества строк
int Maze::getRows() const { return rows; }

// Возврат количества столбцов
int Maze::getCols() const { return cols; }