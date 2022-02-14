#include "mfp.hpp"

bool Mfp::contains_token(int token)const{  
    for(int i : this->tokens_available)
        if(token == i) return true;
    return false;  
}

void Mfp::raffle(std::list<Process>::iterator& iterator){
    if(this->super_low_priority_process.size() == 1){
        iterator = this->super_low_priority_process.begin();
        return;
    }
    bool number_valid = false;
    int luck_number;
    int attempts = 15;
    while(attempts > 0){

        do{
            luck_number = this->radom_number(this->range_tokens_avaliables - 1);
            if(this->contains_token(luck_number)) continue;
            number_valid = true;
        }while(number_valid == false);

        for(iterator = this->super_low_priority_process.begin(); iterator != this->super_low_priority_process.end(); iterator++)
            if(iterator->contains_token(luck_number)) return;
        attempts--;
    }
    std::cout<<"Erro crítico, ninguém tem o número sorteado: "<< luck_number << std::endl;
    exit(90);
}

void Mfp::recover_tokens(std::list<Process>::iterator& iterator){
    std::vector<int> assit = iterator->get_and_remove_tokens();
    for(int x : assit)
        this->tokens_available.push_back(x);
}