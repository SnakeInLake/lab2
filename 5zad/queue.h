#pragma once

#include <iostream>
#include <stdexcept>
using namespace std;

// Структура узла очереди
template <typename T>
struct QueueNode {
    T data;               // Данные узла (тип T)
    QueueNode* next;      // Указатель на следующий узел
};

// Структура для очереди
template <typename T>
struct Queue {
    QueueNode<T>* front;  // Указатель на начало очереди
    QueueNode<T>* rear;   // Указатель на конец очереди

    // Инициализация очереди
    void init() {
        front = nullptr;
        rear = nullptr;
    }

    // Добавление элемента в очередь (enqueue)
    void enqueue(const T& value) { 
        QueueNode<T>* newQueueNode = new QueueNode<T>();
        newQueueNode->data = value;
        newQueueNode->next = nullptr;

        if (rear != nullptr) {
            rear->next = newQueueNode;
        }
        rear = newQueueNode;

        if (front == nullptr) {
            front = rear;
        }
    }

    // Удаление элемента из очереди (dequeue)
    void dequeue() {
        if (front == nullptr) {
            cout << "Очередь пуста." << endl;
            return;
        }

        QueueNode<T>* temp = front;
        front = front->next;
        delete temp;

        if (front == nullptr) {
            rear = nullptr;
        }
    }

    // Получение элемента из начала очереди (front) без удаления
    T peek() const {
        if (front == nullptr) {
            throw runtime_error("Очередь пуста.");
        }
        return front->data;
    }

    // Проверка, пуста ли очередь
    bool isEmpty() const {
        return front == nullptr;
    }

    // Вывод содержимого очереди (для отладки)
    void print() const {
        if (front == nullptr) {
            cout << "Очередь пуста." << endl;
            return;
        }

        QueueNode<T>* temp = front;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};
