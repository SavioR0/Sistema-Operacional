#include "../include/scheduler.hpp"

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

int randomQuantum(int max_quantum){
    srand(time(NULL));
    return rand()%max_quantum + 1;
}


void executingProcessCPU(){}
void executingProcessMemory(){}
void executingProcessStorage(){}

/*void Scheduler::executeProcesses(){
    if(this->processes.empty()){
        cout << "\n\n Nao ha processos para serem executados.\n Tente o comando 'load' para carregar processos para a lista de execucao." << endl;
        return;
    }

    int size_list_process = this->processes.size();
    int quantum = 0;

    do{
        addPC();
        if(quantum == 0)
            quantum = randomQuantum(this->processes.front().maxQuantum);

        if(*((&processes.front())->type) == "cpu-bound"){
            *((&processes.front())->type) = "Em execucao";
            //TODO: adicionar na CPU

        }else if(*((&processes.front())->type)  == "memory-bound"){
            *((&processes.front())->type)= "Bloqueado";
            //TODO: adicionar na Memoria


        }else if(*((&processes.front())->type)  == "io-bound"){
            *((&processes.front())->type) = "Bloqueado";


        }

        quantum--;
        if(quantum == 0){

        }
        usleep(1000000);

    }while( finalized.size() != size_list_process );

}*/








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

