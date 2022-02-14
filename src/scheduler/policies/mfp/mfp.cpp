#include "mfp.hpp"

void Mfp::execute_based_on_fifo(std::list<Process>& current_list, std::list<Process>& next_list){
    if(current_list.empty()) return;
    
    std::list<Process>::iterator current_process = current_list.end();
    int current_quantum = 0;
    int size_list = (int) current_list.size();
    for(std::list<Process>::iterator iter = current_list.begin(); iter != current_list.end(); iter++)
        iter->assist = iter->get_max_quantum();

    do{
        if(current_quantum <= 0){
            current_process++;
            if(!this->continuity_test(current_process, current_quantum, current_list)){
                usleep(100000);
                continue;
            }
            if(current_process == current_list.end()) {std::cout<<"Erro crítico, iterator final lista."<<std::endl; exit(50);}
            current_quantum = this->radom_number(current_process->assist);
            if(current_quantum < 0) {std::cout<<"Erro crítico, quntum menor que 0."<<std::endl; exit(30);}
            current_process->assist -= current_quantum;
            current_process->sub_cycles(current_quantum);
        }



        if(current_process->get_status() == STATUS_READY)
            this->execute_process(current_process);
        
        this->add_time();
        this->check_remove_memory_storage();
        this->check_finished_process(current_process);
        usleep(100000);
        current_quantum--;


       if(current_quantum <= 0 && current_process != current_list.end()){
            this->check_remove_cpu(current_process);
            current_process->set_status_ready();
            if(current_process->assist == 0){
                current_process->sub_priority();
                next_list.push_back(*current_process);
                current_list.erase(current_process--);
                size_list--;
            }
            
        }
    }while(size_list > 0);
}

void Mfp::execute_list_processes(){
    execute_based_on_fifo(this->high_priority_process, this->medium_priority_process);    
    execute_based_on_fifo(this->medium_priority_process, this->low_priority_process);    
    execute_based_on_fifo(this->low_priority_process, this->super_low_priority_process); 
    execute_based_on_mfp();   
}