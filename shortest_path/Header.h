#pragma once
#include <string>
#include <set>
#include <vector>
#include "Error.h"
#include "Maze.h"
#include "Cell.h"

void readMazeFile(const std::string& filename, std::string& content, std::set<Error>& errors);

void parseMazeContent(const std::string& content, Maze& maze, std::set<Error>& errors);

void readCoordsFile(const std::string& filename, std::string& content, std::set<Error>& errors);

bool parseTwoInts(const std::string& line, int lineNum, int& a, int& b, std::set<Error>& errors);

bool parseCoordsContent(const std::string& content, const Maze& maze, int& startRow, int& startCol, int& endRow, int& endCol, std::set<Error>& errors);

bool writeResult(const std::string& filename, const std::vector<Cell*>& path);

void printErrors(const std::set<Error>& errors);