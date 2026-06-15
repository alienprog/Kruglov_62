/**
 * @file Functions.cpp
 * @brief Функции парсинга лабиринта и координат.
 */

#include "Header.h"
#include <sstream>
#include <limits>

 /**
  * @brief Парсит размеры лабиринта из содержимого файла.
  * @param content содержимое файла лабиринта
  * @param rows количество строк лабиринта
  * @param cols количество столбцов лабиринта
  * @param errors набор ошибок
  * @return true если размеры успешно считаны и корректны
  */
bool parseMazeSize(const std::string& content, int& rows, int& cols,
    std::set<Error>& errors) {
    std::istringstream stream(content);

    rows = 0;
    cols = 0;

    // Считать количество строк лабиринта.
    if (!(stream >> rows)) {
        errors.insert(Error(invalidFormatError));
        return false;
    }
    // Считать количество столбцов лабиринта.
    if (!(stream >> cols)) {
        errors.insert(Error(invalidFormatError));
        return false;
    }
    bool rangeOk = true;
    // Проверить допустимый диапазон количества строк.
    if (rows < MIN_MAZE_SIZE || rows > MAX_MAZE_SIZE) {
        errors.insert(Error(outOfRangeError, 0, 0, rows, MAX_MAZE_SIZE));
        rangeOk = false;
    }
    // Проверить допустимый диапазон количества столбцов.
    if (cols < MIN_MAZE_SIZE || cols > MAX_MAZE_SIZE) {
        errors.insert(Error(outOfRangeError, 0, 0, cols, MAX_MAZE_SIZE));
        rangeOk = false;
    }
    return rangeOk;
}

/**
 * @brief Парсит одну строку лабиринта.
 * @param line строка лабиринта
 * @param maze объект лабиринта
 * @param rowNumber номер строки лабиринта
 * @param cols ожидаемое количество столбцов
 * @param hasPassage флаг наличия хотя бы одной проходимой клетки
 * @param errors набор ошибок
 * @return true если строка успешно разобрана
 */
bool parseSingleMazeRow(const std::string& line, Maze& maze,
    int rowNumber, int cols, bool& hasPassage,
    std::set<Error>& errors) {
    std::string preparedLine = line;

    // Удалить символ '\r', если строка была прочитана из Windows-файла.
    if (!preparedLine.empty() && preparedLine.back() == '\r') {
        preparedLine.pop_back();
    }
    std::string cells;
    // Удалить пробелы и табуляцию из строки лабиринта.
    for (char ch : preparedLine) {
        if (ch != ' ' && ch != '\t') {
            cells += ch;
        }
    }
    // Проверить, совпадает ли фактическая длина строки с количеством столбцов.
    if ((int)cells.size() != cols) {
        errors.insert(Error(invalidFormatError, rowNumber + 1, 0,
            (int)cells.size(), cols));
        return false;
    }
    bool rowOk = true;
    // Проверить символы строки и заполнить клетки лабиринта.
    for (int col = 0; col < cols; ++col) {
        char ch = cells[col];

        if (ch != PASSAGE_CHAR && ch != WALL_CHAR) {
            errors.insert(Error(invalidCharError, rowNumber + 1, col + 1,
                0, 0, ch));
            rowOk = false;
        }
        else {
            Cell& cell = maze.getCell(rowNumber, col);
            cell.isWall = (ch == WALL_CHAR);
            cell.x = col;
            cell.y = rowNumber;

            if (ch == PASSAGE_CHAR) {
                hasPassage = true;
            }
        }
    }

    return rowOk;
}

/**
 * @brief Парсит все строки лабиринта.
 * @param stream поток с содержимым файла лабиринта
 * @param maze объект лабиринта
 * @param rows ожидаемое количество строк
 * @param cols ожидаемое количество столбцов
 * @param hasPassage флаг наличия хотя бы одной проходимой клетки
 * @param actualRows количество фактически прочитанных строк
 * @param errors набор ошибок
 */
void parseMazeGrid(std::istringstream& stream, Maze& maze,
    int rows, int cols, bool& hasPassage,
    int& actualRows, std::set<Error>& errors) {
    std::string line;
    actualRows = 0;

    // Читать лабиринт построчно и обрабатывать каждую строку отдельно.
    while (actualRows < rows && std::getline(stream, line)) {
        parseSingleMazeRow(line, maze, actualRows, cols, hasPassage, errors);
        ++actualRows;
    }
}

/**
 * @brief Парсит содержимое файла лабиринта и заполняет объект Maze.
 * @param content содержимое файла в виде строки
 * @param maze объект лабиринта, который будет заполнен
 * @param errors набор ошибок, найденных при парсинге
 */
void parseMazeContent(const std::string& content, Maze& maze,
    std::set<Error>& errors) {
    int rows = 0;
    int cols = 0;

    // Считать и проверить размеры лабиринта.
    if (!parseMazeSize(content, rows, cols, errors)) {
        return;
    }

    maze = Maze(rows, cols);

    std::istringstream stream(content);

    // Повторно считать размеры, чтобы поток перешёл к строкам лабиринта.
    stream >> rows;
    stream >> cols;

    // Пропустить остаток строки после размеров.
    std::string dummy;
    std::getline(stream, dummy);

    bool hasPassage = false;
    int actualRows = 0;

    // Прочитать и разобрать все строки лабиринта.
    parseMazeGrid(stream, maze, rows, cols, hasPassage, actualRows, errors);

    // Проверить, совпадает ли количество прочитанных строк с заявленным.
    if (actualRows != rows) {
        errors.insert(Error(invalidFormatError, 0, 0, actualRows, rows));
    }

    // Проверить, что в лабиринте есть хотя бы одна проходимая клетка.
    if (errors.empty() && !hasPassage) {
        errors.insert(Error(noPassageError));
    }
}

/**
 * @brief Считывает целое число из строки и проверяет его границы.
 * @param str строка с одним числом
 * @param val переменная, в которую будет записано число
 * @param min минимально допустимое значение
 * @param max максимально допустимое значение
 * @param errors набор ошибок
 * @return true если число корректно и находится в заданных границах
 */
bool readIntFromStringAndCheckBounds(const std::string& str, int& val,
    int min, int max, std::set<Error>& errors) {
    std::istringstream stream(str);

    int parsedValue = 0;

    // Проверить, что из строки можно считать целое число.
    if (!(stream >> parsedValue)) {
        errors.insert(Error(invalidFormatError));
        return false;
    }

    // Проверить, что после числа нет лишних символов.
    char extraChar = '\0';

    if (stream >> extraChar) {
        errors.insert(Error(invalidFormatError));
        return false;
    }

    // Сохранить число даже в случае выхода за границы.
    val = parsedValue;

    // Проверить, находится ли число в допустимом диапазоне.
    if (val < min || val > max) {
        errors.insert(Error(coordOutOfBoundsError, 0, 0, val, max));
        return false;
    }

    return true;
}

/**
 * @brief Разбирает одну строку координат.
 * @param line строка с двумя координатами
 * @param first первое число из строки
 * @param second второе число из строки
 * @param lineNumber номер строки координат
 * @param errors набор ошибок
 * @return true если первые два числа удалось получить и в строке нет лишних данных
 */
bool parseCoordsLine(const std::string& line, int& first, int& second,
    int lineNumber, std::set<Error>& errors) {
    std::istringstream stream(line);

    std::string firstText;
    std::string secondText;
    std::string extraText;

    // Прочитать две координаты как строки, чтобы отдельно проверить каждое число.
    if (!(stream >> firstText >> secondText)) {
        errors.insert(Error(invalidFormatError, lineNumber));
        return false;
    }

    bool firstParsed = readIntFromStringAndCheckBounds(firstText, first,
        (std::numeric_limits<int>::min)(),
        (std::numeric_limits<int>::max)(),
        errors);

    bool secondParsed = readIntFromStringAndCheckBounds(secondText, second,
        (std::numeric_limits<int>::min)(),
        (std::numeric_limits<int>::max)(),
        errors);

    bool hasExtraData = false;

    // Проверить, нет ли третьего числа или других лишних данных в строке.
    if (stream >> extraText) {
        errors.insert(Error(extraDataError, lineNumber));
        hasExtraData = true;
    }

    return firstParsed && secondParsed && !hasExtraData;
}

/**
 * @brief Парсит два целых числа из строки.
 * @param line строка для парсинга
 * @param lineNum номер строки
 * @param a первое число
 * @param b второе число
 * @param errors набор ошибок
 * @return true если первые два числа удалось получить
 */
bool parseTwoInts(const std::string& line, int lineNum, int& a, int& b,
    std::set<Error>& errors) {
    return parseCoordsLine(line, a, b, lineNum, errors);
}

/**
 * @brief Проверяет клетки начальной и конечной точки.
 * @param maze лабиринт
 * @param startRow строка начальной точки
 * @param startCol столбец начальной точки
 * @param endRow строка конечной точки
 * @param endCol столбец конечной точки
 * @param startInBounds true если начальная точка находится в границах лабиринта
 * @param endInBounds true если конечная точка находится в границах лабиринта
 * @param errors набор ошибок
 */
void checkPointCells(const Maze& maze, int startRow, int startCol,
    int endRow, int endCol, bool startInBounds, bool endInBounds,
    std::set<Error>& errors) {
    // Проверить, не является ли начальная точка стеной.
    if (startInBounds && maze.getCell(startRow, startCol).isWall) {
        errors.insert(Error(startIsWallError, startRow, startCol));
    }

    // Проверить, не является ли конечная точка стеной.
    if (endInBounds && maze.getCell(endRow, endCol).isWall) {
        errors.insert(Error(endIsWallError, endRow, endCol));
    }

    // Проверить, не совпадают ли начальная и конечная точки.
    if (startInBounds && endInBounds
        && startRow == endRow && startCol == endCol) {
        errors.insert(Error(pointsSameError));
    }
}

/**
 * @brief Читает две строки координат и проверяет лишние строки.
 * @param content содержимое файла координат
 * @param line1 строка с координатами начальной точки
 * @param line2 строка с координатами конечной точки
 * @param errors набор ошибок
 * @return true если две строки координат были прочитаны
 */
bool readCoordsLines(const std::string& content,
    std::string& line1, std::string& line2,
    std::set<Error>& errors) {
    std::istringstream stream(content);

    bool hasFirstLine = false;
    bool hasSecondLine = false;

    // Прочитать первую строку с координатами начальной точки.
    if (std::getline(stream, line1)) {
        hasFirstLine = true;

        if (!line1.empty() && line1.back() == '\r') {
            line1.pop_back();
        }
    }
    else {
        errors.insert(Error(invalidFormatError));
    }

    // Прочитать вторую строку с координатами конечной точки.
    if (std::getline(stream, line2)) {
        hasSecondLine = true;

        if (!line2.empty() && line2.back() == '\r') {
            line2.pop_back();
        }
    }
    else {
        errors.insert(Error(invalidFormatError));
    }

    // Проверить отсутствие лишних строк после двух строк координат.
    std::string line3;

    while (std::getline(stream, line3)) {
        if (!line3.empty() && line3.back() == '\r') {
            line3.pop_back();
        }

        std::istringstream check(line3);
        int tmp = 0;

        if (check >> tmp) {
            errors.insert(Error(extraDataError));
            break;
        }
    }

    return hasFirstLine && hasSecondLine;
}

/**
 * @brief Парсит содержимое файла координат и проверяет корректность точек.
 * @param content содержимое файла координат
 * @param maze лабиринт для проверки границ и стен
 * @param startRow строка начальной точки
 * @param startCol столбец начальной точки
 * @param endRow строка конечной точки
 * @param endCol столбец конечной точки
 * @param errors набор ошибок
 * @return true если координаты корректны
 */
bool parseCoordsContent(const std::string& content, const Maze& maze,
    int& startRow, int& startCol,
    int& endRow, int& endCol,
    std::set<Error>& errors) {
    std::string line1;
    std::string line2;

    readCoordsLines(content, line1, line2, errors);

    // Взять текущие значения выходных параметров как значения по умолчанию.
    int sr = startRow;
    int sc = startCol;
    int er = endRow;
    int ec = endCol;

    bool startParsed = false;
    bool endParsed = false;

    // Разобрать первую строку, даже если вторая строка отсутствует.
    if (!line1.empty()) {
        startParsed = parseCoordsLine(line1, sr, sc, 1, errors);
    }

    // Разобрать вторую строку, если она есть.
    if (!line2.empty()) {
        endParsed = parseCoordsLine(line2, er, ec, 2, errors);
    }

    // Сохранить распарсенные значения сразу, даже если дальше найдутся ошибки.
    startRow = sr;
    startCol = sc;
    endRow = er;
    endCol = ec;

    const int rows = maze.getRows();
    const int cols = maze.getCols();

    bool startRowInBounds = false;
    bool startColInBounds = false;
    bool endRowInBounds = false;
    bool endColInBounds = false;

    // Проверить границы начальной точки.
    if (startParsed) {
        startRowInBounds = readIntFromStringAndCheckBounds(std::to_string(sr),
            sr, 0, rows - 1, errors);

        startColInBounds = readIntFromStringAndCheckBounds(std::to_string(sc),
            sc, 0, cols - 1, errors);
    }

    // Проверить границы конечной точки.
    if (endParsed) {
        endRowInBounds = readIntFromStringAndCheckBounds(std::to_string(er),
            er, 0, rows - 1, errors);

        endColInBounds = readIntFromStringAndCheckBounds(std::to_string(ec),
            ec, 0, cols - 1, errors);
    }

    bool startInBounds = startRowInBounds && startColInBounds;
    bool endInBounds = endRowInBounds && endColInBounds;

    // Проверить, не являются ли точки стенами и не совпадают ли они.
    checkPointCells(maze, sr, sc, er, ec, startInBounds, endInBounds, errors);

    // Если ошибок нет, координаты корректны.
    return errors.empty();
}