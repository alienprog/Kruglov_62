/**
 * @file Maze.h
 * @brief Класс лабиринта.
 */

#pragma once
#include <vector>
#include "Cell.h"

 /**
  * @class Maze
  * @brief Двумерная матрица клеток, образующая лабиринт.
  *
  * Хранит размеры и сетку клеток, предоставляет методы доступа.
  */
class Maze {
private:
    int rows;                                ///< количество строк
    int cols;                                ///< количество столбцов
    std::vector<std::vector<Cell>> grid;    ///< матрица клеток

public:
    /**
     * @brief Конструктор по умолчанию (пустой лабиринт).
     */
    Maze();

    /**
     * @brief Конструктор с указанием размеров.
     * @param r количество строк
     * @param c количество столбцов
     */
    Maze(int r, int c);

    /**
     * @brief Проверяет, находятся ли координаты внутри лабиринта.
     * @param row строка
     * @param col столбец
     * @return true если внутри, false иначе
     */
    bool isValidCell(int row, int col) const;

    /**
     * @brief Сбрасывает состояние всех клеток (visited, distance, parent).
     */
    void reset();

    /**
     * @brief Возвращает ссылку на клетку (неконстантную).
     * @param row строка
     * @param col столбец
     * @return ссылка на клетку
     */
    Cell& getCell(int row, int col);

    /**
     * @brief Возвращает константную ссылку на клетку.
     * @param row строка
     * @param col столбец
     * @return константная ссылка на клетку
     */
    const Cell& getCell(int row, int col) const;

    /**
     * @brief Возвращает количество строк.
     * @return rows
     */
    int getRows() const;

    /**
     * @brief Возвращает количество столбцов.
     * @return cols
     */
    int getCols() const;
};