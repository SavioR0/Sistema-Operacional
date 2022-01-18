#ifndef __CPU_HPP__
#define __CPU_HPP__

#include <iostream>
#include "../process.hpp" 

using namespace std; 

class Cpu{
    private:
        int cores;
        Process* cpu_process      = NULL;
        Process* process_previous = NULL; 
    public:
        Cpu();
        Cpu(int cores);

        void    print();
        void    setProcess(Process* cpu_process);
        Process getProcessPrevious();
        Process getProcess();
};


#endif