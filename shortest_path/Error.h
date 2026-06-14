/**
 * @file Error.h
 * @brief Типы ошибок и структура для их хранения.
 */

#pragma once
#include <string>

 /**
  * @enum ErrorType
  * @brief Типы ошибок, возникающих в программе.
  */
enum ErrorType {
    noError,                ///< нет ошибки
    fileOpenError,          ///< не удалось открыть файл
    fileEmptyError,         ///< файл пуст
    invalidFormatError,     ///< неверный формат данных
    outOfRangeError,        ///< значение вне допустимого диапазона
    invalidCharError,       ///< недопустимый символ в лабиринте
    noPassageError,         ///< нет ни одной проходимой клетки
    coordOutOfBoundsError,  ///< координата за границами лабиринта
    startIsWallError,       ///< начальная точка — стена
    endIsWallError,         ///< конечная точка — стена
    pointsSameError,        ///< начальная и конечная точки совпадают
    extraDataError,         ///< лишние данные в файле координат
    tooManyArgumentsError,  ///< слишком много аргументов командной строки
    tooFewArgumentsError    ///< недостаточно аргументов командной строки
};

/**
 * @struct Error
 * @brief Структура для хранения информации об ошибке.
 *
 * Содержит тип, позицию (строка, столбец), числовые значения и недопустимый символ.
 */
struct Error {
    ErrorType type;         ///< тип ошибки
    int       row_number;   ///< номер строки (для ошибок в файле)
    int       col_number;   ///< номер столбца (для ошибок в файле)
    int       value;        ///< числовое значение (например, ошибочная координата)
    int       max_value;    ///< максимально допустимое значение
    char      invalid_char; ///< недопустимый символ

    /**
    * @brief Конструктор ошибки.
    * @param t тип ошибки
    * @param row номер строки (по умолчанию 0)
    * @param col номер столбца (по умолчанию 0)
    * @param val значение (по умолчанию 0)
    * @param maxVal максимальное значение (по умолчанию 0)
    * @param ch недопустимый символ (по умолчанию '\0')
    */
    explicit Error(ErrorType t,
        int row = 0, int col = 0,
        int val = 0, int maxVal = 0,
        char ch = '\0')
        : type(t), row_number(row), col_number(col),
        value(val), max_value(maxVal), invalid_char(ch) {
    }

    /**
     * @brief Оператор сравнения для использования в std::set.
     * @param other другая ошибка
     * @return true если текущая ошибка меньше другой
     */
    bool operator<(const Error& other) const {
        if (type != other.type) return type < other.type;
        if (row_number != other.row_number) return row_number < other.row_number;
        return col_number < other.col_number;
    }

    /**
     * @brief Генерирует текстовое сообщение об ошибке.
     * @return строка с сообщением
     */
    std::string generate_error_message() const;
};