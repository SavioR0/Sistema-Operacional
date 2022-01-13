#include "../../include/hardware/cpu.hpp"

Cpu::Cpu(int cores){
    this->cores = cores;
    CpuProcess* assist = NULL;
    for (int i = 0; i < cores; i++){
        assist =  (CpuProcess*) malloc(sizeof(CpuProcess));
        (*assist).description = NULL;
        (*assist).quantum     = 0;
        (*assist).timesamp    = 0; 
        this->process.push_back(*assist);
        free(assist);
    }
    /* cout<<"Criados"; */
}

void Cpu::print(){
    int count = 0;
    /* for(CpuProcess item : this->process){
        cout << "\n\n Core: " << count << endl;
        cout << "\tTimestamp: " << item.timesamp << endl;
        cout << "\tQuantum: " << item.quantum << endl;
        if(item.description == NULL)
            cout << "\tDescricao: none" << endl;
        else
            cout << "\tDescricao: " << *item.description << endl;

        count++;

    } */
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
}