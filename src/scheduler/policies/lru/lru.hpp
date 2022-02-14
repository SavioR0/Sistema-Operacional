#pragma once
#include <iostream>
#include "../../scheduler.hpp"
#include "../../../kernel/kernel.hpp"

class Lru : public Scheduler{
    public:
        Lru(Kernel* kernel_ref):Scheduler(kernel_ref, true){}
        void execute_list_processes() override;
    private:
        void sort_list(int& total_cycles);
};