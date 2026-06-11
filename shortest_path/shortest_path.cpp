#include "Header.h"
#include "PathFinder.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>

void readMazeFile(const std::string& filename, std::string& content, std::set<Error>& errors) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        errors.insert(Error(fileOpenError));
        return;
    }

    file.seekg(0, std::ios::end);

    if (file.tellg() == 0) {
        errors.insert(Error(fileEmptyError));
        file.close();
        return;
    }

    file.seekg(0, std::ios::beg);

    std::ostringstream ss;
    ss << file.rdbuf();
    content = ss.str();

    file.close();
}

void readCoordsFile(const std::string& filename, std::string& content, std::set<Error>& errors) {
    std::ifstream file(filename);

    if (!file.is_open()) {  
        errors.insert(Error(fileOpenError));
        return;
    }

    file.seekg(0, std::ios::end);

    if (file.tellg() == 0) {
        errors.insert(Error(fileEmptyError));
        file.close();
        return;
    }

    file.seekg(0, std::ios::beg);

    std::ostringstream ss;
    ss << file.rdbuf();
    content = ss.str();

    file.close();
}

bool writeResult(const std::string& filename, const std::vector<Cell*>& path) {
    std::ofstream out(filename);

    if (!out.is_open()) {
        return false;
    }

    if (path.empty()) {
        out << "No path found";
    }
    else {
        for (std::size_t i = 0; i < path.size(); ++i) {
            if (i > 0) {
                out << ", ";
            }

            out << "(" << path[i]->y << ";" << path[i]->x << ")";
        }
    }

    out.close();
    return true;
}

void printErrors(const std::set<Error>& errors) {
    for (const auto& error : errors) {
        std::cerr << error.generate_error_message() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc > 4) {
        std::cerr << Error(tooManyArgumentsError).generate_error_message() << std::endl;
        return 1;
    }

    if (argc < 4) {
        std::cerr << Error(tooFewArgumentsError).generate_error_message() << std::endl;
        return 1;
    }

    std::set<Error> errors;
    std::string content;
    Maze maze;

    int startRow = 0;
    int startCol = 0;
    int endRow = 0;
    int endCol = 0;

    readMazeFile(argv[1], content, errors);

    if (errors.empty()) {
        parseMazeContent(content, maze, errors);
    }

    if (errors.empty()) {
        readCoordsFile(argv[2], content, errors);
    }

    if (errors.empty()) {
        parseCoordsContent(content, maze,
            startRow, startCol,
            endRow, endCol,
            errors);
    }

    if (!errors.empty()) {
        printErrors(errors);
        return 1;
    }

    PathFinder pathFinder(maze, startRow, startCol, endRow, endCol);
    std::vector<Cell*> path = pathFinder.findPath();

    if (!writeResult(argv[3], path)) {
        std::cerr << "Invalid output file. The specified path may not exist "
            "or you may not have write permissions." << std::endl;
        return 1;
    }

    return 0;
}