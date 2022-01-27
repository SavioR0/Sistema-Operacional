#ifndef __LRU_POLICIES__HPP
#define __LRU_POLICIES__HPP

#include <list>

#include "../../../process/process.hpp"
#include "../../../hardware/cpu/cpu.hpp"
#include "../../../hardware/memory/memory.hpp"
#include "../../../hardware/storage/storage.hpp"
#include <unistd.h>



class LRU{
    private:
        list<Process> processes;
        list<Process> block;
        list<Process> finalized;
        Cpu*          cpu_ref;
        Memory*       memory_ref;
        Storage*      storage_ref;
        float quantum_time;
    
        void check_block_list();
        void check_finished(Process* current_process, int* quantum);
        void check_process_in_pogress(Process* current_process);
        void update_timestamp(Process** current_process);

        void executing_process_cpu    (Process* current_process);
        void executing_process_memory (Process* current_process);
        void executing_process_storage(Process* current_process);
        void sort_list(int* total_cycles);

    public:
        LRU();
        LRU(list<Process> list_process, Cpu* cpu_ref, Memory* memory_ref, Storage* storage_ref, float quantum_time);

        int  execute_processes(); 
        void restart();      
        void report();
};

#endif