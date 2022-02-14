#include "scheduler.hpp"


void header(std::string title, bool centralized){
    std::cout<<"   ------------------------------------------------------------------------------------------------------------------------------"<<std::endl;
    centralized
    ? std::cout<<"   |\t\t\t\t\t    "<<title<<"    \t\t\t\t\t\t\t\t|"<<std::endl
    : std::cout<<"   |\t"<<title<<"\t\t\t\t\t\t\t\t\t\t\t\t\t|"<<std::endl;
    std::cout<<"   ------------------------------------------------------------------------------------------------------------------------------"<<std::endl;  
    std::cout<<"   |\tID\t|\tEstado\t\t|\t  Tipo     \t|\tTimestamp\t|\tCiclos    |\tPrioridade\t|"<<std::endl;
    std::cout<<"   ------------------------------------------------------------------------------------------------------------------------------"<<std::endl;
}
void print_list(std::list<Process> list){
    for(Process item : list){
        std::cout<<"   |\t" << item.get_id() << "\t|\t" << item.get_status() << "    \t|\t"<< item.get_type() <<"\t|\t    " << item.get_timestamp() << "    \t|\t" << item.get_cycles() << "\t  |\t    " << item.get_priority()<<"\t\t|" << std::endl;
    }
}

bool Scheduler::report_processes() const{
    bool have_processes = ( !this->high_priority_process.empty()
        || !this->medium_priority_process.empty()
        || !this->low_priority_process.empty()
        || !this->super_low_priority_process.empty()
        || !this->finalized.empty()
    );
    if(!have_processes){
        std::cout<<" Erro[34] -> Não há processos para serem exibidos, confirme se sua lista de processo está carregada adequadamente no arquivo: " <<PROCESSES_FILE<< " e execute o comando: load para carrega-la." << std::endl;
        return false;
    }
    system("clear");

    bool all_finished = ( 
        this->high_priority_process.empty()
        && this->medium_priority_process.empty()
        && this->low_priority_process.empty()
        && this->super_low_priority_process.empty()
    );

    if(!all_finished){
        header((std::string) "Lista de Processos" , true);
        print_list(this->high_priority_process);
        print_list(this->medium_priority_process);
        print_list(this->low_priority_process);
        print_list(this->super_low_priority_process);
        std::cout<<"   ------------------------------------------------------------------------------------------------------------------------------"<<std::endl;
    }
    
    if(!this->finalized.empty()){
        std::cout<<"\n"<<std::endl;
        header((std::string) "Processos Finalizados" , false);
        print_list(this->finalized);
        std::cout<<"   ------------------------------------------------------------------------------------------------------------------------------"<<std::endl;
    }
    return true;
}    
