#pragma once
#include <string>

enum ErrorType {
    noError,
    fileOpenError,
    fileEmptyError,
    invalidFormatError,
    outOfRangeError,
    invalidCharError,
    noPassageError,
    coordOutOfBoundsError,
    startIsWallError,
    endIsWallError,
    pointsSameError,
    extraDataError,
    tooManyArgumentsError,
    tooFewArgumentsError
};

struct Error {
    ErrorType type;
    int       row_number;
    int       col_number;
    int       value;
    int       max_value;
    char      invalid_char;

    Error(ErrorType t,
        int row = 0, int col = 0,
        int val = 0, int maxVal = 0,
        char ch = '\0')
        : type(t), row_number(row), col_number(col),
        value(val), max_value(maxVal), invalid_char(ch) {
    }

    bool operator<(const Error& other) const {
        if (type != other.type) return type < other.type;
        if (row_number != other.row_number) return row_number < other.row_number;
        return col_number < other.col_number;
    }

    std::string generate_error_message() const;
};