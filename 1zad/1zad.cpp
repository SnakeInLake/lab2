
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#include <fstream>
#include <cstring>


struct StackNode {
    std::string data; 
    StackNode* next;
};

struct Stack {
    StackNode* top;
    StackNode* rear;
    void init();
    void push(const std::string& value); 
    void pop();
    void print();
    void saveToFile(const std::string& fileName);
    void saveToFileRecursive(std::ofstream& fout, StackNode* node);
    void loadFromFile(const std::string& fileName);
    void destroy();
};
using namespace std;

void Stack::init() {
    top = nullptr;
}

void Stack::push(const string& value) { 
    StackNode* newStackNode = new StackNode;
    newStackNode->data = value;
    newStackNode->next = top;
    top = newStackNode;
}

void Stack::pop() {
    if (top == nullptr) {
        cout << "Стек пуст." << endl;
        return;
    }

    StackNode* temp = top;
    top = top->next;
    delete temp;
}

void Stack::print() {
    if (top == nullptr) {
        cout << "Стек пуст." << endl;
        return;
    }

    StackNode* temp = top;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}


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
    Stack tempStack = copyStack(taskStack);

    // Проверяем, существует ли dep2 в стеке задач
    bool foundDep2 = false;
    while (tempStack.top != nullptr) {
        if (tempStack.top->data == dep2) {
            foundDep2 = true;
            break;
        }
        tempStack.pop();
    }
    if (!foundDep2) return false; // Если dep2 не найден, задачи выполнить невозможно

    // Проверяем, что dep2 не встречается раньше dep1 в стеке
    tempStack = copyStack(taskStack); 
    bool foundDep1 = false;
    while (tempStack.top != nullptr) {
        if (tempStack.top->data == dep1) {
            foundDep1 = true;
            break; 
        }
        if (tempStack.top->data == dep2) {
            return false; // dep2 встречается раньше dep1, задачи выполнить невозможно
        }
        tempStack.pop();
    }
    if (!foundDep1) return false; // Если dep1 не найден, задачи выполнить невозможно

    return true; // Если все проверки пройдены, задачи выполнить возможно
}

int main() {
    Stack taskStack;
    taskStack.init();

    string inputLine;

    // Чтение всей строки
    getline(cin, inputLine); 

    // Разделение строки на две части по ']'
    size_t bracketPos = inputLine.find(']');
    string tasksPart = inputLine.substr(0, bracketPos + 1); // +1 чтобы включить ']'
    string dependenciesPart = inputLine.substr(bracketPos + 3); // +3 чтобы пропустить '], '

    // Парсинг задач
    stringstream ss_tasks(tasksPart);
    string word;
    char c;
    string task;

    ss_tasks >> word; // Считываем "задачи"
    ss_tasks >> word; // Считываем "="
    ss_tasks.ignore(); // Игнорируем '['

    while (ss_tasks >> c) {
        if (isalnum(c)) {
            task += c;
        } else if (c == ',' || c == ']') {
            cout << "Задача: " << task << endl; 
            taskStack.push(task);
            task = "";
            if (c == ']') break;
            ss_tasks.ignore(); 
        }
    }

    // Парсинг зависимостей
   stringstream ss_dep(dependenciesPart);
string dep1, dep2;

ss_dep >> word; // Считываем "зависимости"
ss_dep >> word; // Считываем "="
ss_dep.ignore(); // Игнорируем '['

bool possible = true; // Флаг для отслеживания возможности выполнения

while (ss_dep >> c) {
    if (isalnum(c)) {
        dep1 += c;
    } else if (c == ',') {
        ss_dep.ignore(); 
        ss_dep >> c; 
        dep2 = ""; 
        while (ss_dep >> c && c != '\'') {
            dep2 += c;
        }
        ss_dep.ignore(); 

        cout << "Зависимость: " << dep1 << " " << dep2 << endl;

        // Проверка зависимости
        if (!canCompleteTasks(taskStack, dep1, dep2)) {
            possible = false; // Если зависимость не выполнима, устанавливаем флаг в false

        }

        dep1 = "";
        
        if (ss_dep.peek() == ']') break; 

        while (ss_dep.peek() == ' ') ss_dep.ignore(); 
        ss_dep.ignore(3);
    } else if (c == ']') {
        break; 
    }
    else if (isalnum(c)) {  
        dep2 += c; // Если следующий символ - буква, добавляем ее к dep1
    }
}

// Вывод результата на основе флага possible
if (possible) {
    cout << "Возможно" << endl;
} else {
    cout << "Невозможно" << endl;
}

return 0;
}
