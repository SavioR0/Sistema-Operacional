#include "../../include/hardware/cpu.hpp"

Cpu::Cpu(){}
Cpu::Cpu(int cores){
    this->cores = cores;
}
void Cpu::setProcess(Process* cpu_process){
    this->process_previous = this->cpu_process;
    this->cpu_process = cpu_process;
}
Process  Cpu::getProcess(){return *(this->cpu_process);}
Process  Cpu::getProcessPrevious(){return *(this->process_previous);}


void Cpu::print(){
    cout<<"   --------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"   |\t\t\t\t\tINFORMACOES DE PROCESSAMENTO\t\t\t\t\t\t|"<< endl;
    cout<<"   --------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"   |\tCore\t|\tId_Process\t|\tMax_quantum\t|\tTimeStamp\t|\tEstado_cpu\t|"<<endl;
    cout<<"   --------------------------------------------------------------------------------------------------------------"<<endl;

    for(int i = 0; i<this->cores; i++){
        if(cpu_process == NULL)
            cout<<"   |\t["<<i+1<<"]\t| " << "\t    -    \t" << "|\t    -   \t" << "|\t    -   \t" << "|\tDisponivel\t|"<<endl;
        else
            cout<<"   |\t["<<i+1<<"]\t|\t    " << getProcess().getId() << "    \t|\t    "<<getProcess().getMaxQuantum()<<"    \t|\t    "<< getProcess().getTimestamp()<<"\t\t|\t  Em uso   \t|"<<endl;
    }
    cout<<"   --------------------------------------------------------------------------------------------------------------"<<endl;

    if(this->process_previous != NULL){
        cout<<"\n\n   --------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"   |\t\t\t\t\tHISTORICO ULTIMO PROCESSO\t\t\t\t\t\t|"<< endl;
        cout<<"   --------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"   |\tCore\t|\tId_Process\t|\tMax_quantum\t|\tTimeStamp\t|\tEstado_cpu\t|"<<endl;
        cout<<"   --------------------------------------------------------------------------------------------------------------"<<endl;

        for(int i = 0; i<this->cores; i++){
            if(cpu_process == NULL)
                cout<<"   |\t["<<i+1<<"]\t| " << "\t    -    \t" << "|\t    -   \t" << "|\t    -   \t" << "|\tDisponivel\t|"<<endl;
            else
                cout<<"   |\t["<<i+1<<"]\t|\t    " << getProcessPrevious().getId() << "    \t|\t    "<<getProcessPrevious().getMaxQuantum()<<"    \t|\t    "<< getProcessPrevious().getTimestamp()<<"\t\t|\t  Em uso   \t|"<<endl;
        }
        cout<<"   --------------------------------------------------------------------------------------------------------------"<<endl;
    }



}