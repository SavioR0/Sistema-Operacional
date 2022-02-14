#pragma once
#include <iostream>
#include <string>
#include "../kernel/kernel.hpp"
#include "../hardware/cpu/cpu.hpp"
#include "../hardware/memory/memory.hpp"
#include "../hardware/storage/storage.hpp"
#include "../scheduler/scheduler.hpp"

class Shell{
    private:
        Kernel* kernel_ref;
        Scheduler* scheduler_ref;
        bool    ignore = true;
        int     selected_option = -5;
        Cpu*    cpu_ref;
        Memory* memory_ref;
        Storage* storage_ref;

    public:
        Shell(Kernel* kernel_ref, Scheduler* scheduler_ref):kernel_ref(kernel_ref), scheduler_ref(scheduler_ref){}
        int get_selected_option() const {return this->selected_option;} 
        void start_os();       // Função que inicializa os comandos do Sistema
        void select_option();

    private:        
        void help_command();   // Função que especifica os comandos disponíveis
        void message_exit();
        void init_ref();



};

