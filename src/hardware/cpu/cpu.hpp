#ifndef __CPU_HPP__
#define __CPU_HPP__

#include <iostream>
#include "../../process/process.hpp" 

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
        void    set_process(Process* cpu_process);
        void    remove_process();
        Process get_process_previous();
        Process get_process();
};


#endif