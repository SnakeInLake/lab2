#pragma once

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct HashNode {
    string key;
    string value;
    HashNode* next;
};

const int TABLE_SIZE = 1000;

extern HashNode* hashTable[TABLE_SIZE]; // Объявляем массив как extern

// Объявления функций
void initTable();
int hashFunction(const string& key);
void insert(const string& key, const string& value);
string get(const string& key);
void remove(const string& key);
void printTable();
void saveToFile(const string& fileName);
void loadFromFile(const string& fileName);
void freeTable();
void runHashTable(int argc, char* argv[]);

// Функции для работы с множеством (используя хэш-таблицу)
void setAdd(const string& value);
void setRemove(const string& value);
bool setContains(const string& value);
void setPrint();
void setLoadFromFile(const string& fileName);
void setSaveToFile(const string& fileName); 