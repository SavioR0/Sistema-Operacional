#include "cpu.hpp"

Cpu::Cpu(){}
Cpu::Cpu(int cores){
    this->cores = cores;
}
void Cpu::set_process(Process* cpu_process){
    this->process_previous = this->cpu_process;
    this->cpu_process = cpu_process;
}
Process  Cpu::get_process(){return *(this->cpu_process);}
Process  Cpu::get_process_previous(){return *(this->process_previous);}


void Cpu::print(){
    system("clear");
    cout<<"   --------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"   |\t\t\t\t\tINFORMACOES DE PROCESSAMENTO\t\t\t\t\t\t|"<< endl;
    cout<<"   --------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"   |\tCore\t|\tId_Process\t|\tMax_quantum\t|\tTimeStamp\t|\tEstado_cpu\t|"<<endl;
    cout<<"   --------------------------------------------------------------------------------------------------------------"<<endl;

    for(int i = 0; i<this->cores; i++){
        if(cpu_process == NULL)
            cout<<"   |\t["<<i+1<<"]\t| " << "\t    -    \t" << "|\t    -   \t" << "|\t    -   \t" << "|\tDisponivel\t|"<<endl;
        else
            cout<<"   |\t["<<i+1<<"]\t|\t    " << get_process().get_id() << "    \t|\t    "<<get_process().get_max_quantum()<<"    \t|\t    "<< get_process().get_timestamp()<<"\t\t|\t  Em uso   \t|"<<endl;
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
                cout<<"   |\t["<<i+1<<"]\t|\t    " << get_process_previous().get_id() << "    \t|\t    "<<get_process_previous().get_max_quantum()<<"    \t|\t    "<< get_process_previous().get_timestamp()<<"\t\t|\t  Em uso   \t|"<<endl;
        }
        cout<<"   --------------------------------------------------------------------------------------------------------------"<<endl;
    }



}