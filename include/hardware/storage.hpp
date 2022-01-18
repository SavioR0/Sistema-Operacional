#ifndef __STORAGE_HPP__
#define __STORAGE_HPP__

#include <iostream>
#include <list>

using namespace std;

typedef struct BlockData BlockData;
struct BlockData{
    int key;
    string type;

    int time;
    int currentTime;
    bool   alocated = false;
};

class Storage{
    private:
    public:
        int size;
        int qtd;
        list<BlockData> blocks;

        Storage(int size);
        int insertStorage(BlockData bd);
        int searchStorage(int id,BlockData* bd);
        int removeStorage(int id);
        void addTimeStorage();
        void print();
};


#endif