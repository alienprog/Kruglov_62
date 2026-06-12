/**
 * @file Cell.cpp
 * @brief Реализация класса Cell.
 */

#include "Cell.h"
 // Конструктор по умолчанию для инициализации клетки
Cell::Cell()
    : isWall(false), visited(false), distance(0),
    parent(nullptr), x(0), y(0) {
}
// Сбросить состояние клетки
void Cell::reset() {
    visited = false;
    distance = 0;
    parent = nullptr;
}