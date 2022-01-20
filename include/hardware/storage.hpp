#ifndef __STORAGE_HPP__
#define __STORAGE_HPP__

#include <iostream>
#include <list>

using namespace std;

typedef struct BlockData BlockData;
struct BlockData{
    int    key;
    string type;

    int  time;
    int  current_time;
    bool alocated = false;
};

class Storage{
    private:
        int             size_blocks;      // Número de Blocos totais
        int             allocated_blocks; // Blocos alocados
        list<BlockData> blocks;           // Conteúdo e gerência de blocos  

    public:

        Storage(int size);

        int check_time(int** ids);
        void add_time_storage();

        void insert_block_data(int key, string type, int random_number);
        int  insert_storage(BlockData* block_data);
        int  remove_storage(int id);
        
        void print();
};


#endif