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
    if(block.empty()) return;

    int* ids;
    int size_ids;
    size_ids = this->kernelref->memory->check_time(&ids);
    for(int i = 0; i < size_ids; i++)
        for(int j = 0; j < (int)this->block.size(); j++){
            if(!block.empty()){
                if(ids[i] == this->block.front().getId()){
                    this->block.front().setStatus("Pronto");
                    this->processes.push_back( this->block.front() );
                    this->block.pop_front();
                }else{
                    Process* assist = new Process;
                    *assist = this->block.front();
                    this->block.push_back(*assist);
                    this->block.pop_front();
                    free(assist);
                }
            }
        }
    free(ids);
    
    
    /*cout<<"\n\nEntrei na check_block_list" << endl;

    int* ids;
    int teste = 0;
    this->kernelref->memory->print();
    teste = this->kernelref->memory->check_time(&ids);
    cout<<"Galera pronta da memoria: " << teste << endl;
    cout<<"ids: ";
    for(int i = 0; i < teste; i++) cout << ids[i];
    cout<<endl;
    usleep(300000);*/




    /*if(block.front().getType() == "memory-bound"){
        MemoryContent memory_content;
        for( int i = 0; i < (int)this->block.size(); i++){

            this->kernelref->memory->searchMemory(this->block.front().getId(), &memory_content);
            if(memory_content.time == memory_content.currentTime){
                this->kernelref->memory->removeMemory(this->block.front().getId());
                block.front().setStatus("Pronto");
                processes.push_back(block.front());
                block.pop_front();
            }else{
                block.push_back(block.front());
                block.pop_front();
            }
        }

    }else{
        BlockData block_data;
        for( int i=0; i < (int)this->block.size(); i++){
            this->kernelref->storage->searchStorage(block.front().getId(),&block_data);
            if(block_data.time == block_data.currentTime){
                this->kernelref->storage->removeStorage(this->block.front().getId());

                block.front().setStatus("Pronto");
                processes.push_back(block.front());
                block.pop_front(); 
                
            }else{
                block.push_back(block.front());
                block.pop_front();
            }
        } 
    }*/


    //if(this->kernelref->memory->getRam())
    // if(this->block.front().getId() == this->kenelref->memory)
}

bool Scheduler::check_finished(){
    if(this->processes.front().getcyles() <= 0) return true;
    else                                        return false;
}

void Scheduler::update_timestamp(){
    Process* assist;
    for(int i = 0; i < (int) this->processes.size(); i++){
        assist = new Process;
        this->processes.front().add_timestamp();
        *assist = this->processes.front();
        this->processes.pop_front();
        this->processes.push_back(*assist);
        free(assist);
    }
}


//Funções de execução
void Scheduler::executeProcesses(){
    Process* current_process;
    Process assist;
    if(this->processes.empty()){
        cout << "\n\n Nao ha processos para serem executados.\n Tente o comando 'load' para carregar processos para a lista de execucao." << endl;
        return;
    }

    int size_list_process = (int) this->processes.size();
    int quantum = 0;

    do{
        addPC();

        if(quantum == 0 ){
            current_process = &(this->processes.front());
            quantum = randomNumber( current_process->getMaxQuantum());
            if(current_process->getType() == "cpu-bound" || current_process->getType() == "memory-bound"  ) current_process->sub_quantum(quantum);
        }
            
        if(current_process->getStatus() == "Pronto"){
            if     (current_process->getType() == "cpu-bound"   ) executingProcessCPU(); 
            else if(current_process->getType() == "memory-bound") executingProcessMemory();
            else if(current_process->getType() == "io-bound"    ) quantum = 1;  //executingProcessStorage();
        }
        
        this->kernelref->memory->addTimeMemory();
        //this->kernelref->storage->addTimeStorage();
        this->update_timestamp();

        
        this->check_block_list();


        if(check_finished()){
            this->finalized.push_back(*current_process);
            this->processes.pop_front();
            cout<<"\tFINALIZADOS: "<<(int)finalized.size()<<"id:" << this->finalized.back().getId()<< endl;
            current_process = &(this->processes.front());
            quantum = 1;
        }
        
        quantum--;
        if(quantum == 0){
    
            if( current_process->getStatus() == "Em Execucao" ){
                current_process->setStatus("Pronto"); 
                assist = *current_process;
                
                this->processes.pop_front();
                this->processes.push_back(assist);
                
            }else if(this->processes.front().getStatus() == "bloqueado"){
                this->block.push_back( *current_process );
                this->processes.pop_front();
            }
            else if(current_process->getType() == "io-bound") this->processes.pop_front();
        
        }
        usleep(1000000);

    }while( (int)finalized.size() - 4 != size_list_process);

}

void Scheduler::executingProcessCPU(){
    processes.front().setStatus("Em Execucao");
    this->kernelref->cpu->setProcess( &this->processes.front() );
}

void Scheduler::executingProcessMemory(){
    processes.front().setStatus("bloqueado");
    this->kernelref->memory->insertMemory(
        this->processes.front().getId(),
        this->processes.front().getType(),
        randomNumber(4)
    );
}

void Scheduler::executingProcessStorage(){
    processes.front().setStatus("Bloqueado");

    block.push_back(processes.front());
    
    //ADICIONANDO NO STORAGE
    BlockData bd;

    bd.key = this->processes.front().getId();
    bd.type = this->processes.front().getType();
    bd.alocated = true;
    bd.currentTime = 0;
    //Adicionar o numero aleatorio sorteado a cada um dos processos adicionados na lista 
    bd.time = randomNumber(4);
    kernelref->storage->insertStorage(bd);
    this->processes.pop_front();
}


//Funções de relatórios
void Scheduler::report(){
    cout<<"--------------------------------------------------"<<endl;
    cout<<" +\t\t      LIST PROCESS\t\t+"<<endl;
    cout<<"--------------------------------------------------"<<endl;
    if(!this->processes.empty()){
        cout<<" +  ID\t|     Estado\t|\t   Tipo\t\t+"<<endl;
        cout<<"--------------------------------------------------"<<endl;
        for(Process item : this->processes){
            cout<<" +   "<< item.getId() <<"\t|  "<< item.getStatus() <<"\t|\t"<< item.getType() <<"\t+"<<endl;
        }
    }else {
        cout<< " +\t\t\tEMPTY\t\t\t+"<<endl;
    }
    cout<<" --------------------------------------------------"<<endl;

    cout<<"--------------------------------------------------"<<endl;
    cout<<" +\t\t      LIST BLOCK\t\t+"<<endl;
    cout<<"--------------------------------------------------"<<endl;
    if(!this->block.empty()){
        cout<<" +  ID\t|     Estado\t|\t   Tipo\t\t+"<<endl;
        cout<<"--------------------------------------------------"<<endl;
        for(Process item : this->block){
            cout<<" +   "<< item.getId() <<"\t|  "<< item.getStatus() <<"\t|\t"<< item.getType() <<"\t+"<<endl;
        }
    }else {
        cout<< " +\t\t\tEMPTY\t\t\t+"<<endl;
    }
    cout<<" --------------------------------------------------"<<endl;
    kernelref->memory->print();

}




