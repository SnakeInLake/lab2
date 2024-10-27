#pragma once
#include <string>
#include <iostream>


void initTable();
void setAdd(const std::string& value);
void setRemove(const std::string& value);
bool setContains(const std::string& value);
void setPrint();
void setSaveToFile(const std::string& fileName);
void setLoadFromFile(const std::string& fileName);