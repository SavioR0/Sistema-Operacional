#include "mfp.hpp"

void MFP::change_empty_lists(){
    this->empty_lists = true;
}

void distribution_list(list<Process>* processes,list<Process>* priority0, list<Process>* priority1,
    list<Process>* priority2, list<Process>* priority3, list<Process>* priority4){
        
    while(!(*processes).empty()){
        if((*processes).front().get_priority() == 4)      (*priority4).push_back((*processes).front());
        else if((*processes).front().get_priority() == 3) (*priority3).push_back((*processes).front());
        else if((*processes).front().get_priority() == 2) (*priority2).push_back((*processes).front());
        else if((*processes).front().get_priority() == 1) (*priority1).push_back((*processes).front());
        else if((*processes).front().get_priority() == 0) (*priority0).push_back((*processes).front());

        (*processes).pop_front();
    }   
    
}

void add_main_process(list<Process>* processes, list<Process>* priority0,
        list<Process>* priority1, list<Process>* priority2, list<Process>* priority3, list<Process>* priority4){
    
    if(!(*priority4).empty())
        while(!(*priority4).empty()){
            (*processes).push_back((*priority4).front());
            (*priority4).pop_front();
        }
    else if(!(*priority3).empty())
        while(!(*priority3).empty()){
            (*processes).push_back((*priority3).front());
            (*priority3).pop_front();
        }
    else if(!(*priority2).empty())
        while(!(*priority2).empty()){
            (*processes).push_back((*priority2).front());
            (*priority2).pop_front();
        }
    else if(!(*priority1).empty())
        while(!(*priority1).empty()){
            (*processes).push_back((*priority1).front());
            (*priority1).pop_front();
        }
    else if(!(*priority0).empty())
        while(!(*priority0).empty()){
            (*processes).push_back((*priority0).front());
            (*priority0).pop_front();
        }
    
}


void MFP::initialize_policie(){
    if(this-> processes.empty())
        return;
    distribution_list(&(this->processes), &(this->priority0), &(this->priority1), &(this->priority2), &(this->priority3), &(this->priority4));
    add_main_process(&(this->processes),&(this->priority0), &(this->priority1), &(this->priority2), &(this->priority3), &(this->priority4));
}



void MFP::aplly_policie(){
    if(!empty_lists){
        if(!priority4.empty())
            while (!priority4.empty()){
                processes.push_back(priority4.front());
                priority4.pop_front();
            }     
        else if(!priority3.empty())
            while (!priority3.empty()){
                processes.push_back(priority3.front());
                priority3.pop_front();
            }  
        else if(!priority2.empty())
            while (!priority2.empty()){
                processes.push_back(priority2.front());
                priority2.pop_front();
            }  
        else if(!priority1.empty())
            while (!priority1.empty()){
                processes.push_back(priority1.front());
                priority1.pop_front();
            } 
        else if(!priority0.empty()){
            while (!priority0.empty()){
                processes.push_back(priority0.front());
                priority0.pop_front();
            }
            change_empty_lists();
            cout<<"Mudou empty list: "<<empty_lists<<endl; 
        }
    }else {
        cout<<"Aplicando politica da loteria"<<endl;
        //POLITICA DA LOTERIA
    }
}