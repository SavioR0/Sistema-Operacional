#include "process.hpp"

Process::Process(){}

Process::Process( int id, float cycles, int max_quantum, int timestamp, int priority,  string type){
    string* status = new string;
    string* type_ptr = new string;
    *status   = status_ready;
    *type_ptr = type;

    this->id =  id;
    this->cycles = cycles;
    this->max_quantum = max_quantum;
    this->timestamp = timestamp;
    this->priority = priority;
    this->type = type_ptr;
    this->status = status;
}

void Process::set_id                 (int value)     { this->id                     = value;}
void Process::set_cycles             (float value)   { this->cycles                 = value;}
void Process::set_max_quantum        (int value)     { this->max_quantum            = value;}
void Process::set_timestamp          (int value)     { this->timestamp              = value;}
void Process::set_priority           (int value)     { this->priority               = value;}
void Process::set_status_addres      (string* value) { this->status                 = value;}
void Process::set_type_address       (string* value) { this->type                   = value;}
void Process::set_status_await(){
    free(this->status);
    string* assist = new string;
    *assist = status_await;
    this->status = assist;
}
void Process::set_status_ready(){
    free(this->status);
    string* assist = new string;
    *assist = status_ready;
    this->status = assist;
}
void Process::set_status_finished(){
    free(this->status);
    string* assist = new string;
    *assist = status_finished;
    this->status = assist;
}
void Process::set_status_block(){
    free(this->status);
    string* assist = new string;
    *assist = status_block;
    this->status = assist;
}
void Process::set_status(string value){
    free(this->status);
    string* assist = new string;
    *assist = value;
    this->status = assist;
}
void Process::set_type(string value){ 
    string* assist = new string;
    *assist = value;
    this->type = assist;
}



int Process::get_id                  (){return this->id;         }
float Process::get_cyles             (){return this->cycles;     }
int Process::get_max_quantum         (){return this->max_quantum;}
int Process::get_timestamp           (){return this->timestamp;  }
int Process::get_priority            (){return this->priority;   }
        
string  Process::get_status          (){return *(this->status);  }
string* Process::get_status_adress   (){return this->status;     }
string  Process::get_type            (){return *(this->type);    }
string* Process::get_type_adress     (){return this->type;       }


void Process::sub_quantum(int current_quantum){
    float decrease = (float) current_quantum / (float) this->max_quantum;
    this->cycles -= decrease;
}

void Process::add_timestamp(){ this->timestamp++; }