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
    int    current_time;      // Tempo que ele está na memoria
    int    max_quantum;       // Tempo máximo que um processo fica na memoria  
    bool   blocked = false;   // Tempo que o processo fica na memoria até atingir o maxquantum
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
    int check_time(int** ids, bool is_max_quantum);
    int  hashing_function(int key, int size);

    int  insert_memory(int value, string description, int size, int max_quantum, int time);
    int  search_position_memory(int size);
    int  add(MemoryContent memory_content, int position, int size);
    int  search_memory(int value); 
    int  remove_memory(int value, bool is_max_quantum); 


    int  get_segments();

    void print();
};


#endif