/**
 * @file Error.cpp
 * @brief Реализация формирования сообщений об ошибках.
 */

#include "Error.h"
#include <sstream>

 /**
  * @brief Формирует текстовое сообщение об ошибке в зависимости от её типа.
  * @return строка с сообщением
  */
std::string Error::generate_error_message() const {
    std::ostringstream msg;
    switch (type) {
    case fileOpenError:
        // Не удалось открыть файл
        msg << "Invalid maze file. The file may not exist or you may not have read permissions.";
        break;
    case fileEmptyError:
        // Файл пуст
        msg << "File is empty. Please check the file contents.";
        break;
    case invalidFormatError:
        // Неверный формат: если известна строка, сообщаем ожидаемое и фактическое количество символов
        if (row_number > 0)
            msg << "Row " << row_number
            << " contains an incorrect number of characters. Expected "
            << max_value << ", found " << value << ".";
        else
            msg << "Invalid file format.";
        break;
    case outOfRangeError:
        // Значение выходит за пределы 1..max_value
        msg << "Invalid maze file format. Value " << value
            << " is out of valid range 1.." << max_value << ".";
        break;
    case invalidCharError:
        // Встречен недопустимый символ
        msg << "Row " << row_number
            << " contains an invalid character '"
            << invalid_char << "'. Only '.' and '#' are allowed.";
        break;
    case noPassageError:
        // Нет ни одной проходимой клетки
        msg << "Invalid maze file contents. The maze contains no passable cells.";
        break;
    case coordOutOfBoundsError:
        // Координата за границами лабиринта
        msg << "Invalid coordinates. Value " << value
            << " is out of valid range 0.." << (max_value - 1) << ".";
        break;
    case startIsWallError:
        // Начальная точка — стена
        msg << "Invalid coordinates. Start point (row "
            << row_number << ", column " << col_number
            << ") is a wall and cannot be traversed.";
        break;
    case endIsWallError:
        // Конечная точка — стена
        msg << "Invalid coordinates. End point (row "
            << row_number << ", column " << col_number
            << ") is a wall and cannot be traversed.";
        break;
    case pointsSameError:
        // Точки совпадают
        msg << "Invalid coordinates. Start and end points must not be the same.";
        break;
    case extraDataError:
        // Лишние данные в файле
        msg << "File contains extra data.";
        break;
    case tooManyArgumentsError:
        // Слишком много аргументов командной строки
        msg << "Too many arguments. Usage: shortest_path.exe <maze.txt> <coordinates.txt> <coord_sequence.txt>";
        break;
    case tooFewArgumentsError:
        // Недостаточно аргументов командной строки
        msg << "Too few arguments. Usage: shortest_path.exe <maze.txt> <coordinates.txt> <coord_sequence.txt>";
        break;
    default:
        // Неизвестный тип ошибки
        msg << "Unknown error.";
        break;
    }
    return msg.str();
}