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
    return 0;
}