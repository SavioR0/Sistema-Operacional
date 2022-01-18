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

#define processFile    "processos.json"
#define status_ready   "Pronto"
#define status_blocked "Bloaquado"
#define status_running "Em execucao"

using json = nlohmann::json;
using namespace std;


class Scheduler{
    private:
        list<Process> processes;
        list<Process> block;
        list<Process> finalized;
        int pc = 0;
    public:
        Kernel* kernelref;
        Scheduler();
        Scheduler(Kernel* kernel);

        void addPC();
        int  getPC();

        void read_processes();

        void check_block_list();
        bool check_finished();
        void update_timestamp();

        void executeProcesses();
        void executingProcessCPU();
        void executingProcessMemory();
        void executingProcessStorage();

        void report();
};

#endif