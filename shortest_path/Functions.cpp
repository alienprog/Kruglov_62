#include "Header.h"
#include <sstream>

void parseMazeContent(const std::string& content, Maze& maze, std::set<Error>& errors) {
    std::istringstream stream(content);

    int rows = 0;
    int cols = 0;

    if (!(stream >> rows)) {
        errors.insert(Error(invalidFormatError));
        return;
    }

    if (!(stream >> cols)) {
        errors.insert(Error(invalidFormatError));
        return;
    }

    bool rangeOk = true;

    if (rows < 1 || rows > 255) {
        errors.insert(Error(outOfRangeError, 0, 0, rows, 255));
        rangeOk = false;
    }

    if (cols < 1 || cols > 255) {
        errors.insert(Error(outOfRangeError, 0, 0, cols, 255));
        rangeOk = false;
    }

    if (!rangeOk) {
        return;
    }

    maze = Maze(rows, cols);

    std::string dummy;
    std::getline(stream, dummy);

    bool hasPassage = false;
    int actualRows = 0;

    std::string line;
    while (actualRows < rows && std::getline(stream, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        std::string cells;
        for (char ch : line) {
            if (ch != ' ' && ch != '\t') {
                cells += ch;
            }
        }

        if ((int)cells.size() != cols) {
            errors.insert(Error(invalidFormatError, actualRows + 1, 0, (int)cells.size(), cols));
        }
        else {
            for (int col = 0; col < cols; ++col) {
                char ch = cells[col];

                if (ch != '.' && ch != '#') {
                    errors.insert(Error(invalidCharError, actualRows + 1, col + 1, 0, 0, ch));
                }
                else {
                    Cell& cell = maze.getCell(actualRows, col);
                    cell.isWall = (ch == '#');
                    cell.x = col;
                    cell.y = actualRows;

                    if (ch == '.') {
                        hasPassage = true;
                    }
                }
            }
        }

        ++actualRows;
    }

    if (actualRows != rows) {
        errors.insert(Error(invalidFormatError, 0, 0, actualRows, rows));
    }

    if (errors.empty() && !hasPassage) {
        errors.insert(Error(noPassageError));
    }
}

bool parseTwoInts(const std::string& line, int lineNum, int& a, int& b, std::set<Error>& errors) {
    std::istringstream ss(line);

    if (!(ss >> a >> b)) {
        errors.insert(Error(invalidFormatError, lineNum));
        return false;
    }

    int extra = 0;
    if (ss >> extra) {
        errors.insert(Error(extraDataError, lineNum));
        return false;
    }

    return true;
}

bool parseCoordsContent(const std::string& content, const Maze& maze,
    int& startRow, int& startCol,
    int& endRow, int& endCol,
    std::set<Error>& errors) {
    std::istringstream stream(content);

    std::string line1;
    std::string line2;

    if (!std::getline(stream, line1)) {
        errors.insert(Error(invalidFormatError));
        return false;
    }

    if (!line1.empty() && line1.back() == '\r') {
        line1.pop_back();
    }

    if (!std::getline(stream, line2)) {
        errors.insert(Error(invalidFormatError));
        return false;
    }

    if (!line2.empty() && line2.back() == '\r') {
        line2.pop_back();
    }

    bool hasExtra = false;
    std::string line3;

    while (!hasExtra && std::getline(stream, line3)) {
        if (!line3.empty() && line3.back() == '\r') {
            line3.pop_back();
        }

        std::istringstream check(line3);
        int tmp = 0;

        if (check >> tmp) {
            hasExtra = true;
        }
    }

    if (hasExtra) {
        errors.insert(Error(extraDataError));
        return false;
    }

    int sr = 0;
    int sc = 0;
    int er = 0;
    int ec = 0;

    if (!parseTwoInts(line1, 1, sr, sc, errors)) {
        return false;
    }

    if (!parseTwoInts(line2, 2, er, ec, errors)) {
        return false;
    }

    startRow = sr;
    startCol = sc;
    endRow = er;
    endCol = ec;

    return true;
}