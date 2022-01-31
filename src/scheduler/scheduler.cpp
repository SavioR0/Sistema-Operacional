#include "scheduler.hpp"

// Construtores
Scheduler::Scheduler(Kernel* kernel, float quantum_time, string policie){
    this->kernel_ref    = kernel; 
    this->quantum_time  = quantum_time;
    this->policie       = policie;
}
Scheduler::Scheduler(){}

// Setters

// Getters

//Função de leitura
list<Process> Scheduler::read_processes(){
    json process_json;
    ifstream(process_file) >> process_json;
    
    list<Process> list_process;
    Process* assist = NULL;
    
    for (int i = 0; i < (int) process_json[json_list_name].size(); i++){
        
        assist = new Process(
            (int)    process_json[json_list_name][i]["id"],
            (float)  process_json[json_list_name][i]["ciclos"],
            (int)    process_json[json_list_name][i]["max_quantum"],
            (int)    process_json[json_list_name][i]["timestamp"],
            (int)    process_json[json_list_name][i]["prioridade"],
            (string) process_json[json_list_name][i]["init_type"]
        );

        list_process.push_back(*assist);
        free(assist);
    }
    cout<<"\n\n\t Todos os processos foram carregados e estão prontos para serem executados."<<endl;
    cout<<"\t Para ver a lista de processos digite o comando: queueschell."<<endl;
    cout<<"\t Para executar a lista de processos digite o comando: execute."<<endl;
    
    return list_process;
}

void Scheduler::load(){
    if(this->policie == fifo_policie_string )
        this->fifo_policie = new FIFO( 
            this->read_processes(), 
            this->kernel_ref->cpu, 
            this->kernel_ref->memory, 
            this->kernel_ref->storage, 
            this->quantum_time);

    if(this->policie == lru_policie_string )
        this->lru_policie = new LRU( 
            this->read_processes(), 
            this->kernel_ref->cpu, 
            this->kernel_ref->memory, 
            this->kernel_ref->storage, 
            this->quantum_time);

    if(this->policie == mfp_policie_string )
        this->mfp_policie = new MFP( 
            this->read_processes(), 
            this->kernel_ref->cpu, 
            this->kernel_ref->memory, 
            this->kernel_ref->storage, 
            this->quantum_time);
    
}

void Scheduler::restart(){
    if(this->policie == fifo_policie_string )
        this->fifo_policie->restart();
    if(this->policie == lru_policie_string )
        this->lru_policie->restart();
    /*if(this->policie == mfp_policie_string )
        this->mfp_policie->restart();*/
}

void Scheduler::execute(){
    if(this->policie == fifo_policie_string ) 
        this->pc = this->fifo_policie->execute_processes();
    if(this->policie == lru_policie_string ) 
        this->pc = this->lru_policie->execute_processes();
    if(this->policie == mfp_policie_string )
        this->mfp_policie->execute();
}
void Scheduler::report(){
    if(this->policie == fifo_policie_string ) 
        this->fifo_policie->report();
    if(this->policie == lru_policie_string ) 
        this->lru_policie->report();
    if(this->policie == mfp_policie_string )
        this->mfp_policie->report();
}