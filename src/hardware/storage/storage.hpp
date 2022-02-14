#pragma once
#include <iostream>
#include "../hardware.hpp"
#include <list>

class Storage :public Hadware{
    private:
        int size_blocks;               // Segmentos
        int allocated_blocks;          // Segmentos alocados
        std::list<ContentData> blocks; // Representação dos segmentos
    
    public:
        Storage(){}
        Storage(int blocks_size);
        void insert_process (std::list<Process>::iterator iterator) override;
        void remove_process (int id)          override;
        void generate_report()          const override; 
        void remove_ready_process() override;    
        void add_current_time_storage();
   
    private:
        void print_list() const;
        void header_report() const;

};