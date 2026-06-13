#include "pch.h"
#include "CppUnitTest.h"
#include "../shortest_path/Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testsparseCoordsContent {
    TEST_CLASS(testsparseCoordsContent) {
public:

    // Вспомогательная функция: создаёт лабиринт 4×7
    // ##....#
    // #..##.#
    // #.....#
    // #######
    Maze makeMaze4x7() {
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
        return maze;
    }
    // Корректные координаты
    TEST_METHOD(CorrectCoords) {
        Maze maze = makeMaze4x7();
        std::string content =
            "0 5\n"
            "2 3\n";

        std::set<Error> errors;
        int sr = 0;
        int sc = 0;
        int er = 0;
        int ec = 0;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsTrue(result);
        Assert::IsTrue(errors.empty());
        Assert::AreEqual(0, sr);
        Assert::AreEqual(5, sc);
        Assert::AreEqual(2, er);
        Assert::AreEqual(3, ec);
    }
    // Пустой файл
    TEST_METHOD(EmptyFile) {
        Maze maze = makeMaze4x7();
        std::string content = "";

        std::set<Error> errors;
        int sr = 0;
        int sc = 0;
        int er = 0;
        int ec = 0;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)invalidFormatError, (int)errors.begin()->type);
    }
    // Только одна строка с координатами
    TEST_METHOD(OnlyOneLine) {
        Maze maze = makeMaze4x7();
        std::string content =
            "5 0\n";

        std::set<Error> errors;
        int sr = 0;
        int sc = 0;
        int er = 0;
        int ec = 0;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)invalidFormatError, (int)errors.begin()->type);
    }
    // В первой строке больше двух чисел
    TEST_METHOD(ExtraNumberInFirstLine) {
        Maze maze = makeMaze4x7();
        std::string content =
            "5 0 3\n"
            "2 3\n";

        std::set<Error> errors;
        int sr = 0;
        int sc = 0;
        int er = 0;
        int ec = 0;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)extraDataError, (int)errors.begin()->type);
    }
    // Три строки с координатами
    TEST_METHOD(ThreeLines) {
        Maze maze = makeMaze4x7();
        std::string content =
            "0 5\n"
            "2 3\n"
            "4 6\n";

        std::set<Error> errors;
        int sr = 0;
        int sc = 0;
        int er = 0;
        int ec = 0;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)extraDataError, (int)errors.begin()->type);
    }
    // Во второй строке больше двух чисел
    TEST_METHOD(ExtraNumberInSecondLine) {
        Maze maze = makeMaze4x7();
        std::string content =
            "0 5\n"
            "2 3 4\n";

        std::set<Error> errors;
        int sr = 0;
        int sc = 0;
        int er = 0;
        int ec = 0;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)extraDataError, (int)errors.begin()->type);
    }
    // Координаты заданы буквами
    TEST_METHOD(LettersInsteadOfNumbers) {
        Maze maze = makeMaze4x7();
        std::string content =
            "a b\n"
            "2 3\n";

        std::set<Error> errors;
        int sr = 0;
        int sc = 0;
        int er = 0;
        int ec = 0;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)invalidFormatError, (int)errors.begin()->type);
    }
    // Отрицательное число в координата
    TEST_METHOD(NegativeCoord) {
        Maze maze = makeMaze4x7();
        std::string content =
            "-1 5\n"
            "2 3\n";

        std::set<Error> errors;
        int sr = 0;
        int sc = 0;
        int er = 0;
        int ec = 0;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)coordOutOfBoundsError, (int)errors.begin()->type);
    }
    // Номер строки начальной точки выходит за пределы
    TEST_METHOD(StartRowOutOfBounds) {
        Maze maze = makeMaze4x7();
        std::string content =
            "99 5\n"
            "3 2\n";

        std::set<Error> errors;
        int sr = 0;
        int sc = 0;
        int er = 0;
        int ec = 0;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)coordOutOfBoundsError, (int)errors.begin()->type);
    }
    // Номер столбца начальной точки выходит за пределы
    TEST_METHOD(StartColOutOfBounds) {
        Maze maze = makeMaze4x7();
        std::string content =
            "1 10\n"
            "3 2\n";

        std::set<Error> errors;
        int sr = 0;
        int sc = 0;
        int er = 0;
        int ec = 0;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)coordOutOfBoundsError, (int)errors.begin()->type);
    }
    // Номер строки конечной точки выходит за предел
    TEST_METHOD(EndRowOutOfBounds) {
        Maze maze = makeMaze4x7();
        std::string content =
            "0 5\n"
            "99 2\n";

        std::set<Error> errors;
        int sr = 0;
        int sc = 0;
        int er = 0;
        int ec = 0;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)coordOutOfBoundsError, (int)errors.begin()->type);
    }
    // Номер столбца конечной точки выходит за пределы
    TEST_METHOD(EndColOutOfBounds) {
        Maze maze = makeMaze4x7();
        std::string content =
            "0 5\n"
            "3 10\n";

        std::set<Error> errors;
        int sr = 0;
        int sc = 0;
        int er = 0;
        int ec = 0;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)coordOutOfBoundsError, (int)errors.begin()->type);
    }
    // Координаты заданы не целыми числами
    TEST_METHOD(FloatCoords) {
        Maze maze = makeMaze4x7();
        std::string content =
            "1.5 2\n"
            "3 4\n";

        std::set<Error> errors;
        int sr = 0;
        int sc = 0;
        int er = 0;
        int ec = 0;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        Assert::IsFalse(errors.empty());

        bool hasError = false;
        for (const auto& error : errors) {
            if (error.type == extraDataError || error.type == invalidFormatError) {
                hasError = true;
            }
        }

        Assert::IsTrue(hasError);
    }
    // Начальная точка является стеной
    TEST_METHOD(StartIsWall) {
        Maze maze = makeMaze4x7();
        std::string content =
            "0 0\n"
            "2 3\n";

        std::set<Error> errors;
        int sr = 0;
        int sc = 0;
        int er = 0;
        int ec = 0;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)startIsWallError, (int)errors.begin()->type);
    }
    // Конечная точка является стеной
    TEST_METHOD(EndIsWall) {
        Maze maze = makeMaze4x7();
        std::string content =
            "0 5\n"
            "3 0\n";

        std::set<Error> errors;
        int sr = 0;
        int sc = 0;
        int er = 0;
        int ec = 0;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)endIsWallError, (int)errors.begin()->type);
    }
    // Начальная и конечная точки совпадают
    TEST_METHOD(SamePoints) {
        Maze maze = makeMaze4x7();
        std::string content =
            "0 5\n"
            "0 5\n";

        std::set<Error> errors;
        int sr = 0;
        int sc = 0;
        int er = 0;
        int ec = 0;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)pointsSameError, (int)errors.begin()->type);
    }
    };
}