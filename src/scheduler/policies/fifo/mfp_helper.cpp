#include "fifo.hpp"

int random_number_mfp_helper(int max){
    return rand()%max + 1;
}
void add_assist_maxquantum_value(list<Process>* list){
    for(int i = 0; i < (int)list->size(); i++  ){
        list->front().assist = list->front().get_max_quantum();
        list->push_back(list->front());
        list->pop_front(); 
    }
}

void FIFO::check_block_list_mfp(){
    if(this->block.empty()) return;

    int* ids;
    int size_ids;
    size_ids = this->memory_ref->check_time(&ids);
    if(size_ids > 0 )
    for(int i = 0; i < size_ids; i++){ 
        for(int j = 0; j < (int)this->block.size(); j++){
            if(!block.empty()){
                if(ids[i] == this->block.front().get_id()){
                        if(this->block.front().assist <= 0){
                            this->block.front().set_cycles(this->block.front().get_cyles() - 1);
                            this->block.front().set_status_finished();
                            this->finalized.push_back( this->block.front() );
                            this->block.pop_front();    
                        }else{
                            this->block.front().set_status_ready();
                            this->processes.push_back( this->block.front() );
                            this->block.pop_front();
                        }

                }else{
                        Process* assist = new Process;
                        *assist = this->block.front();
                        this->block.push_back(*assist);
                        this->block.pop_front();
                        free(assist);
                }
            }
            
        }
        this->memory_ref->remove_memory(ids[i]);
    }
    free(ids);      
    
    int* ids1;
    size_ids = this->storage_ref->check_time(&ids1);
    for(int i = 0; i < size_ids; i++){ 
        for(int j = 0; j < (int)this->block.size(); j++){
            if(!block.empty()){
                if(ids1[i] == this->block.front().get_id()){
                        if(this->block.front().assist <= 0){
                            this->block.front().set_cycles(this->block.front().get_cyles() - 1);
                            this->block.front().set_status_finished();
                            this->finalized.push_back( this->block.front() );
                            this->block.pop_front();    
                        }else{
                            this->block.front().set_status_ready();
                            this->processes.push_back( this->block.front() );
                            this->block.pop_front();
                        }

                    }else{
                        Process* assist = new Process;
                        *assist = this->block.front();
                        this->block.push_back(*assist);
                        this->block.pop_front();
                        free(assist);
                    }
            }
            
        }
        this->storage_ref->remove_storage(ids1[i]);
    }
    free(ids1);
}

void FIFO::check_finished_mfp(Process* current_process, int* quantum){
    if(current_process == NULL) return;
    if(current_process->assist <= 0){
        current_process->set_cycles( current_process->get_cyles() -1 );
        current_process->set_status_finished();
        this->finalized.push_back(*current_process);
        current_process = NULL;
        this->processes.pop_front();
        *quantum = 1;  
    }

}

list<Process> FIFO::execute_processes_mfp(){
    if(this->processes.empty()){
        cout << "\n\n Nao ha processos para serem executados.\n Tente o comando 'load' para carregar processos para a lista de execucao." << endl;
        return this->finalized;
    }

    add_assist_maxquantum_value(&this->processes);

    Process* current_process      = &(this->processes.front());
    int      size_list_process    = (int) this->processes.size();
    int      quantum              = 0;
    bool     await                = false;

    do{

        if(current_process != NULL){ 
            if(quantum <= 0){
                quantum = random_number_mfp_helper( current_process->assist );
                current_process->assist--;
            }

            if(current_process->get_status() == status_ready && await == false){
                await = true;
                if     (current_process->get_type() == "cpu-bound"   ) executing_process_cpu    (current_process);
                else if(current_process->get_type() == "memory-bound") executing_process_memory (current_process);
                else if(current_process->get_type() == "io-bound"    ) executing_process_storage(current_process);

            }
        }
        this->memory_ref->add_time_memory();
        this->storage_ref->add_time_storage();

        this->update_timestamp(&current_process);
        this->check_block_list_mfp();

        this->check_finished_mfp(current_process, &quantum);
        
        quantum--;
        
        if(quantum == 0){
            await = false;
            this->check_process_in_pogress(current_process);
            if(this->processes.empty()) current_process = NULL;
            else                        current_process = &this->processes.front();
        }
        usleep( (quantum_time * 1000000) );
        
    }while( (int) this->finalized.size()  < size_list_process);

    return this->finalized;
}

void FIFO::report_fifo(){
    cout<<"   ------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"   |\t\t\t\t\t    LISTA DE PROCESSOS    \t\t\t\t\t|"<<endl;
    cout<<"   ------------------------------------------------------------------------------------------------------"<<endl;
    if(!this->processes.empty() || !this->block.empty() || !this->finalized.empty()){
        cout<<"   |\tID\t|\tEstado\t\t|\t  Tipo     \t|\tTimestamp\t|\tCiclos\t|"<<endl;
        cout<<"   ------------------------------------------------------------------------------------------------------"<<endl;
        for(Process item : this->processes){
            cout<<"   |\t" << item.get_id() << "\t|\t" << item.get_status() << "    \t|\t"<< item.get_type() <<"\t|\t    " << item.get_timestamp() << "    \t|\t" << item.get_cyles() << "\t|" << endl;
        }
        for(Process item : this->block){
            cout<<"   |\t" << item.get_id() << "\t|\t" << item.get_status() << "    \t|\t"<< item.get_type() <<"\t|\t    " << item.get_timestamp() << "    \t|\t" << item.get_cyles() << "\t|" << endl;
        }
        for(Process item : this->finalized){
            cout<<"   |\t" << item.get_id() << "\t|\t" << item.get_status() << "    \t|\t"<< item.get_type() <<"\t|\t    " << item.get_timestamp() << "    \t|\t" << "--" << "\t|" << endl;
        }
    }else {
        cout<< " +\t\t\tEMPTY\t\t\t+"<<endl;
    }
    cout<<"   ------------------------------------------------------------------------------------------------------"<<endl;
}