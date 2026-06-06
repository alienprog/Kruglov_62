#include "pch.h"
#include "CppUnitTest.h"
#include "../shortest_path/Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testsparseCoordsContent {
    TEST_CLASS(testsparseCoordsContent) {
public:

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
    };
}