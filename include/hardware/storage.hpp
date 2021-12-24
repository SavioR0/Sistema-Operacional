#ifndef __STORAGE_HPP__
#define __STORAGE_HPP__

#include <iostream>
#include <list>

using namespace std;

typedef struct BlockData BlockData;
struct BlockData{
    int key;
    string* value;
};

class Storage{
    private:
    public:
        int size;
        list<BlockData> blocks;

        void initialize(int size);
        void print();
};


#endif