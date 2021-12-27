#ifndef __CPU_HPP__
#define __CPU_HPP__

#include <iostream>
#include <list>

using namespace std;

typedef struct CpuProcess CpuProcess;
struct CpuProcess{
    string* description;
    int core;
    int timesamp;
    int quantum;
};

class Cpu{
    private:
    public:
        list<CpuProcess> process;
        int cores;

        Cpu(int cores);
        void print();
};


#endif