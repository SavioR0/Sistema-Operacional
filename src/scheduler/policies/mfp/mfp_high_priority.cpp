#include "mfp.hpp"


void check_finished_after_fifo(list<Process>* current_list, list<Process>* finalized){
    int size = (int) current_list->size();

    for( int i = 0; i < size; i++){
        Process* assist = new Process();
        *assist = current_list->front();
        if(assist->get_cyles() <= 0){
            finalized->push_back(*assist );
            assist = NULL;
        }
        if(assist != NULL) current_list->push_back(*assist);
        current_list->pop_front();
        free(assist);
    }

}

void reorder_lists(list<Process>* current_list, list<Process>* next_list ){
    int size = (int) current_list->size();
    for(int i = 0; i < size ; i++){
        current_list->front().set_status_ready();
        current_list->front().set_priority( current_list->front().get_priority() -1 );
        next_list->push_back(current_list->front());
        current_list->pop_front();
    }
}

void MFP::update_timestamp_after_fifo(int time){
    int assist;
    assist = (int) this->priority4.size();
    for(int i = 0; i < assist; i++){
        this->priority4.front().set_timestamp(time);
        this->priority4.push_back(this->priority4.front());
        this->priority4.pop_front();
    }
    assist = (int) this->priority3.size();
    for(int i = 0; i < assist; i++){
        this->priority3.front().set_timestamp(time);
        this->priority3.push_back(this->priority3.front());
        this->priority3.pop_front();
    }
    assist = (int) this->priority2.size();
    for(int i = 0; i < assist; i++){
        this->priority2.front().set_timestamp(time);
        this->priority2.push_back(this->priority2.front());
        this->priority2.pop_front();
    }
    assist = (int) this->priority1.size();
    for(int i = 0; i < assist; i++){
        this->priority1.front().set_timestamp(time);
        this->priority1.push_back(this->priority1.front());
        this->priority1.pop_front();
    }
}

void MFP::after_fifo(list<Process>* current_list, list<Process>* next_list){
    check_finished_after_fifo(current_list, &this->finalized);
    update_timestamp_after_fifo(current_list->back().get_timestamp());
    reorder_lists(current_list, next_list);
}

void MFP::execute_high_priority(){
   fifo_policie = new FIFO(this->priority4, this->cpu_ref, this->memory_ref, this->storage_ref, this->quantum_time); 
   this->priority4 = fifo_policie->execute_processes_mfp();
   this->after_fifo(&this->priority4, &this->priority3);
   free(fifo_policie);
   fifo_policie = new FIFO(this->priority3, this->cpu_ref, this->memory_ref, this->storage_ref, this->quantum_time); 
   this->priority3 = fifo_policie->execute_processes_mfp();
   this->after_fifo(&this->priority3, &this->priority2);
   free(fifo_policie);
    fifo_policie = new FIFO(this->priority2, this->cpu_ref, this->memory_ref, this->storage_ref, this->quantum_time); 
   this->priority2 = fifo_policie->execute_processes_mfp();
   this->after_fifo(&this->priority2, &this->priority1);
   free(fifo_policie);
   fifo_policie = NULL;
    cpu_ref->remove_process();
}
