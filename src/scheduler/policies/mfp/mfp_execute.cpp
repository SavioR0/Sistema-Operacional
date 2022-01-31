#include "mfp.hpp"

// Funções auxiliares
int random_number_mfp(int max){
    return rand()%max + 1;
}

void MFP::check_block_list(){
    if(this->block.empty()) return;

    int* ids;
    int size_ids;
    size_ids = this->memory_ref->check_time(&ids);
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
        this->memory_ref->remove_memory(ids[i]);
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

void MFP::check_finished(list<Process>::iterator list_iterator, int* quantum){
    if(list_iterator == this->priority1.end()) return;
    
    if(list_iterator->get_cyles() <= 0){
        list_iterator->set_status_finished();
        this->finalized.push_back(*(&*list_iterator));
        this->priority1.erase(list_iterator);
        list_iterator = this->priority1.begin();
        *quantum = 1;  

    }

}

void MFP::check_process_in_pogress(list<Process>::iterator list_iterator){
    if(list_iterator == this->priority1.end()) return;

    
    if( list_iterator->get_status() == status_await ){
        cpu_ref->remove_process();
        list_iterator->set_status_ready(); 
    }
}







void MFP::update_timestamp(){
    list<Process>::iterator assist;

    if(!this->priority1.empty())
        for(assist = this->priority1.begin(); assist != this->priority1.end(); assist++)
            assist->add_timestamp();
    

    if(!this->block.empty())
        for(assist = this->block.begin(); assist != this->block.end(); assist++)
            assist->add_timestamp();
}

void MFP::generate_token(){
    int size_new_tokens = (int) this->priority1.size() - (int) this->tokens_available.size();
    
    if(size_new_tokens == 0) return;
    else if(size_new_tokens > 0)
        for(int i = 0; i < size_new_tokens; i++) this->tokens_available.push_back( this->range_tokens + i);
    else{
        cout<<"Cái no -1"<<endl;
        size_new_tokens = size_new_tokens + (int) this->priority1.size();
        for(int i = 0; i < size_new_tokens; i++) this->tokens_available.push_back( this->range_tokens + i);
    }
    this->range_tokens += size_new_tokens;

}
void MFP::distribute_tokens(){
    if((int)this->tokens_available.size() == 0) return;

    list<Process>::iterator list_iterator = this->priority1.begin();
    while(this->tokens_available.size() > 0){
        cout<<"Check 1" <<endl;
        if(!this->priority1.empty()){
            list_iterator = this->priority1.begin();
            cout<<"Check 2" <<endl;
            for(int i=0; i < (int) this->priority1.size(); i++){
                list_iterator->add_token(this->tokens_available.front());
                this->tokens_available.erase(this->tokens_available.begin());
                list_iterator++;
            }
        }
        else if(!this->block.empty()){
            list_iterator = this->block.begin();
            cout<<"Check 3" <<endl;
            for(int i=0; i < (int) this->block.size(); i++){
                list_iterator->add_token(this->tokens_available.front());
                this->tokens_available.erase(this->tokens_available.begin());
                list_iterator++;
            }
        }
    }
}
void MFP::recover_tokens(list<Process>::iterator list_iterator){

    if(list_iterator == this->priority1.end()) return;
    cout<<"\n\nEnterei em recover_tokens"<<endl;
    cout<<"Tamanho da lista de Tokens: " << (int) this->tokens_available.size() <<endl;
    cout<<"Tamanho da lista de Tokens no processo: " << (int) list_iterator->get_tokens().size() <<endl; 

    this->tokens_available = list_iterator->get_tokens();
    list_iterator->remove_tokens();
}


//Funções de execução
void MFP::execute_processes(){
    if(this->priority1.empty()){
        cout << "\n\n Nao ha processos para serem executados.\n Tente o comando 'load' para carregar processos para a lista de execucao." << endl;
        return;
    }
    int luck;
    int quantum = 0;
    bool await  = false;
    list<Process>::iterator list_iterator = this->priority1.begin();
    int      size_list_process    = (int) this->priority1.size();



     do{

        if(!this->priority1.empty()){ 
            if(quantum <= 0){
                cout<<"\n\nEntrei em sortear"<<endl;  
                cout<<"Verificação 1."<<endl;
                this->generate_token();
                cout<<"Verificação 2."<<endl;
                this->distribute_tokens();
                cout<<"Verificação 3."<<endl;
                do{
                luck = random_number_mfp(this->range_tokens - 1);
                for(list_iterator = this->priority1.begin(); list_iterator != this->priority1.end(); list_iterator++)
                    if(list_iterator->winning_token(luck)) break;               
                }while(list_iterator == this->priority1.end());
                cout<<"Verificação 5."<<endl;
                this->recover_tokens(list_iterator);
                cout<<"Verificação 6."<<endl;
                quantum = random_number_mfp( list_iterator->get_max_quantum());
                cout<<"Verificação 7."<<endl;
                list_iterator->sub_quantum(quantum);
                cout<<"\n\nSaí em sortear"<<endl;  

            }
            

            if(list_iterator->get_status() == status_ready && await == false){
                await = true;
                if     (list_iterator->get_type() == "cpu-bound"   ) executing_process_cpu    (list_iterator);
                else if(list_iterator->get_type() == "memory-bound") executing_process_memory (list_iterator);
                else if(list_iterator->get_type() == "io-bound"    ) executing_process_storage(list_iterator);

            }
        }
        this->memory_ref->add_time_memory();
        this->storage_ref->add_time_storage();

        this->update_timestamp();
        this->check_block_list();

        this->check_finished(list_iterator, &quantum);
        
        quantum--;
        
        if(quantum == 0){
            await = false;
            this->check_process_in_pogress(list_iterator);

        }
        usleep( (quantum_time * 1000000) );
        
    }while( (int) this->finalized.size() < size_list_process );



}




void MFP::executing_process_cpu(list<Process>::iterator list_iterator){
    list_iterator->set_status_await();
    this->cpu_ref->set_process( &*list_iterator );
}

void MFP::executing_process_memory(list<Process>::iterator list_iterator){
    list_iterator->set_status_block();
    this->memory_ref->insert_memory(
        list_iterator->get_id(),
        list_iterator->get_type(),
        random_number_mfp(4));

    this->block.push_back( *(&*list_iterator) );

    if(!this->priority1.empty()) this->priority1.erase(list_iterator);

}


void MFP::executing_process_storage(list<Process>::iterator list_iterator){
    list_iterator->set_status_block();
    this->storage_ref->insert_block_data(
        list_iterator->get_id(),
        list_iterator->get_type(),
        random_number_mfp(4));
    
    this->block.push_back( *(&*list_iterator) );

    if(!this->priority1.empty()) this->priority1.erase(list_iterator);
    
    
}

