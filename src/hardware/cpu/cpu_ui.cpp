#include "cpu.hpp"

void Cpu::header_report()const{
    std::cout<<"\n\n  |-------------------------------------------------------------------------------------|"<<std::endl;
    std::cout<<"  |\t\t\t\t    Informações da CPU    \t\t\t\t|"<<std::endl;
    std::cout<<"  |-------------------------------------------------------------------------------------|"<<std::endl;
    std::cout<<"  |\tCore\t|\tId Processo\t|\tQuantum max\t|\tEstado  \t|" << std::endl;
    std::cout<<"  |-------------------------------------------------------------------------------------|"<<std::endl;
}
void print_line( int core){
    std::cout<<"  |\t" << core <<"\t|\t    None   \t|\t   None   \t|\tDisponível\t|"<<std::endl;
}
void print_line(Process process, int core){
    std::cout<<"  |\t" << core <<"\t|\t    "<< process.get_id() <<"   \t|\t   "<<process.get_max_quantum()<<"\t\t|\tIndisponível\t|"<<std::endl;
}

void Cpu::generate_report() const {
    system("clear");
    this->header_report();
    this->print_list();

    std::cout<<"  |-------------------------------------------------------------------------------------|"<<std::endl;  
}


void Cpu::print_list() const{
    int current_core = 0;
    for(Process item : this->cores ){
        if(item.get_id() == -1) print_line(current_core);
        else print_line(item, current_core);
        current_core++;
    }
}
