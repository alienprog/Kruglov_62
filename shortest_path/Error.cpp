#include "Error.h"
#include <sstream>

std::string Error::generate_error_message() const {
    std::ostringstream msg;

    switch (type) {
    case fileOpenError:
        msg << "Invalid maze file. The file may not exist or you may not have read permissions.";
        break;

    case fileEmptyError:
        msg << "File is empty. Please check the file contents.";
        break;

    case invalidFormatError:
        if (row_number > 0) {
            msg << "Row " << row_number
                << " contains an incorrect number of characters. Expected "
                << max_value << ", found " << value << ".";
        }
        else {
            msg << "Invalid file format.";
        }
        break;

    case outOfRangeError:
        msg << "Invalid maze file format. Value " << value
            << " is out of valid range 1.." << max_value << ".";
        break;

    case invalidCharError:
        msg << "Row " << row_number
            << " contains an invalid character '"
            << invalid_char << "'. Only '.' and '#' are allowed.";
        break;

    case noPassageError:
        msg << "Invalid maze file contents. The maze contains no passable cells.";
        break;

    case coordOutOfBoundsError:
        msg << "Invalid coordinates. Value " << value
            << " is out of valid range 0.." << (max_value - 1) << ".";
        break;

    case startIsWallError:
        msg << "Invalid coordinates. Start point (row "
            << row_number << ", column " << col_number
            << ") is a wall and cannot be traversed.";
        break;

    case endIsWallError:
        msg << "Invalid coordinates. End point (row "
            << row_number << ", column " << col_number
            << ") is a wall and cannot be traversed.";
        break;

    case pointsSameError:
        msg << "Invalid coordinates. Start and end points must not be the same.";
        break;

    case extraDataError:
        msg << "File contains extra data.";
        break;

    case tooManyArgumentsError:
        msg << "Too many arguments. Usage: shortest_path.exe <maze.txt> <coordinates.txt> <coord_sequence.txt>";
        break;

    case tooFewArgumentsError:
        msg << "Too few arguments. Usage: shortest_path.exe <maze.txt> <coordinates.txt> <coord_sequence.txt>";
        break;

    default:
        msg << "Unknown error.";
        break;
    }

    return msg.str();
}