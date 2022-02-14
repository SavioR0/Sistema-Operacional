#include "storage.hpp"

Storage::Storage(int blocks_size):size_blocks(blocks_size), allocated_blocks(0){
    for(int i = 0; i < blocks_size; i++)
        this->blocks.push_back( ContentData() );
}


void Storage::insert_process (std::list<Process>::iterator iterator){
    if(allocated_blocks == size_blocks){
        std::cout<<"Erro [012] -> Não foi possível adicionar pois não há espaço suficiente" << std::endl;
        return;
    }
    ContentData data = Hadware::convert_iterator_to_contentData(iterator);
    for(std::list<Hadware::ContentData>::iterator iter = this->blocks.begin(); iter != this->blocks.end(); iter++){
        if(iter->alocated) continue;
        *iter = data;
        this->allocated_blocks++;
        return;
    }
}

void Storage::remove_process (int id){
    if(this->allocated_blocks == 0){ 
        std::cout<<"Erro [0112] -> O contúdo não pôde ser removido pois não existe, ou não está alocado" << std::endl;
        return;
    }
    for(std::list<ContentData>::iterator iter = this->blocks.begin(); iter != this->blocks.end(); iter++){
        if(iter->id != id) continue;
        *iter = ContentData();
        this->allocated_blocks--;
        return;
    }
    std::cout<<"Erro [0112] -> O contúdo não pôde ser removido pois não existe, ou não está alocado" << std::endl;
}

void Storage::remove_ready_process(){
    if(this->allocated_blocks == 0) return;
    for(std::list<ContentData>::iterator iter = this->blocks.begin(); iter != this->blocks.end(); iter++ ){
        if(!iter->alocated) continue;
        if(iter->current_time < iter->time) continue;

        *iter = ContentData(); 
        this->allocated_blocks--;
    }
}

void Storage::add_current_time_storage(){
    if(this->allocated_blocks <= 0) return;
    for(std::list<ContentData>::iterator iter = this->blocks.begin(); iter != this->blocks.end(); iter++)
        if(iter->alocated)
            iter->current_time++;
}
