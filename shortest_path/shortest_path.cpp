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
    return false;
}

void printErrors(const std::set<Error>& errors) {
}

int main(int argc, char* argv[]) {
    return 0;
}