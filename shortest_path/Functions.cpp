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
    if (rows < MIN_MAZE_SIZE || rows > MAX_MAZE_SIZE) {
        errors.insert(Error(outOfRangeError, 0, 0, rows, MAX_MAZE_SIZE));
        rangeOk = false;
    }
    if (cols < MIN_MAZE_SIZE || cols > MAX_MAZE_SIZE) {
        errors.insert(Error(outOfRangeError, 0, 0, cols, MAX_MAZE_SIZE));
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
                if (ch != PASSAGE_CHAR && ch != WALL_CHAR) {
                    errors.insert(Error(invalidCharError, actualRows + 1, c + 1,
                        0, 0, ch));
                }
                else {
                    Cell& cell = maze.getCell(actualRows, c);
                    cell.isWall = (ch == WALL_CHAR);
                    cell.x = c;
                    cell.y = actualRows;
                    if (ch == PASSAGE_CHAR) hasPassage = true;
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

    std::string line1;
    std::string line2;
    std::string line3;

    bool hasFirstLine = false;
    bool hasSecondLine = false;

    // Читаем первую строку с координатами начальной точки.
    if (std::getline(stream, line1)) {
        hasFirstLine = true;

        if (!line1.empty() && line1.back() == '\r') {
            line1.pop_back();
        }
    }
    else {
        errors.insert(Error(invalidFormatError));
    }

    // Читаем вторую строку с координатами конечной точки.
    if (std::getline(stream, line2)) {
        hasSecondLine = true;

        if (!line2.empty() && line2.back() == '\r') {
            line2.pop_back();
        }
    }
    else {
        errors.insert(Error(invalidFormatError));
    }

    // Проверяем, нет ли лишних строк после двух строк с координатами.
    while (std::getline(stream, line3)) {
        if (!line3.empty() && line3.back() == '\r') {
            line3.pop_back();
        }

        std::istringstream check(line3);
        int tmp;

        if (check >> tmp) {
            errors.insert(Error(extraDataError));
            break;
        }
    }

    // Берём текущие значения выходных параметров как значения по умолчанию.
    int sr = startRow;
    int sc = startCol;
    int er = endRow;
    int ec = endCol;

    bool startParsed = false;
    bool endParsed = false;

    // Разбираем координаты начальной точки.
    if (hasFirstLine) {
        startParsed = parseTwoInts(line1, 1, sr, sc, errors);
    }

    // Разбираем координаты конечной точки.
    if (hasSecondLine) {
        endParsed = parseTwoInts(line2, 2, er, ec, errors);
    }

    // Сохраняем распарсенные значения сразу, даже если дальше найдутся ошибки.
    startRow = sr;
    startCol = sc;
    endRow = er;
    endCol = ec;

    const int rows = maze.getRows();
    const int cols = maze.getCols();

    bool startInBounds = startParsed;
    bool endInBounds = endParsed;

    // Проверяем границы начальной точки.
    if (startParsed) {
        if (sr < 0 || sr >= rows) {
            errors.insert(Error(coordOutOfBoundsError, 1, 1, sr, rows));
            startInBounds = false;
        }

        if (sc < 0 || sc >= cols) {
            errors.insert(Error(coordOutOfBoundsError, 1, 2, sc, cols));
            startInBounds = false;
        }
    }

    // Проверяем границы конечной точки.
    if (endParsed) {
        if (er < 0 || er >= rows) {
            errors.insert(Error(coordOutOfBoundsError, 2, 1, er, rows));
            endInBounds = false;
        }

        if (ec < 0 || ec >= cols) {
            errors.insert(Error(coordOutOfBoundsError, 2, 2, ec, cols));
            endInBounds = false;
        }
    }

    // Проверяем, не является ли начальная точка стеной.
    if (startInBounds && maze.getCell(sr, sc).isWall) {
        errors.insert(Error(startIsWallError, sr, sc));
    }

    // Проверяем, не является ли конечная точка стеной.
    if (endInBounds && maze.getCell(er, ec).isWall) {
        errors.insert(Error(endIsWallError, er, ec));
    }

    // Проверяем, не совпадают ли начальная и конечная точки.
    if (startParsed && endParsed && sr == er && sc == ec) {
        errors.insert(Error(pointsSameError));
    }

    // Если ошибок нет, координаты корректны.
    return errors.empty();
}


