#include "../include/scheduler.hpp"

Scheduler::Scheduler(Kernel* kernel){
    this->kernelref = kernel;
}

Scheduler::Scheduler(){}

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

int  Scheduler::getPC(){ return this->pc; }
void Scheduler::addPC(){ this->pc++;      }

void Scheduler::update_timestamp(int value){
    Process assist;
    for(int i = 0; i < (int) this->processes.size(); i++){
        this->processes.front().setTimestamp(value);
        assist = this->processes.front();
        this->processes.pop_front();
        this->processes.push_back(assist);
    }
}


int randomNumber(int max){
    srand(0);
    return rand()%max + 1;
}


void Scheduler::executingProcessCPU(){
    processes.front().setStatus("Em Execucao");
    this->kernelref->cpu->setProcess( &this->processes.front() );
}

void Scheduler::executingProcessMemory(){
    processes.front().setStatus("Bloqueado");
    this->kernelref->memory->insertMemory(
        this->processes.front().getId(),
        this->processes.front().getType(),
        randomNumber(4)
    );
}

void Scheduler::executingProcessStorage(){
    processes.front().setStatus("Bloqueado");

    block.push_back(processes.front());
    this->processes.pop_front();

    //ADICIONANDO NO STORAGE
    BlockData bd;
    bd.key = this->processes.front().getId();
    bd.type = this->processes.front().getTypeAdress();
    //Adicionar o numero aleatorio sorteado a cada um dos processos adicionados na lista 
    bd.time = randomNumber(4);

    kernelref->storage->insertStorage(bd);

}


bool Scheduler::check_finished(){
    if(this->processes.front().getcyles() <= 0) return true;
    else                                        return false;
}

void Scheduler::check_block_list(){
    if(block.front().getType() == "memory-bound"){
        for( int i=0; i < (int)this->block.size(); i++){
            //this->kernelref->memory->get_position_ram
        }
    }else{

    }


    if(this->kernelref->memory->getRam())
     if(this->block.front().getId() == this->kenelref->memory)
}

void Scheduler::executeProcesses(){
    Process assist;
    if(this->processes.empty()){
        cout << "\n\n Nao ha processos para serem executados.\n Tente o comando 'load' para carregar processos para a lista de execucao." << endl;
        return;
    }

    int size_list_process = this->processes.size();
    int quantum = 0;

    do{
        addPC();
        if(quantum == 0){
            quantum = randomNumber(this->processes.front().getMaxQuantum());
            this->processes.front().sub_quantum(quantum);
        }

        
        if(processes.front().getStatus() == "Pronto"){

            if     (processes.front().getType() == "cpu-bound")    executingProcessCPU(); 
            else if(processes.front().getType() == "memory-bound") executingProcessMemory();
            else if(processes.front().getType() == "io-bound")     executingProcessStorage();
        }
        
        this->kernelref->memory->addTimeMemory();
        this->update_timestamp(getPC());

        quantum--;

        this->check_block_list();


        if(check_finished()){
            this->finalized.push_back(this->processes.front());
            this->processes.pop_front();
            quantum = 0;
        }
        
        
        if(quantum == 0){
            if( this->processes.front().getStatus() != "bloqueado"){
                this->processes.front().setStatus("Pronto"); 
                assist = this->processes.front();
                this->processes.pop_front();
                this->processes.push_back(assist);
            }else if(this->processes.front().getStatus() == "bloqueado"){
                this->block.push_back( this->processes.front() );
                this->processes.pop_front();
            }
        }
        
        
        usleep(1000000);

    }while( (int)finalized.size() != size_list_process );

}








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
}

