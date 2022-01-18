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
            (int)    processJson["Itens"][i]["ciclos"],
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

int randomNumber(int max){
    srand(0);
    return rand()%max + 1;
}


void Scheduler::executingProcessCPU(){
    processes.front().setStatus("Em Execucao");
    this->kernelref->cpu->setProcess( &this->processes.front() );
    //TODO: adicionar na CPU

}

void Scheduler::executingProcessMemory(){
    processes.front().setStatus("Bloqueado");


    MemoryContent memory_content; //ADICIONANDO NA MEMORIA
    memory_content.value       = this->processes.front().getId();
    memory_content.description = this->processes.front().getType();
    memory_content.currentTime = 0;

     
    memory_content.time = randomNumber(4); //Adicionar o numero aleatorio sorteado a cada um dos processos adicionados na lista

    this->kernelref->memory->insertMemory(memory_content);
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
        if(quantum == 0)
            quantum = randomNumber(this->processes.front().getMaxQuantum());

        
        if(processes.front().getStatus() == "Pronto"){
            //SE FOR CPU-BOUND
            if(processes.front().getType() == "cpu-bound")
                executingProcessCPU();
            //SE FOR MEMORY-BOUND
            else if(processes.front().getType()  == "memory-bound")
                executingProcessMemory();
            //SE FOR IO-BOUND
            else if(processes.front().getType()  == "io-bound")
                executingProcessStorage();
        }
        
        this->kernelref->memory->addTimeMemory();
        quantum--;
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

