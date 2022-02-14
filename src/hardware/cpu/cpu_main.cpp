#include "cpu.hpp"

Cpu::Cpu(int cores):size_cores(cores), history_process(Process(-1)){ 
    for(int i = 0; i < this->size_cores; i++)
        this->cores.push_back(Process(-1));
}

void Cpu::insert_process(std::list<Process>::iterator iterator){
    for(std::vector<Process>::iterator iter = this->cores.begin(); iter != this->cores.end(); iter++ ){
        if(iter->get_id() != -1 ) continue;
        *iter = *iterator;
        return;
    }
    std::cout<<"Erro[150] -> Não foi possível adicionar itens a cpu. Cpu encontra-se lotada" << std::endl;
}
void Cpu::remove_process(int id){
    for(std::vector<Process>::iterator iter = this->cores.begin(); iter != this->cores.end(); iter++ ){
        if(iter->get_id() != id) continue;
        history_process = *iter;
        *iter = Process(-1);
        return; 
    }
    std::cout<<"Erro[250] -> Item não encontrado para remoção na CPU" << std::endl;
}
void Cpu::remove_ready_process(){
    if(this->cores[0].get_id() == -1 ) return;
    this->cores[0] = Process(-1);
}
