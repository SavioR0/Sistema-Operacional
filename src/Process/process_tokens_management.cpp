#include "process.hpp"

void Process::add_token(int token) { this->tokens.push_back(token);}
bool Process::contains_token(int token){ 
    for(int i : this->tokens)
        if(token == i) return true;
    return false; 
}

std::vector<int> Process::get_and_remove_tokens(){
    std::vector<int> assist = this->tokens;
    this->tokens.clear();
    return assist;
}