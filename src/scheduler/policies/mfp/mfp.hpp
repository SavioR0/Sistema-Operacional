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
        vector<int>   tokens_available;
        vector<int>   tokens_surplus;
        int           range_tokens = 0;

        void distribution_list(list<Process> processes);
        void execute_high_priority();
        void after_fifo(list<Process>* current_list, list<Process>* next_list);
        void update_timestamp_after_fifo(int time);
        void execute_processes();
        void generate_token();
        void distribute_tokens();
        void draw_token();
        void recover_tokens(list<Process>::iterator list_iterator);
        void executing_process_cpu(Process* current_process);
        void executing_process_memory(Process* current_process);
        void executing_process_storage(Process* current_process);
        void update_timestamp(Process** current_process);
        void check_block_list();
        void check_finished(Process* current_process, int* quantum);
        void check_process_in_pogress(Process* current_process);
        list<Process>::iterator raffle();
    
    public:
        MFP();
        MFP(list<Process> list_process, Cpu* cpu_ref, Memory* memory_ref, Storage* storage_ref, float quantum_time);


        void execute();
        void report();
};

#endif