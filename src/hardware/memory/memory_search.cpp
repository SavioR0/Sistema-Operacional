#include "memory.hpp"

int Memory::check_avaliable_size(int size) const{
    if(size > this->segments) return -1;

    int current_position = 0, counter = 0;
    while (current_position < this->segments)
        if(ram[current_position].alocated == false){
            counter++;
            if(counter >= size )
                return current_position;
        }else{
            current_position ++;
            counter = 0;
        }
    return -1;
}

