#ifndef __FIFO_POLICIES__HPP
#define __FIFO_POLICIES__HPP

#include <list>

#include "../../../process/process.hpp"
#include "../../../hardware/cpu/cpu.hpp"
#include "../../../hardware/memory/memory.hpp"
#include "../../../hardware/storage/storage.hpp"
#include <unistd.h>



class FIFO{
    private:
        list<Process> processes;
        list<Process> block;
        list<Process> finalized;
        Cpu*          cpu_ref;
        Memory*       memory_ref;
        Storage*      storage_ref;
        float quantum_time;
    
    public:
        FIFO();
        FIFO(list<Process> list_process, Cpu* cpu_ref, Memory* memory_ref, Storage* storage_ref, float quantum_time);

        void check_block_list();
        bool check_finished();
        void update_timestamp(Process** current_process);

        void execute_processes();
        void executing_process_cpu(Process* current_process);
        void executing_process_memory(Process** current_process, int* last_process);
        void executing_process_storage(Process** current_process, int* last_process);

        void report();
};

#endif