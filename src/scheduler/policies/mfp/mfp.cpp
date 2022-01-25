#include "mfp.hpp"

//contrutores
MFP::MFP(){}
MFP::MFP(list<Process> list_process, Cpu* cpu_ref, Memory* memory_ref, Storage* storage_ref, float quantum_time){
    this->processes   = list_process;
    this->cpu_ref     = cpu_ref;
    this->memory_ref  = memory_ref;
    this->storage_ref = storage_ref;
    this->quantum_time = quantum_time;
}

// Funções auxiliares
int random_number3(int max){
    srand(2);
    return rand()%max + 1;
}


//Funções de gerenciamento
void MFP::restart(){
    this->processes.clear();
    this->block.clear();
    this->finalized.clear();
    cout<<"\n\n\tProcessos reiniciados\n"<<endl;
}

void MFP::check_block_list(){
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



void MFP::check_finished(Process* current_process, int* quantum, int* last_process){
    if(current_process == NULL) return;
    
    if(current_process->get_cyles() <= 0){
        current_process->set_status_finished();
        this->finalized.push_back(*current_process);
        current_process = NULL;
        this->processes.pop_front();
        if(*last_process == this->finalized.back().get_id() && processes.size()!=0){
                *last_process = this->processes.back().get_id();
                if((int)processes.size()>2) aplly_policie();
        }
        *quantum = 1;  
    }

}

void MFP::check_process_in_pogress(Process* current_process, int *last_process){
    if(current_process == NULL) return;
    
    if( current_process->get_status() == status_await ){
        cpu_ref->remove_process();
        current_process->set_status_ready(); 
        this->processes.push_back(*current_process);                
        this->processes.pop_front();
        if(*last_process == current_process->get_id() && (int)processes.size() > 2){
            aplly_policie();
            *last_process = (*current_process).get_id();
        }
    }
}

void MFP::update_timestamp(Process** current_process){

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
int MFP::execute_processes(){
    if(this->processes.empty()){
        cout << "\n\n Nao ha processos para serem executados.\n Tente o comando 'load' para carregar processos para a lista de execucao." << endl;
        return 0;
    }
    int      size_list_process    = (int) this->processes.size();
    initialize_policie();

    Process* current_process = &(this->processes.front());
    
    int      last_process         = (int) this->processes.back().get_id();
    int      quantum              = 0;
    bool     await                = false;
    int      pc                   = 0;
  
    do{

        pc++;

        if(current_process != NULL){ 
            if(quantum <= 0){
                quantum = random_number3( current_process->get_max_quantum());
                current_process->sub_quantum(quantum);
            }

            if(current_process->get_status() == status_ready && await == false){
                await = true;
                if     (current_process->get_type() == "cpu-bound"   ) executing_process_cpu    (current_process);
                else if(current_process->get_type() == "memory-bound") executing_process_memory (current_process, &last_process);
                else if(current_process->get_type() == "io-bound"    ) executing_process_storage(current_process, &last_process);

            }
        }
        this->memory_ref->add_time_memory();
        this->storage_ref->add_time_storage();

        this->update_timestamp(&current_process);
        this->check_block_list();

        this->check_finished(current_process, &quantum, &last_process);
        
        quantum--;
        
        if(quantum == 0){
            await = false;
            this->check_process_in_pogress(current_process, &last_process);
            if(this->processes.empty()) current_process = NULL;
            else                        current_process = &this->processes.front();
        }
        usleep( (quantum_time * 1000000) );
        
    }while( (int) this->finalized.size()  < size_list_process);
    return pc;
}

void MFP::executing_process_cpu(Process* current_process){
    current_process->set_status_await();
    this->cpu_ref->set_process( current_process );
}

void MFP::executing_process_memory(Process* current_process, int* last_process){
    current_process->set_status_block();
    this->memory_ref->insert_memory(
        current_process->get_id(),
        current_process->get_type(),
        random_number3(4));

    this->block.push_back( (*current_process) );

    current_process = NULL;
    this->processes.pop_front();
    if(!this->processes.empty()) {
        current_process = &this->processes.front();
        if(this->block.back().get_id()== (*last_process))
            *last_process = current_process->get_id();
    } 
}

void MFP::executing_process_storage(Process* current_process, int* last_process){
    current_process->set_status_block();
    this->storage_ref->insert_block_data(
        current_process->get_id(),
        current_process->get_type(),
        random_number3(4));
    
    this->block.push_back( (*current_process) );

    current_process = NULL;
    this->processes.pop_front();
    if(!this->processes.empty()){
        current_process = &this->processes.front(); 
        if(this->block.back().get_id()== (*last_process))
            *last_process = current_process->get_id();
    } 
}


//Funções de exibição
void MFP::report(){
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