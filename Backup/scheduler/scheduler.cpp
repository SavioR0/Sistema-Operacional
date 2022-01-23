#include "scheduler.hpp"

//Construtores
Scheduler::Scheduler(Kernel* kernel, float quantum_time){ this->kernel_ref = kernel; this->quantum_time = quantum_time;}
Scheduler::Scheduler(){}

//Gerencia do PC (program counter)
int  Scheduler::get_pc(){ return this->pc; }
void Scheduler::add_pc(){ this->pc++;      }

//Funções auxiliares
int random_number(int max){
    srand(2);
    return rand()%max + 1;
}
Memory*   Scheduler::get_memory_ref() {return this->kernel_ref->memory;  } 
Storage*  Scheduler::get_storage_ref(){return this->kernel_ref->storage; }

//Leitura do arquivo de Processos
void Scheduler::read_processes(){
    json process_json;
    ifstream(process_file) >> process_json;
    Process* assist = NULL;
    
    for (int i = 0; i < (int) process_json[json_list_name].size(); i++){
        
        assist = new Process(
            (int)    process_json[json_list_name][i]["id"],
            (float)  process_json[json_list_name][i]["ciclos"],
            (int)    process_json[json_list_name][i]["max_quantum"],
            (int)    process_json[json_list_name][i]["timestamp"],
            (int)    process_json[json_list_name][i]["prioridade"],
            (string) process_json[json_list_name][i]["init_type"]
        );

        this->processes.push_back(*assist);
        free(assist);
    }
    cout<<"\n\n\t Todos os processos foram carregados e estão prontos para serem executados."<<endl;
    cout<<"\t Para ver a lista de processos digite o comando: queueschell."<<endl;
    cout<<"\t Para executar a lista de processos digite o comando: execute."<<endl;

}

void restart_processes_list(list<Process>* processes, int size){
    if((*processes).empty()) return;
    for(int i=0; i < size; i++)(*processes).pop_front();
}

void restart_block_list(list<Process>* block, int size){
    if((*block).empty()) return;
    for(int i=0; i < size; i++)(*block).pop_front();
}

void restart_finalized_list(list<Process>* finalized, int size){
    if((*finalized).empty()) return;
    for(int i=0; i < size; i++)(*finalized).pop_front();
}

void Scheduler::restart_system(){
    if(this->processes.size()==15 &&
        this->block.size()==0 && this->finalized.size()==0){
            cout<<"\t\t\tSistema já foi reiniciado!"<<endl;
            return;
        }
    restart_processes_list(&this->processes, this->processes.size());
    restart_block_list(&this->block, this->block.size());
    restart_finalized_list(&this->finalized,this->finalized.size() );
    cout<<"\t\t\tPROCESSOS REINICIADOS!"<<endl;
    read_processes();
}

//Funções de gerenciamento
void Scheduler::check_block_list(){
    if(this->block.empty()) return;


    int* ids;
    int size_ids;
    size_ids = this->get_memory_ref()->check_time(&ids);
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
        this->get_memory_ref()->remove_memory(ids[i]);
    }

    free(ids);      
    int* ids1;
    size_ids = this->get_storage_ref()->check_time(&ids1);
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
        this->get_storage_ref()->remove_storage(ids1[i]);
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
    Process aux;
    int size_list_process    = (int) this->processes.size();
    int last_process         = (int) this->processes.back().get_id();
    int quantum              = 0;
    bool await               = false;

    fifo();
    do{

        add_pc();
         
        if(quantum <= 0 && current_process != NULL ){
            quantum = random_number( current_process->get_max_quantum());
            current_process->sub_quantum(quantum);
        }
         
        if(current_process != NULL && current_process->get_status() == status_ready && await == false){
            await = true;
            if     (current_process->get_type() == "cpu-bound"   ) executing_process_cpu    (current_process);
            else if(current_process->get_type() == "memory-bound") executing_process_memory (&current_process, &last_process);
            else if(current_process->get_type() == "io-bound"    ) executing_process_storage(&current_process, &last_process);
            
        }
        this->get_memory_ref()->add_time_memory();
        this->get_storage_ref()->add_time_storage();

        this->update_timestamp(&current_process);
        this->check_block_list();


        if(current_process != NULL)
        if(check_finished()){
            current_process->set_status_finished();
            this->finalized.push_back(*current_process);
            current_process = NULL;
            this->processes.pop_front();
            if(last_process == this->finalized.back().get_id() && processes.size()!=0){
                last_process = this->processes.back().get_id();
                if((int)processes.size()>2) fifo();
            }
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
                    if(last_process == current_process->get_id() && (int)processes.size() > 2){
                        fifo();
                        last_process = (*current_process).get_id();
                    }
                }
            if(this->processes.empty()) current_process = NULL;
            else                        current_process = &this->processes.front();
        
        }
        usleep( (quantum_time * 1000000) );
        
    }while( (int) this->finalized.size()  < size_list_process);

}

void Scheduler::executing_process_cpu(Process* current_process){
    current_process->set_status_await();
    this->kernel_ref->cpu->set_process( current_process );
}

void Scheduler::executing_process_memory(Process** current_process, int* last_process){
    (*current_process)->set_status_block();
    this->get_memory_ref()->insert_memory(
        (*current_process)->get_id(),
        (*current_process)->get_type(),
        random_number(4)
    );
    this->block.push_back( *(*current_process) );

    *current_process = NULL;
    this->processes.pop_front();
    if(!this->processes.empty()) {
        *current_process = &this->processes.front(); 
        
        if(this->block.back().get_id()== (*last_process))
            *last_process = (*current_process)->get_id();
    }

}

void Scheduler::executing_process_storage(Process** current_process, int* last_process){
    (*current_process)->set_status_block();
    this->get_storage_ref()->insert_block_data(
        (*current_process)->get_id(),
        (*current_process)->get_type(),
        random_number(4)
        
    );
    this->block.push_back( *(*current_process) );

    *current_process = NULL;
    this->processes.pop_front();
    if(!this->processes.empty()) {
        *current_process = &this->processes.front(); 
        if(this->block.back().get_id()== (*last_process))
            *last_process = (*current_process)->get_id();
    }
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




