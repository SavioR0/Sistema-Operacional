#ifndef __CPU_HPP__
#define __CPU_HPP__

#include <iostream>
#include <list>
#include <fstream>
#include "../include/json.hpp"
#include "storage.hpp"
#include "memory.hpp"

#define processFile "processos.json"

using json = nlohmann::json;
using namespace std;

typedef struct CpuProcess CpuProcess;
struct CpuProcess{
    int     id;
    int     cycles;
    int     maxQuantum;
    int     timesamp;
    int     priority;
    string  status;
    string  type;
};

class Cpu{
    private:
        Memory*  memoryRef;
        Storage* storageRef;
    public:
        list<CpuProcess> process;
        int cores;

        Cpu(int cores, Memory*  memoryRef, Storage* storageRef);
        void print();
        void setProcess();
        void loadProcess();
        void printProcess();
};


#endif