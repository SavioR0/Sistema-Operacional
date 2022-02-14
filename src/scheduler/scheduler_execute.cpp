#include "scheduler.hpp"

int Scheduler::radom_number(int max) const{return rand()%max + 1;}


void Scheduler::execute_process(std::list<Process>::iterator iterator){

    if(iterator->get_type() == PROCESS_CPU){
        iterator->set_status_await();
        this->cpu_ref->insert_process(iterator);
        return;
    }

    int penalty_time = this->radom_number(4); //TODO: definir uma constante para o tempo máximo de castigo
    iterator->set_penalty_time(penalty_time); 
    iterator->set_status_block();
    
    if(iterator->get_type() == PROCESS_MEM) this->memory_ref->insert_process(iterator);
    else this->storage_ref->insert_process(iterator);
    

}
