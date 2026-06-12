/**
 * @file PathFinder.cpp
 * @brief Реализация класса PathFinder.
 */

#include "PathFinder.h"
#include <queue>
#include <algorithm>

 // Конструктор сохраняет указатель на лабиринт и координаты старта/финиша.
PathFinder::PathFinder(Maze& m, int sr, int sc, int er, int ec)
    : maze(&m), startRow(sr), startCol(sc), endRow(er), endCol(ec) {
}

// Выполняет поиск кратчайшего пути с помощью BFS.
std::vector<Cell*> PathFinder::findPath() {
    // Сбросить состояние всех клеток перед новым поиском
    maze->reset();

    // Инициализация стартовой клетки
    Cell& startCell = maze->getCell(startRow, startCol);
    startCell.visited = true;   // пометить как посещённую
    startCell.distance = 0;     // расстояние от старта до старта = 0
    startCell.parent = nullptr; // у старта нет родителя

    // Очередь для BFS (хранит указатели на клетки)
    std::queue<Cell*> q;
    q.push(&startCell);          // поместить старт в очередь

    bool  found = false;         // флаг, найден ли финиш
    Cell* endCell = nullptr;     // указатель на клетку финиша (если будет найден)

    // Направления движения: вверх, вниз, влево, вправо
    const int dx[] = { 0,  0, -1, 1 };
    const int dy[] = { -1,  1,  0, 0 };

    // Основной цикл BFS
    while (!q.empty() && !found) {
        // Взять клетку из начала очереди и удалить её
        Cell* curr = q.front();
        q.pop();

        // Если текущая клетка — финиш, запомнить и выйти из цикла
        if (curr->x == endCol && curr->y == endRow) {
            found = true;
            endCell = curr;
        }
        else {
            // Проверить всех четырёх соседей
            for (int d = 0; d < 4 && !found; ++d) {
                int nx = curr->x + dx[d];   // координата столбца соседа
                int ny = curr->y + dy[d];   // координата строки соседа

                // Если соседняя клетка находится в пределах лабиринта
                if (maze->isValidCell(ny, nx)) {
                    Cell& neighbor = maze->getCell(ny, nx);
                    // Если сосед — проход и ещё не посещён
                    if (!neighbor.isWall && !neighbor.visited) {
                        neighbor.visited = true;                 // отметить как посещённый
                        neighbor.distance = curr->distance + 1; // обновить расстояние
                        neighbor.parent = curr;                 // запомнить родителя
                        q.push(&neighbor);                      // добавить в очередь
                    }
                }
            }
        }
    }

    // Если финиш не достигнут, вернуть пустой вектор
    if (!found) return std::vector<Cell*>();

    // Восстановление пути от финиша к старту
    std::vector<Cell*> result;
    Cell* curr = endCell;
    while (curr != nullptr) {
        result.push_back(curr);   // добавить текущую клетку в путь
        curr = curr->parent;      // перейти к родительской клетке
    }
    // Развернуть путь, чтобы он шёл от старта к финишу
    std::reverse(result.begin(), result.end());
    path = result;                // сохранить путь в поле класса (опционально)
    return result;               // вернуть путь
}