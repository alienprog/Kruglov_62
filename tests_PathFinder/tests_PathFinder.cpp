#include "pch.h"
#include "CppUnitTest.h"
#include "../shortest_path/Header.h"
#include "../shortest_path/PathFinder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testsPathFinder {
    TEST_CLASS(testsPathFinder) {
public:

    Maze buildMaze(const std::string& content) {
        Maze maze;
        std::set<Error> errors;
        parseMazeContent(content, maze, errors);
        return maze;
    }

    std::string pathToString(const std::vector<Cell*>& path) {
        std::string result;

        for (std::size_t i = 0; i < path.size(); ++i) {
            if (i > 0) {
                result += ", ";
            }

            result += "(" + std::to_string(path[i]->y) + ";"
                + std::to_string(path[i]->x) + ")";
        }

        return result;
    }

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

        Assert::IsFalse(path.empty());
        Assert::AreEqual(0, path.front()->y);
        Assert::AreEqual(5, path.front()->x);
        Assert::AreEqual(2, path.back()->y);
        Assert::AreEqual(3, path.back()->x);
        Assert::AreEqual((std::size_t)5, path.size());

        std::string expected = "(0;5), (1;5), (2;5), (2;4), (2;3)";
        Assert::AreEqual(expected, pathToString(path));
    }

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

        Assert::IsFalse(path.empty());
        Assert::AreEqual(0, path.front()->y);
        Assert::AreEqual(5, path.front()->x);
        Assert::AreEqual(2, path.back()->y);
        Assert::AreEqual(3, path.back()->x);
        Assert::AreEqual((std::size_t)5, path.size());

        std::string actual = pathToString(path);
        bool isFirst = actual == "(0;5), (0;4), (0;3), (1;3), (2;3)";
        bool isSecond = actual == "(0;5), (1;5), (2;5), (2;4), (2;3)";

        Assert::IsTrue(isFirst || isSecond);
    }
    };
}