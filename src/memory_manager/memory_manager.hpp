#pragma once
#include <iostream>
#include "../Process/process.hpp"
#include "../hardware/hardware.hpp"
#include "../hardware/memory/memory.hpp"
#include <list>
#include <vector>

struct Data_assist{
    std::list<Process>::iterator iterator;
    int chances;
    Data_assist(std::list<Process>::iterator iterator):iterator(iterator){chances = 3;}
};


class MemoryManager{
    private:
        Memory* memory_ref;
        std::vector<Data_assist> procees_pending;
    public:
        MemoryManager(Memory* memory_ref):memory_ref(memory_ref){};

        void insert_process_in_memory(std::list<Process>::iterator iterator);
        void check_pending_processes();

};