#pragma once
#include <iostream>
#include "../../scheduler.hpp"
#include "../../../kernel/kernel.hpp"

class Fifo : public Scheduler{
    public:
        Fifo(Kernel* kernel_ref):Scheduler(kernel_ref, true){}
        void execute_list_processes() override;
};