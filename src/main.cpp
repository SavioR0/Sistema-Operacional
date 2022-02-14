#include <iostream>
#include <string>
#include <pthread.h>

#include "shell/shell.hpp"
#include "kernel/kernel.hpp"
#include "scheduler/scheduler.hpp"
#include "scheduler/policies/fifo/fifo.hpp"
#include "scheduler/policies/lru/lru.hpp"
#include "scheduler/policies/mfp/mfp.hpp"
#include "memory_manager/memory_manager.hpp"

using namespace std;

int main(){
    system("clear");
    Kernel* kernel                = new Kernel();
    MemoryManager* memory_manager = new MemoryManager(kernel->get_memory_ref());
    Scheduler* scheduler          = new Lru(kernel, memory_manager); 
    Shell*  shell                 = new Shell(kernel, scheduler);

    shell->start_os();
    return 0;
}