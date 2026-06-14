#include "pch.h"
#include "CppUnitTest.h"
#include "../shortest_path/Header.h"
#include "../shortest_path/PathFinder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testsPathFinder {
    TEST_CLASS(testsPathFinder) {
public:

    // Вспомогательная функция: строит лабиринт из строки.
    Maze buildMaze(const std::string& content) {
        Maze maze;
        std::set<Error> errors;
        parseMazeContent(content, maze, errors);
        return maze;
    }

    // Вспомогательная функция: преобразует путь в вектор пар (строка, столбец).
    std::vector<std::pair<int, int>> pathToVectorPairInt(const std::vector<Cell*>& path) {
        std::vector<std::pair<int, int>> result;

        for (Cell* cell : path) {
            result.push_back({ cell->y, cell->x });
        }

        return result;
    }

    // Вспомогательная функция: сравнивает путь с ожидаемым вектором координат.
    void assertPathEquals(const std::vector<Cell*>& path,
        const std::vector<std::pair<int, int>>& expectedPath) {

        std::vector<std::pair<int, int>> actualPath = pathToVectorPairInt(path);

        Assert::AreEqual(expectedPath.size(), actualPath.size());

        for (std::size_t i = 0; i < expectedPath.size(); ++i) {
            Assert::AreEqual(expectedPath[i].first, actualPath[i].first);
            Assert::AreEqual(expectedPath[i].second, actualPath[i].second);
        }
    }

    // Корректный путь.
    TEST_METHOD(CorrectPath) {
        std::string content =
            "4\n"
            "7\n"
            "# # . . . . #\n"
            "# . . # # . #\n"
            "# . . . . . #\n"
            "# # # # # # #\n";

        Maze maze = buildMaze(content);
        PathFinder pathFinder(maze, 0, 5, 2, 3);

        std::vector<Cell*> path = pathFinder.findPath();

        std::vector<std::pair<int, int>> expectedPath = {
            {0, 5}, {1, 5}, {2, 5}, {2, 4}, {2, 3}
        };

        Assert::IsFalse(path.empty());
        assertPathEquals(path, expectedPath);
    }

    // Путь не существует.
    TEST_METHOD(NoPath) {
        std::string content =
            "4\n"
            "7\n"
            "# # . . # . #\n"
            "# . . . # # #\n"
            "# . . . . . #\n"
            "# # # # # # #\n";

        Maze maze = buildMaze(content);
        PathFinder pathFinder(maze, 0, 5, 2, 3);

        std::vector<Cell*> path = pathFinder.findPath();

        Assert::IsTrue(path.empty());
    }

    // Два и более кратчайших пути
    TEST_METHOD(MultipleShortest) {
        std::string content =
            "4\n"
            "7\n"
            "# # . . . . #\n"
            "# . . . # . #\n"
            "# . . . . . #\n"
            "# # # # # # #\n";

        Maze maze = buildMaze(content);
        PathFinder pathFinder(maze, 0, 5, 2, 3);

        std::vector<Cell*> path = pathFinder.findPath();

        std::vector<std::pair<int, int>> actualPath = pathToVectorPairInt(path);

        std::vector<std::pair<int, int>> firstPath = {
            {0, 5}, {0, 4}, {0, 3}, {1, 3}, {2, 3}
        };

        std::vector<std::pair<int, int>> secondPath = {
            {0, 5}, {1, 5}, {2, 5}, {2, 4}, {2, 3}
        };

        Assert::IsFalse(path.empty());
        Assert::AreEqual((std::size_t)5, path.size());

        bool isFirst = actualPath == firstPath;
        bool isSecond = actualPath == secondPath;

        Assert::IsTrue(isFirst || isSecond);
    }
    };
}