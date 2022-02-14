#include "scheduler.hpp"

void update_timestamp_in_list(std::list<Process>& list){
    for(std::list<Process>::iterator iter = list.begin(); iter != list.end(); iter++ )
        iter->add_timestamp();
}
void Scheduler::update_timestamp(){
    if( !this->high_priority_process.empty()     ) update_timestamp_in_list(this->high_priority_process);
    if( !this->medium_priority_process.empty()   ) update_timestamp_in_list(this->medium_priority_process);
    if( !this->low_priority_process.empty()      ) update_timestamp_in_list(this->low_priority_process);
    if( !this->super_low_priority_process.empty()) update_timestamp_in_list(this->super_low_priority_process);
}

void Scheduler::add_time(){
    this->update_timestamp();
    this->memory_ref->add_current_time_memory();
    this->storage_ref->add_current_time_storage();
}