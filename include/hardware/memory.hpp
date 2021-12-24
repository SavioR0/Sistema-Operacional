#ifndef __HASH_HPP__
#define __HASH_HPP__

#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

struct MemoryContent{
    int value;
    string description;
};


class Hash{
private:
    int seg;
    int qtd;
    MemoryContent *ram;
public:
    Hash(int segmentos);
    void printHash();
    void clearHash(int segmentos);
    //int insereHash(MemoryContent mc);
    //int buscaHash(int mat, MemoryContent mc); 
};


#endif