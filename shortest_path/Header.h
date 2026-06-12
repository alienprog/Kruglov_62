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
#include "Error.h"
#include "Maze.h"
#include "Cell.h"

   /**
    * @ingroup shortest_path
    * @brief Читает содержимое файла лабиринта в строку.
    * @param[in]  filename Путь к файлу лабиринта.
    * @param[out] content  Строка куда записывается содержимое файла.
    * @param[out] errors   Набор ошибок.
    */
void readMazeFile(const std::string& filename, std::string& content, std::set<Error>& errors);

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
 * @ingroup shortest_path
 * @brief Читает содержимое файла координат в строку.
 * @param[in]  filename Путь к файлу координат.
 * @param[out] content  Строка куда записывается содержимое файла.
 * @param[out] errors   Набор ошибок.
 */
void readCoordsFile(const std::string& filename, std::string& content, std::set<Error>& errors);

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