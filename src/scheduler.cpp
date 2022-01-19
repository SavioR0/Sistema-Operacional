#include "../include/scheduler.hpp"

//Construtores
Scheduler::Scheduler(Kernel* kernel){ this->kernelref = kernel;}
Scheduler::Scheduler(){}

//Gerencia do PC (program counter)
int  Scheduler::getPC(){ return this->pc; }
void Scheduler::addPC(){ this->pc++;      }

//Funções auxiliares
int randomNumber(int max){
    srand(time(NULL));
    return rand()%max + 1;
}

//Leitura do arquivo de Processos
void Scheduler::read_processes(){
    json processJson;
    ifstream(processFile) >> processJson;
    Process* assist = NULL;
    
    for (int i = 0; i < (int) processJson["Itens"].size(); i++){
        
        assist = new Process(
            (int)    processJson["Itens"][i]["id"],
            (float)  processJson["Itens"][i]["ciclos"],
            (int)    processJson["Itens"][i]["max_quantum"],
            (int)    processJson["Itens"][i]["timestamp"],
            (int)    processJson["Itens"][i]["prioridade"],
            (string) processJson["Itens"][i]["init_type"]
        );

        this->processes.push_back(*assist);
        free(assist);
    }
    
}


//Funções de gerenciamento
void Scheduler::check_block_list(){
    if(this->block.empty()) return;


    int* ids;
    int size_ids;
    size_ids = this->kernelref->memory->check_time(&ids);
    if(size_ids > 0 )
    for(int i = 0; i < size_ids; i++){ 
        for(int j = 0; j < (int)this->block.size(); j++){
            if(!block.empty()){
                if(ids[i] == this->block.front().getId()){
                        if(this->block.front().getcyles() <= 0){
                            this->block.front().setStatus_finished();
                            this->finalized.push_back( this->block.front() );
                            this->block.pop_front();    
                        }else{
                            this->block.front().setStatus_ready();
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
        this->kernelref->memory->removeMemory(ids[i]);
    }
    free(ids);      
    int* ids1;
    size_ids = this->kernelref->storage->check_time(&ids1);
    for(int i = 0; i < size_ids; i++){ 
        for(int j = 0; j < (int)this->block.size(); j++){
            if(!block.empty()){
                if(ids1[i] == this->block.front().getId()){
                        if(this->block.front().getcyles() <= 0){
                            this->block.front().setStatus_finished();
                            this->finalized.push_back( this->block.front() );
                            this->block.pop_front();    
                        }else{
                            this->block.front().setStatus_ready();
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
        this->kernelref->storage->removeStorage(ids1[i]);
    }
    free(ids1);
}

bool Scheduler::check_finished(){
    if(this->processes.front().getcyles() <= 0) return true;
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
void Scheduler::executeProcesses(){
    if(this->processes.empty()){
        cout << "\n\n Nao ha processos para serem executados.\n Tente o comando 'load' para carregar processos para a lista de execucao." << endl;
        return;
    }

    Process* current_process = &(this->processes.front());
    int size_list_process    = (int) this->processes.size();
    int quantum              = 0;
    bool await = false;

    do{

        addPC();
         
        if(quantum <= 0 && current_process != NULL ){
            quantum = randomNumber( current_process->getMaxQuantum());
            current_process->sub_quantum(quantum);
        }
         
        if(current_process != NULL && current_process->getStatus() == status_ready && await == false){
            await = true;
            if     (current_process->getType() == "cpu-bound"   ) executingProcessCPU    (current_process); 
            else if(current_process->getType() == "memory-bound") executingProcessMemory (&current_process);
            else if(current_process->getType() == "io-bound"    ) executingProcessStorage(&current_process);
        }
        this->kernelref->memory->addTimeMemory();
        this->kernelref->storage->addTimeStorage();

        this->update_timestamp(&current_process);
        
        this->check_block_list();

        if(current_process != NULL)
        if(check_finished()){
            current_process->setStatus_finished();
            this->finalized.push_back(*current_process);
            current_process = NULL;
            this->processes.pop_front();
            quantum = 1;
        }
        
        quantum--;
        if(quantum == 0){  
            await = false;
            if(current_process != NULL)
            if( current_process->getStatus() == status_await ){
                current_process->setStatus_ready(); 
                this->processes.push_back(*current_process);                
                this->processes.pop_front();
                
            }
            if(this->processes.empty()) current_process = NULL;
            else                        current_process = &this->processes.front();
        
        }
        this->report(); 
        usleep(50000);
        

    }while( (int) this->finalized.size()  < size_list_process);

}

void Scheduler::executingProcessCPU(Process* current_process){
    current_process->setStatus_await();
    this->kernelref->cpu->setProcess( current_process );
}

void Scheduler::executingProcessMemory(Process** current_process){
    (*current_process)->setStatus_block();
    this->kernelref->memory->insertMemory(
        (*current_process)->getId(),
        (*current_process)->getType(),
        randomNumber(4)
    );
    this->block.push_back( *(*current_process) );

    *current_process = NULL;
    this->processes.pop_front();
    if(!this->processes.empty()) *current_process = &this->processes.front();

}

void Scheduler::executingProcessStorage(Process** current_process){
    (*current_process)->setStatus_block();
    this->kernelref->storage->insertBlockData(
        (*current_process)->getId(),
        (*current_process)->getType(),
        randomNumber(4)
        
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
            cout<<"   |\t" << item.getId() << "\t|\t" << item.getStatus() << "    \t|\t"<< item.getType() <<"\t|\t    " << item.getTimestamp() << "    \t|\t" << item.getcyles() << "\t|" << endl;
        }
        for(Process item : this->block){
            cout<<"   |\t" << item.getId() << "\t|\t" << item.getStatus() << "    \t|\t"<< item.getType() <<"\t|\t    " << item.getTimestamp() << "    \t|\t" << item.getcyles() << "\t|" << endl;
        }
        for(Process item : this->finalized){
            cout<<"   |\t" << item.getId() << "\t|\t" << item.getStatus() << "    \t|\t"<< item.getType() <<"\t|\t    " << item.getTimestamp() << "    \t|\t" << "--" << "\t|" << endl;
        }
    }else {
        cout<< " +\t\t\tEMPTY\t\t\t+"<<endl;
    }
    cout<<"   ------------------------------------------------------------------------------------------------------"<<endl;
}




