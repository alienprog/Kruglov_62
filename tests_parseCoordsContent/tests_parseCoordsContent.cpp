#include "pch.h"
#include "CppUnitTest.h"
#include "../shortest_path/Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testsparseCoordsContent {
    TEST_CLASS(testsparseCoordsContent) {
public:

    // Вспомогательная функция: создаёт лабиринт 4x7
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

    // Проверка значений выходных параметров координат.
    void assertCoords(int sr, int sc, int er, int ec,
        int expectedSr, int expectedSc, int expectedEr, int expectedEc) {

        Assert::AreEqual(expectedSr, sr);
        Assert::AreEqual(expectedSc, sc);
        Assert::AreEqual(expectedEr, er);
        Assert::AreEqual(expectedEc, ec);
    }

    // Проверка, что первой ошибкой является ошибка нужного типа.
    void assertFirstErrorType(const std::set<Error>& errors, ErrorType expectedType) {
        Assert::IsFalse(errors.empty());
        Assert::AreEqual((int)expectedType, (int)errors.begin()->type);
    }

    // Проверка, что в наборе есть ошибка нужного типа.
    bool hasErrorType(const std::set<Error>& errors, ErrorType type) {
        for (const auto& error : errors) {
            if (error.type == type) {
                return true;
            }
        }

        return false;
    }

    // Проверяет наличие двух ошибок в наборе.
    void assertHasTwoErrorTypes(const std::set<Error>& errors,
        ErrorType firstType, ErrorType secondType) {

        Assert::IsTrue(errors.size() >= 2);
        Assert::IsTrue(hasErrorType(errors, firstType));
        Assert::IsTrue(hasErrorType(errors, secondType));
    }

    // Корректные координаты.
    TEST_METHOD(CorrectCoords) {
        Maze maze = makeMaze4x7();
        std::string content =
            "0 5\n"
            "2 3\n";

        std::set<Error> errors;
        int sr = -1, sc = -1, er = -1, ec = -1;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsTrue(result);
        Assert::IsTrue(errors.empty());
        assertCoords(sr, sc, er, ec, 0, 5, 2, 3);
    }

    // Пустой файл
    TEST_METHOD(EmptyFile) {
        Maze maze = makeMaze4x7();
        std::string content = "";

        std::set<Error> errors;
        int sr = -1, sc = -1, er = -1, ec = -1;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        assertFirstErrorType(errors, invalidFormatError);
        assertCoords(sr, sc, er, ec, -1, -1, -1, -1);
    }

    // Только одна строка с координатами
    TEST_METHOD(OnlyOneLine) {
        Maze maze = makeMaze4x7();
        std::string content =
            "5 0\n";

        std::set<Error> errors;
        int sr = -1, sc = -1, er = -1, ec = -1;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        assertFirstErrorType(errors, invalidFormatError);
        assertCoords(sr, sc, er, ec, 5, 0, -1, -1);
    }

    // В первой строке больше двух чисел
    TEST_METHOD(ExtraNumberInFirstLine) {
        Maze maze = makeMaze4x7();
        std::string content =
            "5 0 3\n"
            "2 3\n";

        std::set<Error> errors;
        int sr = -1, sc = -1, er = -1, ec = -1;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        assertFirstErrorType(errors, extraDataError);
        assertCoords(sr, sc, er, ec, 5, 0, 2, 3);
    }

    // Три строки с координатами
    TEST_METHOD(ThreeLines) {
        Maze maze = makeMaze4x7();
        std::string content =
            "0 5\n"
            "2 3\n"
            "4 6\n";

        std::set<Error> errors;
        int sr = -1, sc = -1, er = -1, ec = -1;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        assertFirstErrorType(errors, extraDataError);
        assertCoords(sr, sc, er, ec, 0, 5, 2, 3);
    }

    // Во второй строке больше двух чисел
    TEST_METHOD(ExtraNumberInSecondLine) {
        Maze maze = makeMaze4x7();
        std::string content =
            "0 5\n"
            "2 3 4\n";

        std::set<Error> errors;
        int sr = -1, sc = -1, er = -1, ec = -1;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        assertFirstErrorType(errors, extraDataError);
        assertCoords(sr, sc, er, ec, 0, 5, 2, 3);
    }

    // Координаты заданы буквами
    TEST_METHOD(LettersInsteadOfNumbers) {
        Maze maze = makeMaze4x7();
        std::string content =
            "a b\n"
            "2 3\n";

        std::set<Error> errors;
        int sr = -1, sc = -1, er = -1, ec = -1;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        assertFirstErrorType(errors, invalidFormatError);
    }

    // Отрицательное число в координатах
    TEST_METHOD(NegativeCoord) {
        Maze maze = makeMaze4x7();
        std::string content =
            "-1 5\n"
            "2 3\n";

        std::set<Error> errors;
        int sr = -1, sc = -1, er = -1, ec = -1;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        assertFirstErrorType(errors, coordOutOfBoundsError);
        assertCoords(sr, sc, er, ec, -1, 5, 2, 3);
    }

    // Номер строки начальной точки выходит за пределы
    TEST_METHOD(StartRowOutOfBounds) {
        Maze maze = makeMaze4x7();
        std::string content =
            "99 5\n"
            "3 2\n";

        std::set<Error> errors;
        int sr = -1, sc = -1, er = -1, ec = -1;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        assertFirstErrorType(errors, coordOutOfBoundsError);
        assertCoords(sr, sc, er, ec, 99, 5, 3, 2);
    }

    // Номер столбца начальной точки выходит за пределы
    TEST_METHOD(StartColOutOfBounds) {
        Maze maze = makeMaze4x7();
        std::string content =
            "1 10\n"
            "3 2\n";

        std::set<Error> errors;
        int sr = -1, sc = -1, er = -1, ec = -1;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        assertFirstErrorType(errors, coordOutOfBoundsError);
        assertCoords(sr, sc, er, ec, 1, 10, 3, 2);
    }

    // Номер строки конечной точки выходит за предел
    TEST_METHOD(EndRowOutOfBounds) {
        Maze maze = makeMaze4x7();
        std::string content =
            "0 5\n"
            "99 2\n";

        std::set<Error> errors;
        int sr = -1, sc = -1, er = -1, ec = -1;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        assertFirstErrorType(errors, coordOutOfBoundsError);
        assertCoords(sr, sc, er, ec, 0, 5, 99, 2);
    }

    // Номер столбца конечной точки выходит за пределы
    TEST_METHOD(EndColOutOfBounds) {
        Maze maze = makeMaze4x7();
        std::string content =
            "0 5\n"
            "3 10\n";

        std::set<Error> errors;
        int sr = -1, sc = -1, er = -1, ec = -1;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        assertFirstErrorType(errors, coordOutOfBoundsError);
        assertCoords(sr, sc, er, ec, 0, 5, 3, 10);
    }

    // Координаты заданы не целыми числами
    TEST_METHOD(FloatCoords) {
        Maze maze = makeMaze4x7();
        std::string content =
            "1.5 2\n"
            "3 4\n";

        std::set<Error> errors;
        int sr = -1, sc = -1, er = -1, ec = -1;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        Assert::IsTrue(hasErrorType(errors, extraDataError) || hasErrorType(errors, invalidFormatError));
    }

    // Начальная точка является стеной
    TEST_METHOD(StartIsWall) {
        Maze maze = makeMaze4x7();
        std::string content =
            "0 0\n"
            "2 3\n";

        std::set<Error> errors;
        int sr = -1, sc = -1, er = -1, ec = -1;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        assertFirstErrorType(errors, startIsWallError);
        assertCoords(sr, sc, er, ec, 0, 0, 2, 3);
    }

    // Конечная точка является стеной
    TEST_METHOD(EndIsWall) {
        Maze maze = makeMaze4x7();
        std::string content =
            "0 5\n"
            "3 0\n";

        std::set<Error> errors;
        int sr = -1, sc = -1, er = -1, ec = -1;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        assertFirstErrorType(errors, endIsWallError);
        assertCoords(sr, sc, er, ec, 0, 5, 3, 0);
    }

    // Начальная и конечная точки совпадают
    TEST_METHOD(SamePoints) {
        Maze maze = makeMaze4x7();
        std::string content =
            "0 5\n"
            "0 5\n";

        std::set<Error> errors;
        int sr = -1, sc = -1, er = -1, ec = -1;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        assertFirstErrorType(errors, pointsSameError);
        assertCoords(sr, sc, er, ec, 0, 5, 0, 5);
    }

    // Несколько ошибок: начальная и конечная точки являются стенами
    TEST_METHOD(MultipleErrorsStartAndEndAreWalls) {
        Maze maze = makeMaze4x7();
        std::string content =
            "0 0\n"
            "3 0\n";

        std::set<Error> errors;
        int sr = -1, sc = -1, er = -1, ec = -1;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        assertHasTwoErrorTypes(errors, startIsWallError, endIsWallError);
        assertCoords(sr, sc, er, ec, 0, 0, 3, 0);
    }

    // Несколько ошибок: старт вне границ, а конечная точка является стеной
    TEST_METHOD(MultipleErrorsStartOutOfBoundsAndEndIsWall) {
        Maze maze = makeMaze4x7();
        std::string content =
            "99 5\n"
            "3 0\n";

        std::set<Error> errors;
        int sr = -1, sc = -1, er = -1, ec = -1;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        assertHasTwoErrorTypes(errors, coordOutOfBoundsError, endIsWallError);
        assertCoords(sr, sc, er, ec, 99, 5, 3, 0);
    }

    // Несколько ошибок: лишние данные и начальная точка является стеной.
    TEST_METHOD(MultipleErrorsExtraDataAndStartIsWall) {
        Maze maze = makeMaze4x7();
        std::string content =
            "0 0\n"
            "2 3\n"
            "7 7\n";

        std::set<Error> errors;
        int sr = -1, sc = -1, er = -1, ec = -1;

        bool result = parseCoordsContent(content, maze, sr, sc, er, ec, errors);

        Assert::IsFalse(result);
        assertHasTwoErrorTypes(errors, extraDataError, startIsWallError);
        assertCoords(sr, sc, er, ec, 0, 0, 2, 3);
    }
    };
}