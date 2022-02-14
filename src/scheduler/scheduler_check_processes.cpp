#include "scheduler.hpp"

void Scheduler::check_remove_cpu(std::list<Process>::iterator iterator){
    if(iterator->get_status() != STATUS_AWAIT ) return;
    this->cpu_ref->remove_process(iterator->get_id());
}

void Scheduler::check_remove_memory_storage(){
    this->memory_ref->remove_ready_process();
    this->storage_ref->remove_ready_process();
}


void check_process_list_finalized(std::list<Process>& list, std::list<Process>& list_finalized, std::list<Process>::iterator& current_iterator ){
    if(list.size() == 1){
        if(list.front().get_cycles() > 0) return;
        current_iterator = list.end();
        list.begin()->set_status_finished();
        list_finalized.push_back(list.front());
        list.clear();
    }
    for(std::list<Process>::iterator iter = list.begin(); iter != list.end(); iter++){
        if(current_iterator == iter) continue;
        if(iter->get_cycles() > 0) continue;
        iter->set_status_finished();
        list_finalized.push_back(*iter);
        list.erase(iter--);
    }
}
void Scheduler::check_finished_process(std::list<Process>::iterator& current_iterator){
    if(!this->high_priority_process.empty()) 
        check_process_list_finalized(this->high_priority_process, this->finalized, current_iterator);
    if(!this->medium_priority_process.empty()) 
        check_process_list_finalized(this->medium_priority_process, this->finalized, current_iterator);
    if(!this->low_priority_process.empty()) 
        check_process_list_finalized(this->low_priority_process, this->finalized, current_iterator);
    if(!this->super_low_priority_process.empty()) 
        check_process_list_finalized(this->super_low_priority_process, this->finalized, current_iterator);

}
