#include "../include/scheduler.hpp"
#include "../include/hardware/memory.hpp"

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
    srand(time(NULL));
    return rand()%max + 1;
}


void Scheduler::executingProcessCPU(){
    cout<<"Executando processo na CPU"<<endl;
    processes.front().getType()= "Em execucao";
    //TODO: adicionar na CPU
    processes.front().getType()= "Pronto"; 

}
void Scheduler::executingProcessMemory(){
    cout<<"Executando processo na memoria"<<endl;
    processes.front().getType()= "Bloqueado";
    //Adiiconar o numero aleatorio sorteado a cada um dos processos adicionados na lista 
    randomNumber(4);
    block.push_back(processes.front());

    //ADICIONANDO NA MEMORIA
    MemoryContent mc;
    mc.value = processes.front().getId();
    mc.description = processes.front().getType();

    kernelref->memory->insertMemory(mc);
}
void Scheduler::executingProcessStorage(){
    cout<<"Executando processo no disco"<<endl;
    processes.front().getType()= "Bloqueado";
    //TODO: adicionar na Memoria

}

void Scheduler::executeProcesses(){
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

        //SE FOR CPU-BOUND
        if(processes.front().getType() == "cpu-bound")
            executingProcessCPU();
        //SE FOR MEMORY-BOUND
        else if(processes.front().getType()  == "memory-bound")
            executingProcessMemory();
        //SE FOR IO-BOUND
        else if(processes.front().getType()  == "io-bound")
            executingProcessStorage();

        

        quantum--;
        if(quantum == 0){

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

