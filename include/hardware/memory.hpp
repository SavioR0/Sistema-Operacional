#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

#include <iostream>
#include <string>

using namespace std;

typedef struct MemoryContent MemoryContent; 
struct MemoryContent{
    int    idContant;
    int    value;             // ID do processo
    int    time;              // Tempo máximo de castigo
    int    currentTime;       // Tempo que ele está na memoria
    bool   alocated = false;  // variável que define se está alocado ou não 
    string description;       // Tipo do processo
};


class Memory{
private:
    int            segments;            // Segmentos
    int            allocated_segments;  // Segmentos alocados
    MemoryContent* ram;
public:
    Memory(int segments);

    void addTimeMemory();
    void resetMemory();
    int  check_time(int** ids);
    int  hashingFunction(int key, int size);

    int  insertMemory(int value, string description, int time);
    int  addHash(MemoryContent memory_content);
    int  searchMemory(int value, MemoryContent* mc); 
    int  removeMemory(int value); 


    int  get_segments();

    void print();
};


#endif