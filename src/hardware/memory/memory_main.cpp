#include "memory.hpp"

Memory::Memory(int segments):segments(segments){
    this->allocated_segments = 0;
    this->ram = new ContentData[segments];
}

int Memory::hashing_function(int key, int size){
    return (key & 0x7FFFFFFF) % size;
}

void Memory::insert_process (std::list<Process>::iterator iterator){
    if(allocated_segments == segments){ 
        std::cout<<"Erro[151] -> Não foi possível adicionar itens a Memória. Memória encontra-se lotada" << std::endl;
        return;
    }
    ContentData memory_data = Hadware::convert_iterator_to_contentData(iterator);

    int position_alocated = hashing_function(memory_data.id,  this->segments);
    ram[position_alocated] = memory_data;
    this->allocated_segments++;
}

void Memory::remove_process (int id){
    if(this->allocated_segments == 0){ 
        std::cout<<"Erro [0111] -> O contúdo não pôde ser removido pois não existe, ou não está alocado" << std::endl;
        return;
    }
    int position = hashing_function(id, this->segments);
    
    if(ram[position].alocated == false){ 
        std::cout<<"Erro [0111] -> O contúdo não pôde ser removido pois não existe, ou não está alocado" << std::endl;
        return;
    }
    ram[position] = ContentData(); 
    this->allocated_segments--;
}

void Memory::remove_ready_process(){
    if(this->allocated_segments == 0) return;
    for(int i = 0; i < this->segments; i++){
        if(!ram[i].alocated) continue;
        if(ram[i].current_time < ram[i].time) continue;

        ram[i] = ContentData();
        this->allocated_segments--;
    }
}

void Memory::add_current_time_memory(){
    if(this->allocated_segments <= 0) return;
    for(int i = 0; i < this->segments; i++)
        if(ram[i].alocated)
            ram[i].current_time++;
}
