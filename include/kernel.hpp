#ifndef __KERNEL_HPP__
#define __KERNEL_HPP__

#include <iostream>
#include <fstream>
#include "hardware/cpu.hpp"
#include "hardware/storage.hpp"
#include "hardware/memory.hpp"

#define FileName "hardware.json"


using namespace std;

class Kernel{
    private:
        int cores;
        int blocksStorage;
    public:

    Cpu*     cpu;
    Storage* storage;

    Kernel();
    void initialize();
    
    void setCore(int number);
    void setBlocksStorage(int number);

    int getCore();
    int getBlocksStorage();

};

#endif