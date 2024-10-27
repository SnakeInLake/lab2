#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>

using namespace std;

struct StackNode {
    std::string data; 
    StackNode* next; 
};

// Структура для представления стека
struct Stack {
    StackNode* top; 

    void init(); 
    void push(const std::string& value);
    void pop(); 
    void print(); 
};

// Инициализация стека
void Stack::init() {
    top = nullptr; // Устанавливаем верхний элемент в nullptr (стек пуст)
}

// Добавление элемента в стек
void Stack::push(const string& value) {
    StackNode* newStackNode = new StackNode; // Создаем новый узел стека
    newStackNode->data = value; // Записываем данные в узел
    newStackNode->next = top; // Устанавливаем указатель next на текущий верхний элемент
    top = newStackNode; // Новый узел становится верхним элементом стека
}

// Удаление элемента из стека
void Stack::pop() {
    if (top == nullptr) { // Если стек пуст
        cout << "Стек пуст." << endl;
        return;
    }

    StackNode* temp = top; // Сохраняем указатель на верхний элемент
    top = top->next; // Перемещаем top на следующий элемент
    delete temp; // Удаляем старый верхний элемент
}

// Создание копии стека
Stack copyStack(const Stack& original) {
    Stack newStack; 
    newStack.init(); 
    StackNode* current = original.top; 
    while (current != nullptr) { 
        newStack.push(current->data); 
        current = current->next; 
    }
    return newStack; 
}

bool canCompleteTasks(Stack taskStack, string dep1, string dep2) {
    // Создаем копию стека, чтобы не изменять исходный стек
    Stack tempStack = copyStack(taskStack); 

    // Проверяем, существует ли dep2 в стеке задач
    bool foundDep2 = false;
    while (tempStack.top != nullptr) { // Проходим по стеку
        if (tempStack.top->data == dep2) { // Если нашли dep2
            foundDep2 = true;
            break; // Выходим из цикла
        }
        tempStack.pop(); 
    }
    if (!foundDep2) return false; // Если dep2 не найден, задачи выполнить невозможно

    // Проверяем, что dep2 не встречается раньше dep1 в стеке
    tempStack = copyStack(taskStack); // Создаем еще одну копию стека
    bool foundDep1 = false;
    while (tempStack.top != nullptr) { 
        if (tempStack.top->data == dep1) { 
            foundDep1 = true;
            break; 
        }
        if (tempStack.top->data == dep2) { 
            return false; 
        }
        tempStack.pop(); 
    }
    if (!foundDep1) return false; 

    return true; 
}

int main() {
    Stack taskStack; 
    taskStack.init(); 

    string inputLine; 

    getline(cin, inputLine); 

    size_t bracketPos = inputLine.find(']'); 
    string tasksPart = inputLine.substr(0, bracketPos + 1); 
    string dependenciesPart = inputLine.substr(bracketPos + 3); 

    // Парсинг задач
    stringstream ss_tasks(tasksPart); 
    string word; 
    char c; 
    string task; 

    ss_tasks >> word; 
    ss_tasks >> word; 
    ss_tasks.ignore(); 

    while (ss_tasks >> c) { 
        if (isalnum(c)) { 
            task += c; 
        } else if (c == ',' || c == ']') { 
            taskStack.push(task); 
            task = ""; 
            if (c == ']') break; 
            ss_tasks.ignore(); 
        }
    }


    stringstream ss_dep(dependenciesPart); 
    string dep1, dep2; 
    
    ss_dep >> word; 
    ss_dep >> word; 
    ss_dep.ignore(); 

    bool possible = true; // Флаг, указывающий, возможно ли выполнить все задачи

    while (ss_dep >> c) { // Читаем символы из потока зависимостей
        if (isalnum(c)) { // Если символ - буква или цифра
            dep1 += c; 
        } else if (c == ',') { // Если символ - запятая
            ss_dep.ignore(); 
            ss_dep.ignore(); 

            dep2 = ""; // Очищаем название второй задачи
            while (ss_dep >> c && c != '\'') { // Читаем название второй задачи до закрывающей кавычки
                dep2 += c; 
            }
            ss_dep.ignore(); // Игнорируем закрывающую кавычку '

            if (!canCompleteTasks(taskStack, dep1, dep2)) { 
                possible = false; 
            }

            dep1 = ""; 

            if (ss_dep.peek() == ']') break; 

            while (ss_dep.peek() == ' ') ss_dep.ignore(); 
            ss_dep.ignore(3); // Игнорируем '), (' 
        } else if (c == ']') { 
            break; 
        }
    }

        cout << "Возможно" << endl; 
    } else {
        cout << "Невозможно" << endl;
    }

    return 0;
}
