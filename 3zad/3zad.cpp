#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "HashTable.h" 
#include "DualLinkedList.h"
#include <string.h>
#include <cmath> 
#include "set.h"

using namespace std;

// Структура для хранения информации о подмножестве
struct SubsetInfo {
    int sum;
    DualLinkedList elements;
};

// Функция для разбиения множества на два подмножества с минимальной разницей сумм
void partitionSetMinDiff(SubsetInfo& subset1, SubsetInfo& subset2) {
    int totalSum = 0;
    int n = 0;

    // Вычисляем общую сумму элементов множества и количество элементов
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* current = hashTable[i];
        while (current != nullptr) {
            totalSum += stoi(current->key);
            n++;
            current = current->next;
        }
    }
    
    subset1.elements.init();
    subset2.elements.init();
    subset1.sum = 0;
    subset2.sum = 0;
    
    int minDiff = 2147483647;
    
    // Перебираем все возможные комбинации битовой маски
    for (int mask = 0; mask < (1 << n); ++mask) {
        SubsetInfo currentSubset1, currentSubset2;
        currentSubset1.elements.init();
        currentSubset2.elements.init();
        currentSubset1.sum = 0;
        currentSubset2.sum = 0;

        int k = 0; // Индекс элемента в множестве
        
        // Проходим по хэш-таблице, чтобы получить элементы множества
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode* current = hashTable[i];
            while (current != nullptr) {
                // Если k-й бит в маске установлен, добавляем элемент в первое подмножество
                // иначе во второе
                if ((mask >> k) & 1) {
                    currentSubset1.sum += stoi(current->key);
                    currentSubset1.elements.addToTail(current->key);
                } else {
                    currentSubset2.sum += stoi(current->key);
                    currentSubset2.elements.addToTail(current->key);
                }
                k++;
                current = current->next;
            }
        }

        int diff = abs(currentSubset1.sum - currentSubset2.sum);

        // Обновляем минимальную разницу и соответствующие подмножества
        if (diff < minDiff) {
            minDiff = diff;
            subset1 = currentSubset1;
            subset2 = currentSubset2;
        }
    }
}


int main() {
    initTable();

    setAdd("1");
    setAdd("2");
    setAdd("3");
    setAdd("4");
    setAdd("5");
    setAdd("6");
    setAdd("7");
    setAdd("8");

    SubsetInfo subset1, subset2;
    partitionSetMinDiff(subset1, subset2); 

    cout << "Подмножество 1: ";
    subset1.elements.print();

    cout << "Подмножество 2: ";
    subset2.elements.print();

    cout << "Разница сумм: " << abs(subset1.sum - subset2.sum) << endl;

    freeTable();
}