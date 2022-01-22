#ifndef __Scheduler_HPP__
#define __Scheduler_HPP__

#include <iostream>
#include <list>
#include <fstream>
#include "json.hpp"
#include <string>
#include <time.h>
#include <unistd.h>
#include "process.hpp"
#include "kernel.hpp"

#define process_file    "processos.json"
#define quantum_time   2500 /* 250000  */             // 0.25 segundos (1s = 1.000.000)

#define status_ready   "Pronto"
#define status_blocked "Bloqueado"
#define status_running "Em execucao"

using json = nlohmann::json;
using namespace std;


class Scheduler{
    private:
        list<Process> processes;
        list<Process> block;
        list<Process> finalized;
        Kernel* kernel_ref;
        int pc = 0;

    public:
        Scheduler();
        Scheduler(Kernel* kernel);

        //politicas
        void fifo();
        void lru();
        void mfp();

        void add_pc();
        int  get_pc();

        Memory*  get_memory_ref();
        Storage* get_storage_ref();

        void read_processes();
        void restart_system();

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