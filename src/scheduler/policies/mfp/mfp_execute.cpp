#include "mfp.hpp"

// Funções auxiliares
int random_number_mfp(int max){
    int x = rand()%max + 1;
    return x;
}

void MFP::check_block_list(){
    if(this->block.empty()) return;

    int* ids;
    int size_ids;
    size_ids = this->memory_ref->check_time(&ids, false);
    if(size_ids > 0 )
    for(int i = 0; i < size_ids; i++){ 
        for(int j = 0; j < (int)this->block.size(); j++){
            if(!block.empty()){
                if(ids[i] == this->block.front().get_id()){
                        if(this->block.front().get_cyles() <= 0){
                            this->block.front().set_status_finished();
                            this->finalized.push_back( this->block.front() );
                            this->block.pop_front();    
                        }else{
                            this->block.front().set_status_ready();
                            this->priority1.push_back( this->block.front() );
                            this->block.pop_front();
                        }

                }else{
                        Process* assist = new Process;
                        *assist = this->block.front();
                        this->block.push_back(*assist);
                        this->block.pop_front();
                        free(assist);
                }
            }
            
        }
        this->memory_ref->remove_memory(ids[i], false);
    }
    free(ids);      
    
    int* ids1;
    size_ids = this->storage_ref->check_time(&ids1);
    for(int i = 0; i < size_ids; i++){ 
        for(int j = 0; j < (int)this->block.size(); j++){
            if(!block.empty()){
                if(ids1[i] == this->block.front().get_id()){
                        if(this->block.front().get_cyles() <= 0){
                            this->block.front().set_status_finished();
                            this->finalized.push_back( this->block.front() );
                            this->block.pop_front();    
                        }else{
                            this->block.front().set_status_ready();
                            this->priority1.push_back( this->block.front() );
                            this->block.pop_front();
                        }

                    }else{
                        Process* assist = new Process;
                        *assist = this->block.front();
                        this->block.push_back(*assist);
                        this->block.pop_front();
                        free(assist);
                    }
            }
            
        }
        this->storage_ref->remove_storage(ids1[i]);
    }
    free(ids1);
}

void MFP::check_finished(Process* current_process, int* quantum){
    if(current_process == NULL) return;
    
    if(current_process->get_cyles() <= 0){
        current_process->set_status_finished();
        this->finalized.push_back(*current_process);
        current_process = NULL;
        this->priority1.pop_front();
        *quantum = 1;  
    }

}

void MFP::check_process_in_pogress(Process* current_process){
    if(current_process == NULL) return;
    
    if( current_process->get_status() == status_await ){
        cpu_ref->remove_process();
        current_process->set_status_ready(); 
        this->priority1.push_back(*current_process);                
        this->priority1.pop_front();
    }
}

void MFP::update_timestamp(Process** current_process){

    if(!this->priority1.empty()) 
    for(int i = 0; i < (int) this->priority1.size(); i++){
        this->priority1.front().add_timestamp();
        this->priority1.push_back(  this->priority1.front()  );
        this->priority1.pop_front();
    }

    if(!this->block.empty())
    for(int i = 0; i < (int) this->block.size(); i++){
        this->block.front().add_timestamp();
        this->block.push_back(  this->block.front()  );
        this->block.pop_front();
    }

    if(!this->priority1.empty())(*current_process) = &this->priority1.front();
    else (*current_process) = NULL;
}









void MFP::generate_token(){
    int tokens_generate = ((int) this->priority1.size()) - ((int) this->tokens_available.size());

    if(tokens_generate == 0) return; //Já tenho o número de fichas suficientes para todo mundo.
   
    else if(tokens_generate < 0 ){   //Tenho mais fichas que o necessário.
        for(int i = 0; i < (tokens_generate * -1); i++){  //Guardei todos os Tokens excedentes 
            this->tokens_surplus.push_back( this->tokens_available.back() );
            this->tokens_available.pop_back();
        }


    }else if(tokens_generate > 0){ // Preciso de novos Tokens
        if(this->tokens_surplus.empty()){ //Existem tokens excedentes?
            for(int i = 0; i < tokens_generate; i++) this->tokens_available.push_back( this->range_tokens + i);
            this->range_tokens += tokens_generate;
        }
        else if( (int) this->tokens_surplus.size() > tokens_generate  ){ // A quantidade execendetes é maior do que a quantidade que preciso 
            for(int i = 0; i < tokens_generate; i++){
                this->tokens_available.push_back( this->tokens_surplus.back() );
                this->tokens_surplus.pop_back();
            }
        }
        else if((int) this->tokens_surplus.size() <= tokens_generate){ // A quantidade execendetes é menor do que a quantidade que preciso 
            int new_tokens =  tokens_generate - (int) this->tokens_surplus.size(); //Quantos tokens preciso gerar
             for(int i = 0; i < (int) this->tokens_surplus.size(); i++){ //Peguei os tokens existentes
                this->tokens_available.push_back( this->tokens_surplus.back() );
                this->tokens_surplus.pop_back();
            }
            for(int i = 0; i < new_tokens; i++) this->tokens_available.push_back( this->range_tokens + i); //gerei novos tokens
            this->range_tokens += new_tokens;
        }
    }

}
void MFP::distribute_tokens(){
    if(this->tokens_available.empty()) return; // Tenho Tokens para distribuir?
    list<Process>::iterator list_iterator= this->priority1.begin();

    for(int i = 0; i < (int) this->priority1.size(); i++){
        list_iterator->add_token(this->tokens_available.back());
        this->tokens_available.pop_back();
        list_iterator++;
    }

}
void MFP::recover_tokens(list<Process>::iterator list_iterator){
    if(list_iterator == this->priority1.end()) return; //Verificando que o processo recebido é válido 
    
    this->tokens_available = list_iterator->get_tokens();
    list_iterator->remove_tokens();


}
list<Process>::iterator MFP::raffle(){
    list<Process>::iterator list_iterator = this->priority1.begin();
    int luck_number = 0;
    bool valid = false;

    if(this->range_tokens == (int)this->tokens_surplus.size()){ 

  

        this->generate_token();
        this->distribute_tokens();
    }
    if(this->range_tokens == (int)this->tokens_surplus.size()) cout<<"Deu ruim"<< endl;

    
    
    
  do{
    valid = false;
    while(valid == false){
        luck_number = rand()%(this->range_tokens - 1) + 1 ;  
        if(this->tokens_surplus.empty()) valid = true;
        else 
            valid = !count(this->tokens_surplus.begin(), this->tokens_surplus.end(), luck_number);  
    }

        for(int i = 0; i <(int) this->priority1.size(); i++){
            if(list_iterator->winning_token(luck_number)) break;
            list_iterator++;
        }
    }while(list_iterator == priority1.end());
    

    return list_iterator;
}



//Funções de execução
void MFP::execute_processes(){
    if(this->priority1.empty()){
        cout << "\n\n Nao ha processos para serem executados.\n Tente o comando 'load' para carregar processos para a lista de execucao." << endl;
        return;
    }
    int quantum = 0;
    bool await  = false;
    list<Process>::iterator list_iterator = this->priority1.begin();
    int      size_list_process    = (int) this->priority1.size();
    Process* current_process;



     do{
         if(current_process != NULL){ 
            if(quantum <= 0){
                this->generate_token();
                this->distribute_tokens();
                list_iterator = this->raffle();
                this->recover_tokens(list_iterator);

                while(this->priority1.front().get_id() != list_iterator->get_id()){
                    this->priority1.push_back(this->priority1.front());
                    this->priority1.pop_front();
                }
                current_process = &this->priority1.front();

                quantum = random_number_mfp( current_process->get_max_quantum());
                current_process->sub_quantum(quantum);
            }

            if(current_process->get_status() == status_ready && await == false){
                await = true;
                if     (current_process->get_type() == "cpu-bound"   ) executing_process_cpu    (current_process);
                else if(current_process->get_type() == "memory-bound") executing_process_memory (current_process);
                else if(current_process->get_type() == "io-bound"    ) executing_process_storage(current_process);

            }
        }
        this->memory_ref->add_time_memory();
        this->storage_ref->add_time_storage();

        this->update_timestamp(&current_process);
        this->check_block_list();

        this->check_finished(current_process, &quantum);
        
        quantum--;
        
        if(quantum == 0){
            await = false;
            this->check_process_in_pogress(current_process);
            if(this->priority1.empty()) current_process = NULL;
            else                        current_process = &this->priority1.front();
        }
        usleep( (quantum_time * 1000000) );

    }while( (int) this->finalized.size() < size_list_process  );
    cout<<"Saí";



}




void MFP::executing_process_cpu(Process* current_process){
    current_process->set_status_await();
    this->cpu_ref->set_process( current_process );
}

void MFP::executing_process_memory(Process* current_process){
    current_process->set_status_block();
    this->memory_ref->insert_memory(
        current_process->get_id(),
        current_process->get_type(),
        current_process->get_size(),
        current_process->get_max_quantum(),
        random_number_mfp(4));

    this->block.push_back( (*current_process) );

    current_process = NULL;
    this->priority1.pop_front();
    if(!this->priority1.empty()) current_process = &this->priority1.front(); 
    
}

void MFP::executing_process_storage(Process* current_process){
    current_process->set_status_block();
    this->storage_ref->insert_block_data(
        current_process->get_id(),
        current_process->get_type(),
        random_number_mfp(4));
    
    this->block.push_back( (*current_process) );

    current_process = NULL;
    this->priority1.pop_front();
    if(!this->priority1.empty()) current_process = &this->priority1.front(); 
    
}

