#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

struct MemoryContent{
    int value;
    string description;
};


class Memory{
private:
    int segments;
    int qtd;
    MemoryContent *ram;
public:
    Memory(int segmentos);
    void print();
    void clearMemory(int segmentos);
    int  hashingFunction(int key, int size);
    int  insertMemory(MemoryContent mc);
    int  searchMemory(int mat, MemoryContent* mc); 
};


#endif