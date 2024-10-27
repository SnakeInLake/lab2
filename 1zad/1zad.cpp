
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
    Stack tempStack = copyStack(taskStack); // Глубокая копия для поиска dep2
    bool foundDep2 = false;
    while (tempStack.top != nullptr) {
        if (tempStack.top->data == dep2) {
            foundDep2 = true;
            break;
        }
        tempStack.pop();
    }
    if (!foundDep2) return false;

    tempStack = copyStack(taskStack); // Глубокая копия для проверки порядка
    while (tempStack.top != nullptr) {
        if (tempStack.top->data == dep1) break;
        if (tempStack.top->data == dep2) return false;
        tempStack.pop();
    }
    if (tempStack.top == nullptr) return false;

    // Создаем новый стек без dep1
    Stack newTaskStack;
    newTaskStack.init();
    tempStack = copyStack(taskStack); // Глубокая копия для создания нового стека
    while (tempStack.top != nullptr) {
        if (tempStack.top->data != dep1) {
            newTaskStack.push(tempStack.top->data);
        }
        tempStack.pop();
    }
    taskStack = newTaskStack; // Заменяем старый стек новым
    return true;
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

    while (ss_dep >> c) {
        if (isalnum(c)) {
            dep1 += c;
        } else if (c == ',') {
            ss_dep.ignore(); 
            ss_dep >> c; // Считываем '('
            ss_dep >> dep2;
            ss_dep.ignore(); // Игнорируем ')'

            cout << "Зависимость: " << dep1 << " " << dep2 << endl;

            // Проверка зависимости
            if (!canCompleteTasks(taskStack, dep1, dep2)) {
                cout << "Невозможно" << endl;
                return 0;
            }

            dep1 = "";
            dep2 = "";
            if (ss_dep.peek() == ']') break;

            while (ss_dep.peek() == ' ') { // Пропускаем пробелы
            ss_dep.ignore();
        }
        ss_dep.ignore(3); // Игнорируем ', (' 
        
        while (ss_dep.peek() == ' ') { // Пропускаем пробелы
            ss_dep.ignore();
        }
    }

    cout << "Возможно" << endl;

    return 0;
}
}