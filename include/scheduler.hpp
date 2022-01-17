#include <iostream>
#include <list>
#include <fstream>
#include "json.hpp"
#include <string>
#include <time.h>
#include <unistd.h>
#include "process.hpp"
#include "kernel.hpp"

#define processFile "processos.json"

using json = nlohmann::json;
using namespace std;

typedef struct Process Process;

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
        int getPC();
        void read_processes();
        void executeProcesses();
        void report();
};