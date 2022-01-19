#include "../include/process.hpp"

Process::Process(){}

Process::Process( int id, float cycles, int maxQuantum, int timestamp, int priority,  string type){
    string* status = new string;
    string* type_ptr = new string;
    *status   = status_ready;
    *type_ptr = type;

    this->id =  id;
    this->cycles = cycles;
    this->maxQuantum = maxQuantum;
    this->timestamp = timestamp;
    this->priority = priority;
    this->type = type_ptr;
    this->status = status;
}

void Process::setId                 (int value)     { this->id          = value; }
void Process::setCycles             (float value)   { this->cycles      = value; }
void Process::setMaxQuantum         (int value)     { this->maxQuantum  = value; }
void Process::setTimestamp          (int value)     { this->timestamp   = value; }
void Process::setPriority           (int value)     { this->priority    = value; }
void Process::setStatusAddres       (string* value) { this->status      = value; }
void Process::setTypeAddress        (string* value) { this->type        = value; }
void Process::setStatus_await(){
    free(this->status);
    string* assist = new string;
    *assist = status_await;
    this->status = assist;
}
void Process::setStatus_ready(){
    free(this->status);
    string* assist = new string;
    *assist = status_ready;
    this->status = assist;
}
void Process::setStatus_finished(){
    free(this->status);
    string* assist = new string;
    *assist = status_finished;
    this->status = assist;
}
void Process::setStatus_block(){
    free(this->status);
    string* assist = new string;
    *assist = status_block;
    this->status = assist;
}
void Process::setStatus(string value){
    free(this->status);
    string* assist = new string;
    *assist = value;
    this->status = assist;
}
void Process::setType(string value){ 
    string* assist = new string;
    *assist = value;
    this->type = assist;
}



int Process::getId                  (){return this->id;         }
float Process::getcyles             (){return this->cycles;     }
int Process::getMaxQuantum          (){return this->maxQuantum; }
int Process::getTimestamp           (){return this->timestamp;  }
int Process::getPriority            (){return this->priority;   }
        
string  Process::getStatus          (){return *(this->status);  }
string* Process::getStatusAdress    (){return this->status;     }
string  Process::getType            (){return *(this->type);    }
string* Process::getTypeAdress      (){return this->type;       }


void Process::sub_quantum(int currentQuantum){
    float decrease = (float) currentQuantum / (float) this->maxQuantum;
    this->cycles -= decrease;
}

void Process::add_timestamp(){ this->timestamp++; }