#pragma once

#include <iostream>
using namespace std;

// Структура узла очереди
template <typename T>
struct QueueNode {
    T data;
    QueueNode* next;
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

        cout << "Элемент " << value << " добавлен в очередь." << endl;
    }

    // Удаление элемента из очереди (dequeue)
    void dequeue() {
        if (front == nullptr) {
            cerr << "Ошибка: Очередь пуста." << endl;
            return;
        }

        QueueNode<T>* temp = front;
        front = front->next;
        delete temp;

        if (front == nullptr) {
            rear = nullptr;
        }

        cout << "Элемент удален из очереди." << endl;
    }

    // Получение элемента из начала очереди (front) без удаления
    T peek() const {
        if (front == nullptr) {
            cerr << "Ошибка: Очередь пуста." << endl;
            return T();  // Возвращаем значение по умолчанию для типа T
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
