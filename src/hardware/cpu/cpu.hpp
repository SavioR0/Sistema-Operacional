#pragma once
#include <iostream>
#include <vector>
#include "../hardware.hpp"
#include "../../Process/process.hpp"
#include <list>

class Cpu: public Hadware{
    private:
        int size_cores;
        std::vector<Process> cores;
        Process history_process;
    public:
        Cpu(){}
        Cpu(int cores);
        void insert_process (std::list<Process>::iterator iterator)   override;
        void remove_process (int id)            override;
        void generate_report()          const   override;
        void remove_ready_process() override;
    private:
        void print_list() const;
        void header_report() const;
        
};