#include "array.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

void findSubarraysWithSum(DynamicArray& arr, int targetSum) {
    int n = arr.length();

    for (int i = 0; i < n; i++) {
        int currentSum = 0;
        DynamicArray currentSubarray;
        currentSubarray.init(10); // Инициализируем временный динамический массив

        for (int j = i; j < n; j++) {
            currentSum += stoi(arr.get(j)); 
            currentSubarray.add(arr.get(j)); 

            if (currentSum == targetSum) {
                cout << "Подмассив: ";
                currentSubarray.print(); 
            }
        }

        currentSubarray.destroy(); // Освобождаем память временного массива
    }
}



int main() {
    DynamicArray arr;
    arr.init(10);

    arr.add("4");
    arr.add("-7");
    arr.add("1");
    arr.add("5");
    arr.add("-4");
    arr.add("0");
    arr.add("-3");
    arr.add("2");
    arr.add("4");
    arr.add("1");

    int targetSum = 5;
    findSubarraysWithSum(arr, targetSum);

    arr.destroy(); 
    return 0;
}