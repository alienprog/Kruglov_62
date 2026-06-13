#include "pch.h"
#include "CppUnitTest.h"
#include "../shortest_path/Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testsparseMazeContent {

    TEST_CLASS(testsparseMazeContent) {
public:

    // Вспомогательная функция для проверки, что каждая клетка лабиринта совпадает с ожидаемой матрицей.
    template<int Rows, int Cols>
    void assertMazeWalls(const Maze& maze, const bool(&isWallMatrix)[Rows][Cols]) {
        Assert::AreEqual(Rows, maze.getRows());
        Assert::AreEqual(Cols, maze.getCols());

        for (int row = 0; row < Rows; ++row) {
            for (int col = 0; col < Cols; ++col) {
                Assert::AreEqual(isWallMatrix[row][col], maze.getCell(row, col).isWall);
            }
        }
    }

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

        bool isWallMatrix[4][7] = {
            {true,  true,  false, false, false, false, true},
            {true,  false, false, true,  true,  false, true},
            {true,  false, false, false, false, false, true},
            {true,  true,  true,  true,  true,  true,  true}
        };

        Assert::IsTrue(errors.empty());
        assertMazeWalls(maze, isWallMatrix);
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

        bool isWallMatrix[1][1] = {
            {false}
        };

        Assert::IsTrue(errors.empty());
        assertMazeWalls(maze, isWallMatrix);
    }

    // Лабиринт 255×255 все проходы
    // Проверяет лабиринт максимального размера 255x255.
    TEST_METHOD(MaxMaze255x255) {
        std::string content = "255\n255\n";
        bool isWallMatrix[255][255];

        for (int row = 0; row < 255; ++row) {
            for (int col = 0; col < 255; ++col) {
                isWallMatrix[row][col] = ((row + col) % 2 == 0);

                if (isWallMatrix[row][col]) {
                    content += "#";
                }
                else {
                    content += ".";
                }
                if (col < 254) {
                    content += " ";
                }
            }
            content += "\n";
        }
        Maze maze;
        std::set<Error> errors;

        parseMazeContent(content, maze, errors);

        Assert::IsTrue(errors.empty());
        assertMazeWalls(maze, isWallMatrix);
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

        bool isWallMatrix[3][3] = {
            {false, false, false},
            {false, false, false},
            {false, false, false}
        };

        Assert::IsTrue(errors.empty());
        assertMazeWalls(maze, isWallMatrix);
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

        bool isWallMatrix[4][7] = {
            {true, true, true,  false, true,  false, true},
            {true, false, false, false, false, false, true},
            {true, false, false, false, false, false, true},
            {true, true, true,  true,  true,  true,  true}
        };

        Assert::IsTrue(errors.empty());
        assertMazeWalls(maze, isWallMatrix);
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

        bool isWallMatrix[2][2] = {
            {true, false},
            {true, true}
        };

        Assert::IsTrue(errors.empty());
        assertMazeWalls(maze, isWallMatrix);
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

        bool isWallMatrix[3][3] = {
            {true, true,  true},
            {true, false, true},
            {true, true,  true}
        };

        Assert::IsTrue(errors.empty());
        assertMazeWalls(maze, isWallMatrix);
    }
    };
}
