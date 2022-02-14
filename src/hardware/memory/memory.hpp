#pragma once
#include <iostream>
#include "../hardware.hpp"
#include <list>

class Memory :public Hadware{
    private:
        int segments;            // Segmentos
        int allocated_segments;  // Segmentos alocados
        ContentData* ram;        // Representação dos segmentos
    
    public:
        Memory(){}
        Memory(int segments);
        void insert_process (std::list<Process>::iterator iterator) override;
        void remove_process (int id)          override;
        void generate_report()          const override;   
        void remove_ready_process()           override;
        void add_current_time_memory();

   
    private:
        int  hashing_function(int key, int size);
        void print_list() const;
        void header_report() const;

};