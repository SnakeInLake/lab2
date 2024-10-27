#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "HashTable.h" // Подключаем вашу хэш-таблицу
#include <string.h>

using namespace std;


// Функции для работы с множеством (используя хэш-таблицу)
void setAdd(const string& value) {
    insert(value, " "); // Вставляем ключ (значение не важно)
}


void setRemove(const string& value) {
    remove(value);
}

bool setContains(const string& value) {
    return get(value) != "Ключ не найден"; 
}

void setPrint() {
    printTable(); // Выводит всю таблицу, можно адаптировать для вывода только ключей
}

void setLoadFromFile(const string& fileName) {
    loadFromFile(fileName);
}

void setSaveToFile(const string& fileName) {
    saveToFile(fileName);
}

int main(int argc, char* argv[]) {
    initTable(); // Инициализируем хэш-таблицу

    string fileName;
    string query;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--file") == 0 && i + 1 < argc) {
            fileName = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "--query") == 0 && i + 1 < argc) {
            query = argv[i + 1];
            i++;
        }
    }

    if (fileName.empty()) {
        cout << "Ошибка: не указан файл (--file)" << endl;
        return 1;
    }

    if (query.empty()) {
        cout << "Ошибка: не указан запрос (--query)" << endl;
        return 1;
    }

    setLoadFromFile(fileName);

    string command;
    string value;
    stringstream ss(query);

    ss >> command;

    if (command == "ADD") {
        ss >> value;
        setAdd(value);
        cout << "Значение " << value << " добавлено в множество." << endl;
    } else if (command == "REMOVE") {
        ss >> value;
        setRemove(value);
        cout << "Значение " << value << " удалено из множества." << endl;
    } else if (command == "CONTAINS") {
        ss >> value;
        if (setContains(value)) {
            cout << "Множество содержит значение " << value << "." << endl;
        } else {
            cout << "Множество не содержит значение " << value << "." << endl;
        }
    } else if (command == "PRINT") {
        cout << "Множество: ";
        setPrint();
    } else {
        cout << "Ошибка: неизвестная команда " << command << endl;
    }

    setSaveToFile(fileName);
    freeTable();

    return 0;
}