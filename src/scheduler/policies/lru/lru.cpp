#include "lru.hpp"

void Lru::sort_list(int& total_cycles){
    if(this->super_low_priority_process.empty()) return;

    this->super_low_priority_process.sort([](Process p1, Process p2) {
        return p1.get_cycles() < p2.get_cycles();
    });
    total_cycles = (int) this->super_low_priority_process.size();
}

void Lru::execute_list_processes(){
    if(this->super_low_priority_process.empty()){
        std::cout<<"Erro[44] -> Não há processos para serem executados, tente o comando 'load' para carregar processos." << std::endl;
        return;
    }
    std::list<Process>::iterator current_process = this->super_low_priority_process.end();
    int current_quantum = 0;
    int total_cycles = (int) this->super_low_priority_process.size();
    int initial_size_list_process = (int) this->super_low_priority_process.size();
    sort_list(total_cycles);


    do{

        if(current_quantum <= 0){
            if(total_cycles == 0){
                current_process = this->super_low_priority_process.end();
                sort_list(total_cycles);
            }
            total_cycles--;
            current_process++;
            if(!this->continuity_test(current_process, current_quantum, this->super_low_priority_process)){
                usleep(this->kernel_ref->get_quantum_time());
                continue;
            }
            
            current_quantum = this->radom_number(current_process->get_max_quantum());
            current_process->sub_cycles(current_quantum);
        }

        if(current_process->get_status() == STATUS_READY)
            this->execute_process(current_process);
        
        this->add_time();
        this->check_remove_memory_storage();
        this->check_finished_process(current_process);

        usleep(this->kernel_ref->get_quantum_time());
        current_quantum--;

       if(current_quantum <= 0 && current_process != this->super_low_priority_process.end()){
            this->check_remove_cpu(current_process);
            current_process->set_status_ready();
        }
    }while((int) this->finalized.size() < initial_size_list_process);

} 