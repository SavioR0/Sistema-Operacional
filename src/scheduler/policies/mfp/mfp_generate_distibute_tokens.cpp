#include "mfp.hpp"

void Mfp::generate_tokens(){
    int number_of_tokens_generated = (int) this->super_low_priority_process.size() - (int) this->tokens_available.size();

    if(number_of_tokens_generated <= 0) return; // Já possuo todos os tokens que preciso (pelo menos 1 token para cada processo)

    for(int i = 0; i < number_of_tokens_generated; i++)
        this->tokens_available.push_back(range_tokens_avaliables + i);
    
    this->range_tokens_avaliables += number_of_tokens_generated;
}

void Mfp::distribute_tokens(){
    if(this->super_low_priority_process.empty()) return;
    int division = (int) this->tokens_available.size() / (int) this->super_low_priority_process.size();
    for(int i = 0; i < division; i++)
    for(std::list<Process>::iterator iterator = this->super_low_priority_process.begin(); iterator != this->super_low_priority_process.end(); iterator++){
        iterator->add_token( this->tokens_available.back() );
        this->tokens_available.pop_back();
    }

}