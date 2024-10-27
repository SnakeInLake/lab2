#include <iostream>
#include <string>
#include "array.h"

using namespace std;

const int BLOOM_FILTER_SIZE = 20;
const int NUM_HASH_FUNCTIONS = 2;

struct BloomFilter {
    DynamicArray bitArray; 
};
// Хеш-функции
int hash1(const string& key) {
    int hash = 0;
    for (int i = 0; i < key.length(); i++) {
        hash = (hash * 31 + key[i]) % BLOOM_FILTER_SIZE;
    }
    return hash;
}

int hash2(const string& key) {
    int hash = 5381;
    for (int i = 0; i < key.length(); i++) {
        hash = ((hash << 5) + hash) + key[i]; 
    }
    return hash % BLOOM_FILTER_SIZE;
}
int hash3(const string& key) {
    unsigned int hash = 0;
    for (int i = 0; i < key.length(); i++) {
        hash = (hash ^ key[i]) * 16777619; // XOR и умножение на простое число
    }
    return hash % BLOOM_FILTER_SIZE;
}
// ... (реализовать остальные хэш-функции)

int hashFunction(const string& key, int i) {
    switch (i) {
        case 0: return hash1(key);
        case 1: return hash2(key);
        case 2: return hash3(key);
        default: return 0; 
    }
}

void bloomFilterInit(BloomFilter& bf) {
    bf.bitArray.init(BLOOM_FILTER_SIZE);
    // Инициализируем битовый массив нулями
    for (int i = 0; i < BLOOM_FILTER_SIZE; i++) {
        bf.bitArray.add("0"); 
    }
}

// Функция для добавления элемента в фильтр Блума
void bloomFilterAdd(BloomFilter& bf, const string& key) {
    for (int i = 0; i < NUM_HASH_FUNCTIONS; i++) {
        int index = hashFunction(key, i);
        bf.bitArray.set(index, "1"); 
    }
}

// Функция для проверки наличия элемента в фильтре Блума
bool bloomFilterMightContain(const BloomFilter& bf, const string& key) {
    for (int i = 0; i < NUM_HASH_FUNCTIONS; i++) {
        int index = hashFunction(key, i);
        if (bf.bitArray.get(index) == "0") { 
            return false; // Точно не присутствует
        }
    }
    return true; // Может присутствовать
}


int main() {
    BloomFilter bloomFilter; // Создаем фильтр Блума
    bloomFilterInit(bloomFilter); // Инициализируем фильтр

    bloomFilterAdd(bloomFilter, "apple");
    bloomFilterAdd(bloomFilter, "banana");
    cout<<"Ключ к apple: "<<hash1("apple")<<endl; 
    cout<<"Ключ к apple 2: "<<hash2("apple")<<endl; 


    cout << "Содержит ли 'apple'? " << bloomFilterMightContain(bloomFilter, "apple") << endl; // true
    cout << "Содержит ли 'grape'? " << bloomFilterMightContain(bloomFilter, "grape") << endl;  // false (может быть true, если произошла коллизия)

    bloomFilter.bitArray.print(); // Выводим битовый массив

    return 0;
}