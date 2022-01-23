#ifndef __Scheduler_HPP__
#define __Scheduler_HPP__

#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <time.h>
#include <unistd.h>
#include "../process/process.hpp"
#include "../kernel/kernel.hpp"
#include "../../lib/json.hpp"
#include "policies/fifo/fifo.hpp"

#define process_file    "processos.json"

#define status_ready   "Pronto"
#define status_blocked "Bloqueado"
#define status_running "Em execucao"
#define json_list_name "all"

using json = nlohmann::json;
using namespace std;


class Scheduler{
    private:
        Kernel* kernel_ref;
        string policie;
        int pc = 0;
        float quantum_time;
        FIFO fifo_policie;

        list<Process> read_processes();

    
    public:
        Scheduler();
        Scheduler(Kernel* kernel, float quantum_time, string policie);

        void load();
        void execute();
        void report();

};

#endif