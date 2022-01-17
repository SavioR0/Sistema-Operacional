#include <fstream>
#include <iostream> 
#include "../include/settler.hpp"
#include "../include/json.hpp"
#include <chrono>
#include <unistd.h>

using json = nlohmann::json;

using namespace std::chrono;

Settler::Settler(int numProcess){
    json procs;
    string line;
    ifstream(File) >> procs;

    this->numProcesses = numProcess;

    json itens = procs["Itens"];
    //TODO: Fazer com numeros de processos diferentes
    //for(int i = 0; i< (procs["Itens"]).size(); i++){ 
    for(int i = 0; i< numProcess; i++){
        Process process;
        process.id          = procs["Itens"][i]["processo"];
        process.estado      = "Pronto";
        process.ciclos      = procs["Itens"][i]["ciclos"];
        process.maxQuantum  = procs["Itens"][i]["max_quantum"];
        process.initType    = procs["Itens"][i]["init_type"];
        process.timestamp   = procs["Itens"][i]["timestamp"];
        process.prioridade  = procs["Itens"][i]["prioridade"];
        /* printProcess(process); */
        processes.push(process);
        
    }
     printQueue();   
}

/* void Settler::printProcess(Process proc){
    cout<< "Id:" << proc.id <<"  Ciclos : " << proc.ciclos <<"  MaxQuantum: ";
    cout<<proc.maxQuantum<<"  initType: "<<proc.initType<< "  timesStamp: "<<proc.timestamp<<"  Prioridade: "<< proc.prioridade<<"\n"<<endl;
} */

void Settler::printQueue(){
    queue<Process> tempQueue;

    cout<<"--------------------------------------------------"<<endl;
    cout<<" +\t\t     QUEUE PROCESS\t\t+"<<endl;
    cout<<"--------------------------------------------------"<<endl;
    if(!processes.empty()){
        cout<<" +  ID\t|     STATE\t|\t   TYPE\t\t+"<<endl;
        cout<<"--------------------------------------------------"<<endl;
        while(!processes.empty()){
            cout<<" +   "<<processes.front().id<<"\t|  "<<processes.front().estado<<"\t|\t"<<processes.front().initType<<"\t+"<<endl;
            tempQueue.push(processes.front());
            processes.pop();
        }
        
        processes = tempQueue;
    }else {
        cout<< " +\t\t\tEMPTY\t\t\t+"<<endl;
    }
    cout<<" --------------------------------------------------"<<endl;
    
}

void Settler::executeQueue(){
    
    Process processExecuting; 

    int quantum;
    int pc = 0;
    int currentId=0;

    queue<Process> processesTemp;

    if(!processes.empty()){
        processExecuting = processes.front();
        cout<<processExecuting.maxQuantum<<endl;
        processExecuting.quantumCount = rand()%(processExecuting.maxQuantum)+1;
    }

    while(!processes.empty()){
        pc++;
        processExecuting.timestamp++;
        cout<<"ID:"<<processExecuting.id<< " PC:"<<pc<<" \tTimeStamp:"<<processExecuting.timestamp<<" \tCiclos: "<<processExecuting.ciclos<<endl;
        
        usleep(250000); //1 000 000 = 1 seconds
  
        // SE É CPU-BOUND 
        if(processes.front().initType == "cpu-bound" && currentId != processExecuting.id){
            currentId = processExecuting.id;
            processExecuting.estado = "Em execução";
            //TODO: adicionar na CPU
            
            /* cout<<"\t\t\tQuantum: "<<processExecuting.quantumCount<<endl; */

        // SE É MEMORY-BOUND
        }else if(processes.front().initType == "memory-bound" && currentId != processExecuting.id){
            currentId = processExecuting.id;
            processExecuting.quantumCount=1;
            //TODO: adicionar na Memoria
            processExecuting.estado = "Bloqueado";
            //TODO: aplicar penalidade de numero de ciclos 

        // SE É io-BOUND    
        }else if(processes.front().initType == "io-bound" && currentId != processExecuting.id){
            currentId = processExecuting.id;
            processExecuting.quantumCount=1;
            //TODO: adicionar no disco
            processExecuting.estado = "Bloqueado";
            //TODO: aplicar penalidade de numero de ciclos 
        }
        processExecuting.quantumCount--;

        if(processExecuting.quantumCount == 0 ){
            //processExecuting.estado!="Bloqueado" é apenas um teste pra que eu possa enxergar o funcionamento o cpu-bound
            if(processExecuting.estado!="Bloqueado" && processExecuting.timestamp <= processExecuting.ciclos){
                    processesTemp.push(processExecuting);
                }
                
            processes.pop();


            //SE A FILA ESTIVER VAZIA, CRIAR NOVO CICLO
            if(processes.empty()){
                /* processes = processesTemp; */
                if(!processesTemp.empty()){
                    while(!processesTemp.empty()){
                        processes.push(processesTemp.front());
                        processesTemp.pop();
                    }
                    cout<<endl;
                    /* return; */
                }else
                    return;
            }
            
            processExecuting = processes.front();
            //Sorteia o MaxQuantum
            quantum = rand()%(processExecuting.maxQuantum)+1;
            processExecuting.quantumCount = quantum;
        }
    }
}