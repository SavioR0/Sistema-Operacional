#pragma once
#include <iostream>
#include "../../scheduler.hpp"
#include "../../../kernel/kernel.hpp"
#include <vector>

class Mfp : public Scheduler{
    private:
        std::vector<int> tokens_available; // Tokens disponíveis
        int range_tokens_avaliables;       // até qual número posso sortear


    public:
        Mfp(Kernel* kernel_ref):Scheduler(kernel_ref, false){this->range_tokens_avaliables = 1;}
        void execute_list_processes() override;
    private:
        void execute_based_on_fifo(std::list<Process>& current_list, std::list<Process>& next_list);
        void execute_based_on_mfp();
        void generate_tokens();
        void distribute_tokens();
        void raffle(std::list<Process>::iterator& iterator);
        bool contains_token(int token) const;
        void recover_tokens(std::list<Process>::iterator& iterator);
};