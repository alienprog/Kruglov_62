/**
 * @file PathFinder.h
 * @brief Класс для поиска кратчайшего пути алгоритмом BFS.
 */

#pragma once
#include <vector>
#include "Maze.h"
#include "Cell.h"

 /**
  * @class PathFinder
  * @brief Находит кратчайший путь в лабиринте от старта до финиша.
  */
class PathFinder {
private:
    Maze* maze;                ///< указатель на лабиринт
    int startRow, startCol;    ///< координаты старта
    int endRow, endCol;        ///< координаты финиша
    std::vector<Cell*> path;   ///< вектор указателей на клетки пути

public:
    /**
     * @brief Конструктор.
     * @param m ссылка на лабиринт
     * @param sr строка старта
     * @param sc столбец старта
     * @param er строка финиша
     * @param ec столбец финиша
     */
    PathFinder(Maze& m, int sr, int sc, int er, int ec);

    /**
     * @brief Выполняет поиск кратчайшего пути с помощью BFS.
     * @return вектор указателей на клетки в порядке от старта к финишу,
     *         или пустой вектор, если путь не найден.
     */
    std::vector<Cell*> findPath();
};