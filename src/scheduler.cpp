#include "../include/scheduler.hpp"

//Construtores
Scheduler::Scheduler(Kernel* kernel){ this->kernel_ref = kernel;}
Scheduler::Scheduler(){}

//Gerencia do PC (program counter)
int  Scheduler::get_pc(){ return this->pc; }
void Scheduler::add_pc(){ this->pc++;      }

//Funções auxiliares
int random_number(int max){
    srand(time(NULL));
    return rand()%max + 1;
}

//Leitura do arquivo de Processos
void Scheduler::read_processes(){
    json process_json;
    ifstream(process_file) >> process_json;
    Process* assist = NULL;
    
    for (int i = 0; i < (int) process_json["Itens"].size(); i++){
        
        assist = new Process(
            (int)    process_json["Itens"][i]["id"],
            (float)  process_json["Itens"][i]["ciclos"],
            (int)    process_json["Itens"][i]["max_quantum"],
            (int)    process_json["Itens"][i]["timestamp"],
            (int)    process_json["Itens"][i]["prioridade"],
            (string) process_json["Itens"][i]["init_type"]
        );

        this->processes.push_back(*assist);
        free(assist);
        fifo();
    }
    
}
 
//Politicas
void Scheduler::fifo(){}

//Funções de gerenciamento
void Scheduler::check_block_list(){
    if(this->block.empty()) return;


    int* ids;
    int size_ids;
    size_ids = this->kernel_ref->memory->check_time(&ids);
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
        this->kernel_ref->memory->remove_memory(ids[i]);
    }

    free(ids);      
    int* ids1;
    size_ids = this->kernel_ref->storage->check_time(&ids1);
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
        this->kernel_ref->storage->remove_storage(ids1[i]);
    }
    free(ids1);
}

bool Scheduler::check_finished(){
    if(this->processes.front().get_cyles() <= 0) return true;
    else                                        return false;
}

void Scheduler::update_timestamp(Process** current_process){

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
void Scheduler::execute_processes(){
    if(this->processes.empty()){
        cout << "\n\n Nao ha processos para serem executados.\n Tente o comando 'load' para carregar processos para a lista de execucao." << endl;
        return;
    }

    Process* current_process = &(this->processes.front());
    int size_list_process    = (int) this->processes.size();
    int quantum              = 0;
    bool await = false;

    do{

        add_pc();
         
        if(quantum <= 0 && current_process != NULL ){
            quantum = random_number( current_process->get_max_quantum());
            current_process->sub_quantum(quantum);
        }
         
        if(current_process != NULL && current_process->get_status() == status_ready && await == false){
            await = true;
            if     (current_process->get_type() == "cpu-bound"   ) executing_process_cpu    (current_process); 
            else if(current_process->get_type() == "memory-bound") executing_process_memory (&current_process);
            else if(current_process->get_type() == "io-bound"    ) executing_process_storage(&current_process);
        }
        this->kernel_ref->memory->add_time_memory();
        this->kernel_ref->storage->add_time_storage();

        this->update_timestamp(&current_process);
        
        this->check_block_list();

        if(current_process != NULL)
        if(check_finished()){
            current_process->set_status_finished();
            this->finalized.push_back(*current_process);
            current_process = NULL;
            this->processes.pop_front();
            quantum = 1;
        }
        
        quantum--;
        if(quantum == 0){  
            await = false;
            if(current_process != NULL)
            if( current_process->get_status() == status_await ){
                current_process->set_status_ready(); 
                this->processes.push_back(*current_process);                
                this->processes.pop_front();
                
            }
            if(this->processes.empty()) current_process = NULL;
            else                        current_process = &this->processes.front();
        
        }
        /* this->report();  */
        usleep(quantum_time);
        
    }while( (int) this->finalized.size()  < size_list_process);

}

void Scheduler::executing_process_cpu(Process* current_process){
    current_process->set_status_await();
    this->kernel_ref->cpu->set_process( current_process );
}

void Scheduler::executing_process_memory(Process** current_process){
    (*current_process)->set_status_block();
    this->kernel_ref->memory->insert_memory(
        (*current_process)->get_id(),
        (*current_process)->get_type(),
        random_number(4)
    );
    this->block.push_back( *(*current_process) );

    *current_process = NULL;
    this->processes.pop_front();
    if(!this->processes.empty()) *current_process = &this->processes.front();

}

void Scheduler::executing_process_storage(Process** current_process){
    (*current_process)->set_status_block();
    this->kernel_ref->storage->insert_block_data(
        (*current_process)->get_id(),
        (*current_process)->get_type(),
        random_number(4)
        
    );
    this->block.push_back( *(*current_process) );

    *current_process = NULL;
    this->processes.pop_front();
    if(!this->processes.empty()) *current_process = &this->processes.front();
}


//Funções de relatórios
void Scheduler::report(){
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




