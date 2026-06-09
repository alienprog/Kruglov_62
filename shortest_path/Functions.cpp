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

        if ((int)line.size() != cols) {
            errors.insert(Error(invalidFormatError, actualRows + 1, 0, (int)line.size(), cols));
        }
        else {
            for (int col = 0; col < cols; ++col) {
                char ch = line[col];

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
    return false;
}

bool parseCoordsContent(const std::string& content, const Maze& maze,
    int& startRow, int& startCol,
    int& endRow, int& endCol,
    std::set<Error>& errors) {
    return false;
}