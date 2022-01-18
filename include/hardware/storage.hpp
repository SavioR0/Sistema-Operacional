#ifndef __STORAGE_HPP__
#define __STORAGE_HPP__

#include <iostream>
#include <list>

using namespace std;

typedef struct BlockData BlockData;
struct BlockData{
    int key;
    string* type;

    int time;
};

class Storage{
    private:
    public:
        int size;
        int qtd;
        list<BlockData> blocks;

        Storage(int size);
        int insertStorage(BlockData bd);
        void print();
};


#endif