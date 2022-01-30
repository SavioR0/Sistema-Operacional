#ifndef __MFP_POLICIES__HPP
#define __MFP_POLICIES__HPP

#include <list>

#include "../../../process/process.hpp"
#include "../../../hardware/cpu/cpu.hpp"
#include "../../../hardware/memory/memory.hpp"
#include "../../../hardware/storage/storage.hpp"
#include "../fifo/fifo.hpp"
#include <unistd.h>


class MFP{
    private:
        list<Process> block;
        list<Process> finalized;

        list<Process> priority1;
        list<Process> priority2;
        list<Process> priority3;
        list<Process> priority4;

        FIFO* fifo_policie = NULL;

        Cpu*          cpu_ref;
        Memory*       memory_ref;
        Storage*      storage_ref;
                
        float         quantum_time;

        void distribution_list(list<Process> processes);
    
    public:
        MFP();
        MFP(list<Process> list_process, Cpu* cpu_ref, Memory* memory_ref, Storage* storage_ref, float quantum_time);

        void report();


};

#endif