#include "Header.h"
#include "PathFinder.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>


//Читает содержимое текстового файла, проверяя открытие файла и наличие данных.
void readTextFromFile(const std::string& filename, std::string& content,
    std::set<Error>& errors) {
    // Открыть файл для чтения.
    std::ifstream file(filename);

    // Если файл не удалось открыть, добавить ошибку и завершить чтение.
    if (!file.is_open()) {
        errors.insert(Error(fileOpenError));
        return;
    }

    // Переместить указатель чтения в конец файла, чтобы проверить размер.
    file.seekg(0, std::ios::end);

    // Если файл пуст, добавить ошибку и завершить чтение.
    if (file.tellg() == 0) {
        errors.insert(Error(fileEmptyError));
        file.close();
        return;
    }

    // Вернуть указатель чтения в начало файла.
    file.seekg(0, std::ios::beg);

    // Считать всё содержимое файла в строковый поток.
    std::ostringstream stream;
    stream << file.rdbuf();

    // Сохранить содержимое файла в выходной параметр.
    content = stream.str();

    file.close();
}

// Записать результат поиска пути в выходной файл
bool writeResult(const std::string& filename, const std::vector<Cell*>& path) {
    // Открыть выходной файл для записи
    std::ofstream out(filename);
    // Если не удалось открыть, вернуть false
    if (!out.is_open()) return false;

    // Если путь не найден, записать "No path found"
    if (path.empty()) {
        out << "No path found";
    }
    else {
        // Вывести координаты в формате (строка;столбец), разделённые ", "
        for (std::size_t i = 0; i < path.size(); ++i) {
            if (i > 0) out << ", ";
            out << "(" << path[i]->y << ";" << path[i]->x << ")";
        }
    }

    out.close();
    return true;
}

// Выводит все ошибки из набора в стандартный поток ошибок
void printErrors(const std::set<Error>& errors) {
    for (const auto& e : errors)
        std::cerr << e.generate_error_message() << std::endl;
}

// Главная функция программы
int main(int argc, const char* argv[]) {
    // Проверить количество переданных аргументов командной строки
    if (argc > 4) {
        std::cerr << Error(tooManyArgumentsError).generate_error_message() << std::endl;
        return 1;
    }

    if (argc < 4) {
        std::cerr << Error(tooFewArgumentsError).generate_error_message() << std::endl;
        return 1;
    }

    // Создать контейнер для сбора ошибок
    std::set<Error> errors;
    std::string content;
    Maze maze;

    int startRow = 0;
    int startCol = 0;
    int endRow = 0;
    int endCol = 0;

    // Чтение и парсинг файла лабиринта
    readTextFromFile(argv[1], content, errors);

    if (errors.empty()) {
        parseMazeContent(content, maze, errors);
    }

    // Чтение и парсинг файла координат
    if (errors.empty()) {
        readTextFromFile(argv[2], content, errors);
    }

    if (errors.empty()) {
        parseCoordsContent(content, maze,
            startRow, startCol,
            endRow, endCol, errors);
    }

    // Если есть ошибки - вывести и завершить
    if (!errors.empty()) {
        printErrors(errors);
        return 1;
    }

    // Поиск кратчайшего пути
    PathFinder pathFinder(maze, startRow, startCol, endRow, endCol);
    std::vector<Cell*> path = pathFinder.findPath();

    // Запись результата в выходной файл
    if (!writeResult(argv[3], path)) {
        std::cerr << "Invalid output file. The specified path may not exist "
            "or you may not have write permissions." << std::endl;
        return 1;
    }

    return 0;
}