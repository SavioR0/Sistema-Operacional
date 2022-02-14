#include "scheduler.hpp"

Scheduler::Scheduler(Kernel* kernel_ref, bool single_list):kernel_ref(kernel_ref), single_list(single_list){
    this->cpu_ref     = kernel_ref->get_cpu_ref();
    this->memory_ref  = kernel_ref->get_memory_ref();
    this->storage_ref = kernel_ref->get_storage_ref();

}

bool Scheduler::continuity_test(std::list<Process>::iterator& iterator, int& current_quantum, std::list<Process>& list) {
    if( list.empty() ){ current_quantum--; return false;}
    if(iterator != list.end()) return true;
    else{
        iterator++;
        return true;
    }
    return false;
}

void add_process_in_list(std::list<Process>& list, nlohmann::json json_file, int position){
    list.push_back(
        Process(
            (int)         json_file[LIST_NAME][position]["id"],
            (float)       json_file[LIST_NAME][position]["ciclos"],
            (int)         json_file[LIST_NAME][position]["max_quantum"],
            (int)         json_file[LIST_NAME][position]["timestamp"],
            (int)         json_file[LIST_NAME][position]["prioridade"],
            (std::string) json_file[LIST_NAME][position]["init_type"] 
        ) 
    );
}

void Scheduler::load_list_processes(){
    nlohmann::json json_file;
    std::ifstream file;
    file.open(PROCESSES_FILE);
    if(file.fail()){
        std::cout<<"Erro [404] -> Não foi possível abrir o arquivo: " << PROCESSES_FILE << ". \n \tVerifique se ele existe e se está correto." << std::endl;
        return;
    }

    file >> json_file;

    bool empty_list = json_file[LIST_NAME].size() <= 0; 
    if(empty_list){
        std::cout<<"Erro[33] -> Não foi possível carregar a lista. A lista pode não existir no arquivo: " << PROCESSES_FILE << " ou pode estar vazia." << std::endl;
        return;
    } 

    for(int i = 0; i < (int) json_file[LIST_NAME].size(); i++ ){
        if(this->single_list){
            add_process_in_list(this->super_low_priority_process, json_file, i); 
            continue;
        }        
        if(json_file[LIST_NAME][i]["prioridade"] == 4){
            add_process_in_list(this->high_priority_process, json_file, i); 
            continue;
        }
        if(json_file[LIST_NAME][i]["prioridade"] == 3){
            add_process_in_list(this->medium_priority_process, json_file, i); 
            continue;
        }
        if(json_file[LIST_NAME][i]["prioridade"] == 2){
            add_process_in_list(this->low_priority_process, json_file, i); 
            continue;
        }
        if(json_file[LIST_NAME][i]["prioridade"] == 1){
            add_process_in_list(this->super_low_priority_process, json_file, i); 
            continue;
        }
    }
    std::cout<<"\n\n\t Todos os processos foram carregados e estão prontos para serem executados."<<std::endl;
    std::cout<<    "\t Para ver a lista de processos digite o comando: queueschell."              <<std::endl;
    std::cout<<    "\t Para executar a lista de processos digite o comando: execute."             <<std::endl; 
}