#ifndef __CPU_HPP__
#define __CPU_HPP__

#include <iostream>
#include <list>
#include <fstream>
#include <time.h>
#include <unistd.h>
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
        int pc = 0;
    public:
        list<CpuProcess> process;
        int cores;

        Cpu(int cores, Memory*  memoryRef, Storage* storageRef);
        int  getPC();
        void addPC();
        void print();
        void setProcess();
        void loadProcess();
        void executeListProcess();
        void printProcess();
        void executeProcess();
};


#endif