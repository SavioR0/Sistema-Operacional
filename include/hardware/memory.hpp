#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

#include <iostream>
#include <string>

using namespace std;

typedef struct MemoryContent MemoryContent; 
struct MemoryContent{
    int    id_constant;
    int    value;             // ID do processo
    int    time;              // Tempo máximo de castigo
    int    current_time;       // Tempo que ele está na memoria
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

    void add_time_memory();
    void reset_memory();
    int  check_time(int** ids);
    int  hashing_function(int key, int size);

    int  insert_memory(int value, string description, int time);
    int  add_hash(MemoryContent memory_content);
    int  search_memory(int value, MemoryContent* mc); 
    int  remove_memory(int value); 


    int  get_segments();

    void print();
};


#endif