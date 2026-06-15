#pragma once

/**
 * @file Header.h
 * @brief Заголовочный файл программы поиска кратчайшего пути в лабиринте.
 *
 * Файл содержит перечисление типов ошибок, структуру ошибки,
 * и объявления всех функций, используемых для чтения входных файлов,
 * парсинга лабиринта и координат, поиска пути и записи результата.
 */

 /**
  * @mainpage Документация программы поиска кратчайшего пути в лабиринте
  *
  * @section intro_sec Назначение программы
  * Программа предназначена для поиска кратчайшего пути в лабиринте
  * методом обхода в ширину (BFS). Лабиринт задаётся текстовым файлом,
  * координаты начальной и конечной точек — отдельным файлом.
  *
  * @section input_sec Входные данные
  * Программа получает три аргумента командной строки:
  * - имя файла лабиринта;
  * - имя файла координат;
  * - имя выходного файла.
  *
  * Файл лабиринта:
  * - первая строка — целое число: количество строк лабиринта (1..255);
  * - вторая строка — целое число: количество столбцов лабиринта (1..255);
  * - далее строки лабиринта, где '.' — проход, '#' — стена.
  * Пробелы между символами допускаются.
  *
  * Файл координат:
  * - первая строка — два целых числа: строка и столбец начальной точки;
  * - вторая строка — два целых числа: строка и столбец конечной точки.
  *
  * @section output_sec Выходные данные
  * В выходной файл записывается последовательность координат пути
  * в формате (строка;столбец), разделённых запятой и пробелом.
  * Если путь не найден — записывается строка "No path found".
  *
  * @section example_sec Пример работы программы
  *
  * Пример запуска программы:
  *
  * @code{.bat}
  * shortest_path.exe maze.txt coordinates.txt coord_sequence.txt
  * @endcode
  *
  * Пример содержимого файла maze.txt:
  *
  * @code{.txt}
  * 4
  * 7
  * ##....#
  * #..##.#
  * #.....#
  * #######
  * @endcode
  *
  * Пример содержимого файла coordinates.txt:
  *
  * @code{.txt}
  * 0 5
  * 2 3
  * @endcode
  *
  * Пример содержимого выходного файла output.txt:
  *
  * @code{.txt}
  * (0;5), (1;5), (2;5), (2;4), (2;3)
  * @endcode
  */

  /**
   * @defgroup functions Functions
   * @brief Функции программы поиска кратчайшего пути в лабиринте.
   */

#include <string>
#include <set>
#include <vector>
#include <sstream>
#include "Error.h"
#include "Maze.h"
#include "Cell.h"

// Символы лабиринта
#define WALL_CHAR    '#'
#define PASSAGE_CHAR '.'

// Границы допустимых размеров лабиринта
#define MIN_MAZE_SIZE 1
#define MAX_MAZE_SIZE 255

/**
 * @ingroup shortest_path
 * @brief Читает содержимое текстового файла в строку.
 *
 * Функция открывает текстовый файл, проверяет возможность чтения
 * и наличие данных, после чего записывает всё содержимое файла в строку.
 *
 * @param[in]  filename Путь к текстовому файлу.
 * @param[out] content  Строка, в которую записывается содержимое файла.
 * @param[out] errors   Набор ошибок.
 */
void readTextFromFile(const std::string& filename, std::string& content,
    std::set<Error>& errors);

/**
 * @ingroup Functions
 * @brief Парсит содержимое файла лабиринта и заполняет объект Maze.
 *
 * Функция читает размеры лабиринта, проверяет их допустимость,
 * затем построчно читает символы лабиринта, игнорируя пробелы.
 * Допустимые символы: '.' (проход) и '#' (стена).
 *
 * @param[in]  content Содержимое файла лабиринта.
 * @param[out] maze    Объект лабиринта который будет заполнен.
 * @param[out] errors  Набор ошибок.
 */
void parseMazeContent(const std::string& content, Maze& maze, std::set<Error>& errors);

/**
 * @ingroup Functions
 * @brief Парсит размеры лабиринта из содержимого файла.
 *
 * Функция считывает количество строк и столбцов лабиринта,
 * а также проверяет, входят ли они в допустимый диапазон.
 *
 * @param[in]  content Содержимое файла лабиринта.
 * @param[out] rows    Количество строк лабиринта.
 * @param[out] cols    Количество столбцов лабиринта.
 * @param[out] errors  Набор ошибок.
 * @return true если размеры успешно считаны и корректны, false если найдена ошибка.
 */
bool parseMazeSize(const std::string& content, int& rows, int& cols,
    std::set<Error>& errors);

/**
 * @ingroup Functions
 * @brief Парсит одну строку лабиринта.
 *
 * Функция удаляет пробелы и табуляцию из строки, проверяет длину строки,
 * проверяет символы PASSAGE_CHAR и WALL_CHAR, а затем заполняет клетки
 * соответствующей строки объекта Maze.
 *
 * @param[in]  line       Строка лабиринта.
 * @param[out] maze       Объект лабиринта.
 * @param[in]  rowNumber  Номер строки лабиринта.
 * @param[in]  cols       Ожидаемое количество столбцов.
 * @param[out] hasPassage Флаг наличия хотя бы одной проходимой клетки.
 * @param[out] errors     Набор ошибок.
 * @return true если строка успешно разобрана, false если найдена ошибка.
 */
bool parseSingleMazeRow(const std::string& line, Maze& maze,
    int rowNumber, int cols, bool& hasPassage,
    std::set<Error>& errors);

/**
 * @ingroup Functions
 * @brief Парсит все строки лабиринта.
 *
 * Функция читает строки лабиринта из потока и для каждой строки вызывает
 * parseSingleMazeRow.
 *
 * @param[in,out] stream     Поток с содержимым файла лабиринта.
 * @param[out]    maze       Объект лабиринта.
 * @param[in]     rows       Ожидаемое количество строк.
 * @param[in]     cols       Ожидаемое количество столбцов.
 * @param[out]    hasPassage Флаг наличия хотя бы одной проходимой клетки.
 * @param[out]    actualRows Количество фактически прочитанных строк.
 * @param[out]    errors     Набор ошибок.
 */
void parseMazeGrid(std::istringstream& stream, Maze& maze,
    int rows, int cols, bool& hasPassage,
    int& actualRows, std::set<Error>& errors);

/**
 * @ingroup Functions
 * @brief Парсит два целых числа из строки.
 *
 * Функция читает ровно два целых числа из строки.
 * Если чисел больше двух — добавляется ошибка extraDataError.
 * Если чисел меньше двух — добавляется ошибка invalidFormatError.
 *
 * @param[in]  line    Строка для парсинга.
 * @param[in]  lineNum Номер строки в файле координат (для сообщения об ошибке).
 * @param[out] a       Первое число.
 * @param[out] b       Второе число.
 * @param[out] errors  Набор ошибок.
 * @return true если успешно, false если ошибка.
 */
bool parseTwoInts(const std::string& line, int lineNum, int& a, int& b, std::set<Error>& errors);

/**
 * @ingroup Functions
 * @brief Считывает целое число из строки и проверяет его границы.
 *
 * Функция получает строку с одним числом, пытается считать из неё целое значение,
 * сохраняет результат в выходной параметр и проверяет, входит ли число
 * в допустимый диапазон от min до max.
 *
 * @param[in]  str    Строка с числом.
 * @param[out] val    Переменная, в которую записывается считанное число.
 * @param[in]  min    Минимально допустимое значение.
 * @param[in]  max    Максимально допустимое значение.
 * @param[out] errors Набор ошибок.
 * @return true если число успешно считано и находится в допустимых границах, false если найдена ошибка.
 */
bool readIntFromStringAndCheckBounds(const std::string& str, int& val,
    int min, int max, std::set<Error>& errors);

/**
 * @ingroup Functions
 * @brief Разбирает одну строку координат.
 *
 * Функция читает из строки две координаты: строку и столбец.
 * Используется для обработки первой строки с начальной точкой
 * и второй строки с конечной точкой.
 *
 * @param[in]  line       Строка с координатами.
 * @param[out] first      Первое число из строки.
 * @param[out] second     Второе число из строки.
 * @param[in]  lineNumber Номер строки в файле координат.
 * @param[out] errors     Набор ошибок.
 * @return true если строка успешно разобрана, false если найдена ошибка.
 */
bool parseCoordsLine(const std::string& line, int& first, int& second,
    int lineNumber, std::set<Error>& errors);

/**
 * @ingroup Functions
 * @brief Проверяет клетки начальной и конечной точки.
 *
 * Функция проверяет, не являются ли начальная и конечная точки стенами,
 * а также не совпадают ли они друг с другом.
 *
 * @param[in]  maze          Лабиринт.
 * @param[in]  startRow      Строка начальной точки.
 * @param[in]  startCol      Столбец начальной точки.
 * @param[in]  endRow        Строка конечной точки.
 * @param[in]  endCol        Столбец конечной точки.
 * @param[in]  startInBounds true если начальная точка находится в границах лабиринта.
 * @param[in]  endInBounds   true если конечная точка находится в границах лабиринта.
 * @param[out] errors        Набор ошибок.
 */
void checkPointCells(const Maze& maze, int startRow, int startCol,
    int endRow, int endCol, bool startInBounds, bool endInBounds,
    std::set<Error>& errors);

/**
 * @ingroup Functions
 * @brief Читает две строки координат из содержимого файла.
 *
 * Функция получает содержимое файла координат, читает первую строку
 * с начальной точкой и вторую строку с конечной точкой. Также проверяет,
 * нет ли после них лишних строк с данными.
 *
 * @param[in]  content Содержимое файла координат.
 * @param[out] line1   Строка с координатами начальной точки.
 * @param[out] line2   Строка с координатами конечной точки.
 * @param[out] errors  Набор ошибок.
 * @return true если две строки координат были успешно прочитаны, false если найдена ошибка.
 */
bool readCoordsLines(const std::string& content,
    std::string& line1, std::string& line2,
    std::set<Error>& errors);
/**
 * @ingroup Functions
 * @brief Парсит содержимое файла координат и проверяет корректность точек.
 *
 * Функция читает координаты начальной и конечной точек,
 * проверяет что они находятся в границах лабиринта,
 * не являются стенами и не совпадают друг с другом.
 *
 * @param[in]  content   Содержимое файла координат.
 * @param[in]  maze      Объект лабиринта для проверки границ и стен.
 * @param[out] startRow  Строка начальной точки.
 * @param[out] startCol  Столбец начальной точки.
 * @param[out] endRow    Строка конечной точки.
 * @param[out] endCol    Столбец конечной точки.
 * @param[out] errors    Набор ошибок.
 * @return true если успешно, false если ошибка.
 */
bool parseCoordsContent(const std::string& content, const Maze& maze,
    int& startRow, int& startCol,
    int& endRow, int& endCol,
    std::set<Error>& errors);

/**
 * @ingroup shortest_path
 * @brief Записывает результат поиска пути в файл.
 *
 * Если путь найден — записывает последовательность координат
 * в формате (строка;столбец), разделённых ", ".
 * Если путь не найден — записывает строку "No path found".
 *
 * @param[in] filename Путь к выходному файлу.
 * @param[in] path     Вектор указателей на клетки пути.
 * @return true если успешно, false если файл не удалось открыть.
 */
bool writeResult(const std::string& filename, const std::vector<Cell*>& path);

/**
 * @ingroup shortest_path
 * @brief Выводит все ошибки из набора в stderr.
 *
 * Для каждой ошибки вызывается generate_error_message()
 * и результат выводится в стандартный поток ошибок.
 *
 * @param[in] errors Набор ошибок.
 */
void printErrors(const std::set<Error>& errors);