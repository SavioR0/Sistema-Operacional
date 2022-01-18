#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

struct MemoryContent{
    int value;
    string description;
    int time;
    int currentTime;
};


class Memory{
private:
    int segments;
    int qtd;
    MemoryContent *ram;
public:
    Memory(int segmentos);
    void print();
    void clearMemory();
    void addTimeMemory();
    int  hashingFunction(int key, int size);
    int  insertMemory(MemoryContent mc);
    int  searchMemory(int mat, MemoryContent* mc); 
};


#endif