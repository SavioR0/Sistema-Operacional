#include "../../include/hardware/cpu.hpp"



Cpu::Cpu(int cores, Memory*  memoryRef, Storage* storageRef){
    this->cores      = cores;
    this->memoryRef  = memoryRef;
    this->storageRef = storageRef;
}

void Cpu::loadProcess(){
    json processJson;
    ifstream(processFile) >> processJson;
    CpuProcess* assist = NULL;

    for (int i = 0; i < (int) processJson["Itens"].size(); i++){
        assist =  new CpuProcess;

        assist->id         = (int)    processJson["Itens"][i]["id"];
        assist->cycles     = (int)    processJson["Itens"][i]["ciclos"];
        assist->maxQuantum = (int)    processJson["Itens"][i]["max_quantum"];
        assist->timesamp   = (int)    processJson["Itens"][i]["timestamp"];
        assist->priority   = (int)    processJson["Itens"][i]["prioridade"];
        assist->type       = (string) processJson["Itens"][i]["init_type"];
        assist->status     = "Pronto";

        this->process.push_back(*assist);
        free(assist);
    }
    cout << "\n\n\tProcessos carregados com sucesso e prontos para execucao." <<endl;
    cout << "\t Para mais informacoes digite o comando: queueschell" <<endl;


}

void Cpu::print(){

    
    /*cout<< this->process.size() << endl;
    for(CpuProcess item : this->process){
        cout << "\nID: "         << item.id;
        cout << "\nCiclos: "     << item.cycles;
        cout << "\nMaxQuantum: " << item.maxQuantum;
        cout << "\nTimeStamp: "  << item.timesamp;

    }*/

    /*int count = 0;
    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<<"  +    CORE\t|   TIMESTAMP\t|   QUANTUM\t|     DESCRIÇÃO   \t+"<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;
    for(CpuProcess item : this->process){

        cout<<"  +\t"<<count<<"\t|\t"<<item.timesamp<<"\t|\t"<<item.quantum<<"\t|\t";
        if(item.description ==NULL)
            cout<<"\t\t+"<<endl;
        else
            cout<<"\t"<<*item.description<<"\t+"<<endl;
        count++;
    }
    cout<<"----------------------------------------------------------------------------"<<endl;
*/}

void Cpu::printProcess(){
    cout<<"--------------------------------------------------"<<endl;
    cout<<" +\t\t      LIST PROCESS\t\t+"<<endl;
    cout<<"--------------------------------------------------"<<endl;
    if(!this->process.empty()){
        cout<<" +  ID\t|     Estado\t|\t   Tipo\t\t+"<<endl;
        cout<<"--------------------------------------------------"<<endl;
        for(CpuProcess item : this->process){
            cout<<" +   "<<item.id<<"\t|  "<<item.status<<"\t|\t"<<item.type<<"\t+"<<endl;
        }
    }else {
        cout<< " +\t\t\tEMPTY\t\t\t+"<<endl;
    }
    cout<<" --------------------------------------------------"<<endl;
}