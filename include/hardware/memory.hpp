#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

typedef struct MemoryContent MemoryContent; 
struct MemoryContent{
    int    idContant;
    int    value;             // ID do processo
    string description;       // Tipo do processo
    int    time;              // Tempo máximo de castigo
    int    currentTime;       // Tempo que ele está na memoria
    bool   alocated = false;  // variável que define se está alocado ou não     
};


class Memory{
private:
    int            segments;
    int            allocated_amount; 
    MemoryContent* ram;
public:
    Memory(int segments);
    void print();
    void resetMemory();
    void addTimeMemory();
    int  hashingFunction(int key, int size);
    void insertMemory(int value, string description, int time);
    int  addHash(MemoryContent memory_content);
    int  searchMemory(int value, MemoryContent* mc); 
    int  removeMemory(int value); 
    int  check_time(int** ids);
    int  get_segments();
};


#endif