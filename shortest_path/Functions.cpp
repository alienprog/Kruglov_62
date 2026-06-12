/**
 * @file Functions.cpp
 * @brief Функции парсинга лабиринта и координат.
 */

#include "Header.h"
#include <sstream>

 /**
  * @brief Парсит содержимое файла лабиринта и заполняет объект Maze.
  * @param content содержимое файла в виде строки
  * @param maze объект лабиринта, который будет заполнен
  * @param errors набор ошибок (добавляются при обнаружении)
  */
void parseMazeContent(const std::string& content, Maze& maze, std::set<Error>& errors) {
    std::istringstream stream(content);
    // Прочитать количество строк и столбцов
    int rows = 0, cols = 0;
    if (!(stream >> rows)) {
        errors.insert(Error(invalidFormatError));
        return;
    }
    if (!(stream >> cols)) {
        errors.insert(Error(invalidFormatError));
        return;
    }
    // Проверить допустимость размеров
    bool rangeOk = true;
    if (rows < 1 || rows > 255) {
        errors.insert(Error(outOfRangeError, 0, 0, rows, 255));
        rangeOk = false;
    }
    if (cols < 1 || cols > 255) {
        errors.insert(Error(outOfRangeError, 0, 0, cols, 255));
        rangeOk = false;
    }
    if (!rangeOk) return;

    maze = Maze(rows, cols);
    // Пропустить остаток строки после размеров
    std::string dummy;
    std::getline(stream, dummy);

    bool hasPassage = false;
    int  actualRows = 0;
    // Прочитать лабиринт построчно
    std::string line;
    while (actualRows < rows && std::getline(stream, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        // Удалить пробелы и табуляцию из строки
        std::string cells;
        for (char ch : line) {
            if (ch != ' ' && ch != '\t') cells += ch;
        }
        // Проверка длины строки
        if ((int)cells.size() != cols) {
            errors.insert(Error(invalidFormatError, actualRows + 1, 0,
                (int)cells.size(), cols));
        }
        else {
            for (int c = 0; c < cols; ++c) {
                char ch = cells[c];
                if (ch != '.' && ch != '#') {
                    errors.insert(Error(invalidCharError, actualRows + 1, c + 1,
                        0, 0, ch));
                }
                else {
                    Cell& cell = maze.getCell(actualRows, c);
                    cell.isWall = (ch == '#');
                    cell.x = c;
                    cell.y = actualRows;
                    if (ch == '.') hasPassage = true;
                }
            }
        }
        ++actualRows;
    }
    // Проверка соответствия количества строк объявленному
    if (actualRows != rows) {
        errors.insert(Error(invalidFormatError, 0, 0, actualRows, rows));
    }

    if (errors.empty() && !hasPassage) {
        errors.insert(Error(noPassageError));
    }
}

/**
 * @brief Парсит два целых числа из строки.
 * @param line строка для парсинга
 * @param lineNum номер строки (для сообщения об ошибке)
 * @param a первый операнд (выходной)
 * @param b второй операнд (выходной)
 * @param errors набор ошибок
 * @return true если успешно, false если ошибка (ошибка добавляется в errors)
 */
bool parseTwoInts(const std::string& line, int lineNum, int& a, int& b, std::set<Error>& errors) {
    std::istringstream ss(line);
    if (!(ss >> a >> b)) {
        errors.insert(Error(invalidFormatError, lineNum));
        return false;
    }
    // Проверка наличия лишних данных после двух чисел
    int extra;
    if (ss >> extra) {
        errors.insert(Error(extraDataError, lineNum));
        return false;
    }
    return true;
}

/**
 * @brief Парсит содержимое файла координат и проверяет корректность точек.
 * @param content содержимое файла координат
 * @param maze лабиринт (для проверки границ и стен)
 * @param startRow строка начальной точки (выход)
 * @param startCol столбец начальной точки (выход)
 * @param endRow строка конечной точки (выход)
 * @param endCol столбец конечной точки (выход)
 * @param errors набор ошибок
 * @return true если успешно, false при ошибке
 */
bool parseCoordsContent(const std::string& content, const Maze& maze,
    int& startRow, int& startCol,
    int& endRow, int& endCol,
    std::set<Error>& errors) {
    std::istringstream stream(content);

    // Чтение двух строк с координатами
    std::string line1, line2;
    if (!std::getline(stream, line1)) {
        errors.insert(Error(invalidFormatError));
        return false;
    }
    if (!line1.empty() && line1.back() == '\r') line1.pop_back();

    if (!std::getline(stream, line2)) {
        errors.insert(Error(invalidFormatError));
        return false;
    }
    if (!line2.empty() && line2.back() == '\r') line2.pop_back();

    // Проверка отсутствия лишних строк после координат
    bool hasExtra = false;
    std::string line3;
    while (!hasExtra && std::getline(stream, line3)) {
        if (!line3.empty() && line3.back() == '\r') line3.pop_back();
        std::istringstream check(line3);
        int tmp;
        if (check >> tmp) hasExtra = true;
    }
    if (hasExtra) {
        errors.insert(Error(extraDataError));
        return false;
    }

    // Разбор координат
    int sr = 0, sc = 0, er = 0, ec = 0;
    if (!parseTwoInts(line1, 1, sr, sc, errors)) return false;
    if (!parseTwoInts(line2, 2, er, ec, errors)) return false;

    const int rows = maze.getRows();
    const int cols = maze.getCols();

    // Проверка выхода за границы
    if (sr < 0 || sr >= rows) errors.insert(Error(coordOutOfBoundsError, 0, 0, sr, rows));
    if (sc < 0 || sc >= cols) errors.insert(Error(coordOutOfBoundsError, 0, 0, sc, cols));
    if (er < 0 || er >= rows) errors.insert(Error(coordOutOfBoundsError, 0, 0, er, rows));
    if (ec < 0 || ec >= cols) errors.insert(Error(coordOutOfBoundsError, 0, 0, ec, cols));
    if (!errors.empty()) return false;

    // Проверка, что точки не являются стенами
    if (maze.getCell(sr, sc).isWall) errors.insert(Error(startIsWallError, sr, sc));
    if (maze.getCell(er, ec).isWall) errors.insert(Error(endIsWallError, er, ec));
    if (sr == er && sc == ec)        errors.insert(Error(pointsSameError));
    if (!errors.empty()) return false;

    // Сохранение координат
    startRow = sr; startCol = sc;
    endRow = er; endCol = ec;
    return true;
}