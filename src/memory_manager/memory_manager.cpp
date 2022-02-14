#include "memory_manager.hpp"

void MemoryManager::insert_process_in_memory(std::list<Process>::iterator iterator){
    int initial_position_to_allocate = memory_ref->check_avaliable_size(iterator->get_segments());
    if(initial_position_to_allocate == -1){
        procees_pending.push_back( Data_assist(iterator)  );
        return;
    } 
    memory_ref->position_to_alloc = initial_position_to_allocate;
    memory_ref->insert_process(iterator);
}
void MemoryManager::check_pending_processes(){
    if(this->procees_pending.empty()) return;
    int initial_position_to_allocate;
    for(std::vector<Data_assist>::iterator vector_iter = this->procees_pending.begin(); vector_iter != this->procees_pending.end(); vector_iter++){
        initial_position_to_allocate = memory_ref->check_avaliable_size(vector_iter->iterator->get_segments());
        if(initial_position_to_allocate != -1){
            memory_ref->insert_process(vector_iter->iterator);
            this->procees_pending.erase(vector_iter--);
            continue;
        }
        vector_iter->chances--;
        if(vector_iter->chances > 0 ) continue;

        *(vector_iter->iterator) = Process(-1);
        std::cout<<"Processo descartado"<<std::endl;
    }
}