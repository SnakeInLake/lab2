#include <iostream>
#include <stdexcept>
#include "queue.h"  

using namespace std;

// Структура узла дерева
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

// Функции для работы с AVL-деревом
int height(Node* node) {
    return node ? node->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* createNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

Node* insert(Node* node, int key) {
    if (node == nullptr)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void printTree(Node* root, int space = 0) {
    if (root == nullptr) return;

    space += 5;

    printTree(root->right, space);

    cout << endl;
    for (int i = 5; i < space; i++)
        cout << " ";
    cout << root->key << "\n";

    printTree(root->left, space);
}

// Обход дерева "змейкой" с использованием собственной очереди
void zigzagTraversal(Node* root) {
    if (!root) return;

    // Собственная очередь для хранения узлов
    Queue<Node*> queue;
    queue.init();
    queue.enqueue(root);

    // Флаг для определения направления вывода
    bool leftToRight = true;

    while (!queue.isEmpty()) {
        int levelSize = 0;
        Queue<Node*> tempQueue;  // Временная очередь для текущего уровня
        tempQueue.init();

        // Подсчитываем количество узлов на уровне
        while (!queue.isEmpty()) {
            Node* node = queue.peek();
            queue.dequeue();
            tempQueue.enqueue(node);
            levelSize++;
        }

        // Выводим узлы в правильном порядке
        for (int i = 0; i < levelSize; ++i) {
            Node* node = tempQueue.peek();
            tempQueue.dequeue();

            if (leftToRight)
                cout << node->key << " ";
            else
                cout << node->key << " ";  // Для обратного порядка обработаем позже

            // Добавляем детей узла в очередь для следующего уровня
            if (node->left) queue.enqueue(node->left);
            if (node->right) queue.enqueue(node->right);
        }

        // Меняем направление обхода
        leftToRight = !leftToRight;

        cout << endl;  // Переход на новую строку для каждого уровня
    }
}

int main() {
    // Пример использования
    Node* root = nullptr;

    // Вставляем узлы в дерево
    root = insert(root, 22);
    root = insert(root, 19);
    root = insert(root, 57);
    root = insert(root, 7);
    root = insert(root, 16);
    root = insert(root, 43);
    root = insert(root, 51);

    // Печать дерева
    cout << "Дерево:" << endl;
    printTree(root);

    // Выполняем обход дерева змейкой
    cout << "\nОбход дерева змейкой:" << endl;
    zigzagTraversal(root);

    return 0;
}