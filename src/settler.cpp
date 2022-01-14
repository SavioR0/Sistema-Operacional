#include <fstream>
#include <iostream> 
#include "../include/settler.hpp"
#include "../include/json.hpp"

using json = nlohmann::json;

Settler::Settler(){
    json procs;
    string line;
    ifstream(File) >> procs;

    json itens = procs["Itens"];
    //TODO: Fazer com numeros de processos diferentes
    //for(int i = 0; i< (procs["Itens"]).size(); i++){ 
    for(int i = 0; i< 15; i++){
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

void Settler::printProcess(Process proc){
    cout<< "Id:" << proc.id <<"  Ciclos : " << proc.ciclos <<"  MaxQuantum: ";
    cout<<proc.maxQuantum<<"  initType: "<<proc.initType<< "  timesStamp: "<<proc.timestamp<<"  Prioridade: "<< proc.prioridade<<"\n"<<endl;
}

void Settler::printQueue(){
    cout<<"--------------------------------------------------"<<endl;
    cout<<" +\t\t   QUEUE PROCESS\t\t+"<<endl;
    cout<<"--------------------------------------------------"<<endl;
    cout<<" +  ID\t|     STATE\t|\t   TYPE\t\t+"<<endl;
    cout<<"--------------------------------------------------"<<endl;
    while(!processes.empty()){
        cout<<" +   "<<processes.front().id<<"\t|     "<<processes.front().estado<<"\t|\t"<<processes.front().initType<<"\t+"<<endl;
        processes.pop();
    }
    cout<<" --------------------------------------------------"<<endl;
}
