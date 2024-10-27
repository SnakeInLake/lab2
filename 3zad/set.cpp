#include "set.h"
#include <fstream>
#include "HashTable.h"


void setAdd(const std::string& value) {
    insert(value, ""); 
}

void setRemove(const std::string& value) {
    remove(value);
}

bool setContains(const std::string& value) {
    return get(value) != "Ключ не найден";
}

void setPrint() {
    printTable();
}

void setSaveToFile(const std::string& fileName) {
    saveToFile(fileName);
}

void setLoadFromFile(const std::string& fileName) {
    loadFromFile(fileName);
}