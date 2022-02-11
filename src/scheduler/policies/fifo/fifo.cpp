#include "fifo.hpp"

//contrutores
FIFO::FIFO(){}
FIFO::FIFO(list<Process> list_process, Cpu* cpu_ref, Memory* memory_ref, Storage* storage_ref, float quantum_time){
    this->processes   = list_process;
    this->cpu_ref     = cpu_ref;
    this->memory_ref  = memory_ref;
    this->storage_ref = storage_ref;
    this->quantum_time = quantum_time;
}

// Funções auxiliares
int random_number(int max){
    return rand()%max + 1;
}


//Funções de gerenciamento
void FIFO::restart(){
    this->processes.clear();
    this->block.clear();
    this->finalized.clear();
    cout<<"\n\n\tProcessos reiniciados\n"<<endl;
}

void FIFO::check_block_list(){
    if(this->block.empty()) return;

    int* ids;
    int size_ids;
    size_ids = this->memory_ref->check_time(&ids);
    if(size_ids > 0 )
    for(int i = 0; i < size_ids; i++){ 
        for(int j = 0; j < (int)this->block.size(); j++){
            if(!block.empty()){
                if(ids[i] == this->block.front().get_id()){
                        if(this->block.front().get_cyles() <= 0){
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
                        if(this->block.front().get_cyles() <= 0){
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

void FIFO::check_finished(Process* current_process, int* quantum){
    if(current_process == NULL) return;
    
    if(current_process->get_cyles() <= 0){
        current_process->set_status_finished();
        this->finalized.push_back(*current_process);
        current_process = NULL;
        this->processes.pop_front();
        *quantum = 1;  
    }

}

void FIFO::check_process_in_pogress(Process* current_process){
    if(current_process == NULL) return;
    
    if( current_process->get_status() == status_await ){
        cpu_ref->remove_process();
        current_process->set_status_ready(); 
        this->processes.push_back(*current_process);                
        this->processes.pop_front();
    }
}

void FIFO::update_timestamp(Process** current_process){

    if(!this->processes.empty()) 
    for(int i = 0; i < (int) this->processes.size(); i++){
        this->processes.front().add_timestamp();
        this->processes.push_back(  this->processes.front()  );
        this->processes.pop_front();
    }

    if(!this->block.empty())
    for(int i = 0; i < (int) this->block.size(); i++){
        this->block.front().add_timestamp();
        this->block.push_back(  this->block.front()  );
        this->block.pop_front();
    }

    if(!this->processes.empty())(*current_process) = &this->processes.front();
    else (*current_process) = NULL;
}

//Funções de execução
int FIFO::execute_processes(){
    if(this->processes.empty()){
        cout << "\n\n Nao ha processos para serem executados.\n Tente o comando 'load' para carregar processos para a lista de execucao." << endl;
        return 0;
    }

    Process* current_process = &(this->processes.front());
    int      size_list_process    = (int) this->processes.size();
    int      quantum              = 0;
    bool     await                = false;
    int      pc                   = 0;

    do{

        pc++;

        if(current_process != NULL){ 
            if(quantum <= 0){
                quantum = random_number( current_process->get_max_quantum());
                current_process->sub_quantum(quantum);
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
        this->check_block_list();

        this->check_finished(current_process, &quantum);
        
        quantum--;
        
        if(quantum == 0){
            await = false;
            this->check_process_in_pogress(current_process);
            if(this->processes.empty()) current_process = NULL;
            else                        current_process = &this->processes.front();
        }
        usleep( (quantum_time * 1000000) );
        
    }while( (int) this->finalized.size()  < size_list_process);
    return pc;
}

void FIFO::executing_process_cpu(Process* current_process){
    current_process->set_status_await();
    this->cpu_ref->set_process( current_process );
}

void FIFO::executing_process_memory(Process* current_process){
    current_process->set_status_block();
    this->memory_ref->insert_memory(
        current_process->get_id(),
        current_process->get_type(),
        current_process->get_size(),
        random_number(4));

    this->block.push_back( (*current_process) );

    current_process = NULL;
    this->processes.pop_front();
    if(!this->processes.empty()) current_process = &this->processes.front(); 
    
}

void FIFO::executing_process_storage(Process* current_process){
    current_process->set_status_block();
    this->storage_ref->insert_block_data(
        current_process->get_id(),
        current_process->get_type(),
        random_number(4));
    
    this->block.push_back( (*current_process) );

    current_process = NULL;
    this->processes.pop_front();
    if(!this->processes.empty()) current_process = &this->processes.front(); 
    
}


//Funções de exibição
void FIFO::report(){
    system("clear");
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