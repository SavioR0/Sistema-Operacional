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
        int blocks_storage;
        int segments;
        int num_process;
    public:

    Cpu*     cpu;
    Storage* storage;
    Memory*  memory;

    Kernel();
    void initialize();
    
    void set_core(int number);
    void set_blocks_storage(int number);
    void set_segments(int number);
    void set_process(int number);

    int get_core();
    int get_blocks_storage();
    int get_segments();
    int get_process();

};

#endif