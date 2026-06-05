#include "pch.h"
#include "CppUnitTest.h"
#include "../shortest_path/Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testsparseMazeContent {
    TEST_CLASS(testsparseMazeContent) {
public:

    TEST_METHOD(CorrectMaze) {
        std::string content =
            "4\n"
            "7\n"
            "# # . . . . #\n"
            "# . . # # . #\n"
            "# . . . . . #\n"
            "# # # # # # #\n";

        Maze maze;
        std::set<Error> errors;
        parseMazeContent(content, maze, errors);
        Assert::IsTrue(errors.empty());
        Assert::AreEqual(4, maze.getRows());
        Assert::AreEqual(7, maze.getCols());
        Assert::IsTrue(maze.getCell(0, 0).isWall);
        Assert::IsFalse(maze.getCell(0, 2).isWall);
    }

    TEST_METHOD(MinimalMaze1x1) {
        std::string content =
            "1\n"
            "1\n"
            ".\n";

        Maze maze;
        std::set<Error> errors;
        parseMazeContent(content, maze, errors);
        Assert::IsTrue(errors.empty());
        Assert::AreEqual(1, maze.getRows());
        Assert::AreEqual(1, maze.getCols());
        Assert::IsFalse(maze.getCell(0, 0).isWall);
    }

    TEST_METHOD(MaxMaze255x255) {
        std::string row255(255, '.');
        std::string content = "255\n255\n";

        for (int i = 0; i < 255; ++i) {
            content += row255 + "\n";
        }

        Maze maze;
        std::set<Error> errors;

        parseMazeContent(content, maze, errors);

        Assert::IsTrue(errors.empty());
        Assert::AreEqual(255, maze.getRows());
        Assert::AreEqual(255, maze.getCols());
    }
    };
}