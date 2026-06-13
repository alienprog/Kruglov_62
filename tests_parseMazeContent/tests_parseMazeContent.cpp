#include "pch.h"
#include "CppUnitTest.h"
#include "../shortest_path/Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testsparseMazeContent {
    TEST_CLASS(testsparseMazeContent) {
public:
    // Корректный лабиринт
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
    // Лабиринт минимального размера 1×1 с проходом
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
    // Лабиринт 255×255 все проходы
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
    // Строки отсутствуют (rows = 0)
    TEST_METHOD(ZeroRows) {
        std::string content =
            "0\n"
            "7\n";

        Maze maze;
        std::set<Error> errors;

        parseMazeContent(content, maze, errors);

        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)outOfRangeError, (int)errors.begin()->type);
    }
    // Количество строк выходит за диапазон (rows = 256)
    TEST_METHOD(RowsOutOfRange) {
        std::string content =
            "256\n"
            "7\n";

        Maze maze;
        std::set<Error> errors;

        parseMazeContent(content, maze, errors);

        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)outOfRangeError, (int)errors.begin()->type);
    }
    // Столбцы отсутствуют (cols = 0)
    TEST_METHOD(ZeroCols) {
        std::string content =
            "4\n"
            "0\n";

        Maze maze;
        std::set<Error> errors;

        parseMazeContent(content, maze, errors);

        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)outOfRangeError, (int)errors.begin()->type);
    }
    // Количество столбцов выходит за диапазон (cols = 256)
    TEST_METHOD(ColsOutOfRange) {
        std::string content =
            "4\n"
            "256\n";

        Maze maze;
        std::set<Error> errors;

        parseMazeContent(content, maze, errors);

        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)outOfRangeError, (int)errors.begin()->type);
    }
    // Первая строка не является целым числом
    TEST_METHOD(FirstLineNotInteger) {
        std::string content =
            "abc\n"
            "7\n"
            "# # . . . . #\n"
            "# . . # # . #\n"
            "# . . . . . #\n"
            "# # # # # # #\n";

        Maze maze;
        std::set<Error> errors;

        parseMazeContent(content, maze, errors);

        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)invalidFormatError, (int)errors.begin()->type);
    }
    // Вторая строка не является целым числом
    TEST_METHOD(SecondLineNotInteger) {
        std::string content =
            "4\n"
            "abc\n"
            "# # . . . . #\n"
            "# . . # # . #\n"
            "# . . . . . #\n"
            "# # # # # # #\n";

        Maze maze;
        std::set<Error> errors;

        parseMazeContent(content, maze, errors);

        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)invalidFormatError, (int)errors.begin()->type);
    }
    // Количество строк меньше объявленного
    TEST_METHOD(FewerRowsThanDeclared) {
        std::string content =
            "4\n"
            "7\n"
            "# # . . . . #\n"
            "# . . # # . #\n";

        Maze maze;
        std::set<Error> errors;

        parseMazeContent(content, maze, errors);

        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)invalidFormatError, (int)errors.begin()->type);
    }
    // Длина строки не соответствует объявленному числу столбцов
    TEST_METHOD(WrongRowLength) {
        std::string content =
            "4\n"
            "7\n"
            "# # . . . . #\n"
            "# . . #\n"
            "# . . . . . #\n"
            "# # # # # # #\n";

        Maze maze;
        std::set<Error> errors;

        parseMazeContent(content, maze, errors);

        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)invalidFormatError, (int)errors.begin()->type);
    }
    // Недопустимый символ
    TEST_METHOD(InvalidCharacter) {
        std::string content =
            "4\n"
            "7\n"
            "# # . . . . #\n"
            "# . X # # . #\n"
            "# . . . . . #\n"
            "# # # # # # #\n";

        Maze maze;
        std::set<Error> errors;

        parseMazeContent(content, maze, errors);

        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)invalidCharError, (int)errors.begin()->type);
        Assert::AreEqual('X', errors.begin()->invalid_char);
        Assert::AreEqual(2, errors.begin()->row_number);
    }
    // Лабиринт полностью из стен
    TEST_METHOD(AllWalls) {
        std::string content =
            "4\n"
            "7\n"
            "# # # # # # #\n"
            "# # # # # # #\n"
            "# # # # # # #\n"
            "# # # # # # #\n";

        Maze maze;
        std::set<Error> errors;

        parseMazeContent(content, maze, errors);

        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)noPassageError, (int)errors.begin()->type);
    }
    // Лабиринт из одних проходов
    TEST_METHOD(AllPassages) {
        std::string content =
            "3\n"
            "3\n"
            ". . .\n"
            ". . .\n"
            ". . .\n";

        Maze maze;
        std::set<Error> errors;

        parseMazeContent(content, maze, errors);

        Assert::IsTrue(errors.empty());
    }
    // Корректный лабиринт без пустых строк
    TEST_METHOD(NoEmptyLines) {
        std::string content =
            "4\n"
            "7\n"
            "# # # . # . #\n"
            "# . . . . . #\n"
            "# . . . . . #\n"
            "# # # # # # #\n";

        Maze maze;
        std::set<Error> errors;

        parseMazeContent(content, maze, errors);

        Assert::IsTrue(errors.empty());
    }
    // Лабиринт 2×2 с одним проходом
    TEST_METHOD(Maze2x2OnePassage) {
        std::string content =
            "2\n"
            "2\n"
            "# .\n"
            "# #\n";

        Maze maze;
        std::set<Error> errors;

        parseMazeContent(content, maze, errors);
        Assert::IsTrue(errors.empty());
        Assert::IsTrue(maze.getCell(0, 0).isWall);
        Assert::IsFalse(maze.getCell(0, 1).isWall);
    }
    // Лабиринт 3×3 с проходом в центре
    TEST_METHOD(Maze3x3CenterPassage) {
        std::string content =
            "3\n"
            "3\n"
            "# # #\n"
            "# . #\n"
            "# # #\n";

        Maze maze;
        std::set<Error> errors;

        parseMazeContent(content, maze, errors);
        Assert::IsTrue(errors.empty());
        Assert::IsTrue(maze.getCell(0, 0).isWall);
        Assert::IsFalse(maze.getCell(1, 1).isWall);
        Assert::IsTrue(maze.getCell(2, 2).isWall);
    }
    };
}