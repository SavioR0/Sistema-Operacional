#include "mfp.hpp"
void print_tokens(const std::list<Process> list);

void Mfp::execute_based_on_mfp(){
    if(this->super_low_priority_process.empty()){
        std::cout<<"Erro[44]-> Não há processos a serem executados."<<std::endl;
        return;
    }

    int current_quantum = 0;
    std::list<Process>::iterator current_process;
    int initial_size_list_process = (int) this->super_low_priority_process.size();

    do{
        if(current_quantum <= 0){
            generate_tokens();
            distribute_tokens();
            /*print_tokens(this->super_low_priority_process);
            std::cout<<"\n\nTokens avaliables: " ;
            for(int x : this->tokens_available) std::cout<<"[" << x << "]  " ;*/
            raffle(current_process);
            recover_tokens(current_process);
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


void print_tokens(const std::list<Process> list){
     std::cout<<std::endl;
    for(Process teste : list){
        std::cout<<"\nProcesso " << teste.get_id() << ": ";
        std::vector<int> tokens = teste.get_and_remove_tokens();
        for(int x : tokens) std::cout<<"[" << x << "]  " ;
    }
     std::cout<<std::endl;


}