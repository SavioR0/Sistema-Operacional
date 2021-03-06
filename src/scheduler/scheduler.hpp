#pragma once

#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <time.h>
#include <unistd.h>

#include "../Process/process.hpp"
#include "../kernel/kernel.hpp"
#include "../../lib/json.hpp"
#include "../hardware/cpu/cpu.hpp"
#include "../hardware/memory/memory.hpp"
#include "../hardware/storage/storage.hpp"
#include "../memory_manager/memory_manager.hpp"

#define PROCESSES_FILE "processos.json"
#define LIST_NAME "all"


class Scheduler{
    protected:
        Kernel*        kernel_ref;
        Cpu*           cpu_ref;
        Memory*        memory_ref;
        Storage*       storage_ref;

        std::list<Process> high_priority_process;
        std::list<Process> medium_priority_process;
        std::list<Process> low_priority_process;
        std::list<Process> super_low_priority_process;

        std::list<Process> finalized;
        bool single_list;
        MemoryManager* memory_manager_ref;


    public:
        Scheduler(Kernel* kernel_ref, bool single_list, MemoryManager* memory_manager_ref);
        void load_list_processes();
        virtual void execute_list_processes() = 0;
        bool report_processes() const;
        void check_invalid_process(std::list<Process>& list, std::list<Process>::iterator& current_process );

    
    protected:
        bool continuity_test(std::list<Process>::iterator& iterator, int& current_quantum, std::list<Process>& list) ;
        int radom_number(int max) const;
        void execute_process(std::list<Process>::iterator iterator);
        void update_timestamp();
        void check_remove_cpu(std::list<Process>::iterator iterator);
        void check_remove_memory_storage();
        void check_finished_process(std::list<Process>::iterator& current_iterator);
        void add_time();
    
};

