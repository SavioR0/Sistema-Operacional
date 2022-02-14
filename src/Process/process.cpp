#include "process.hpp"

Process::Process(int id,float cycles,const short int max_quantum, int timestamp, int priority, std::string type):
    id(id),
    cycles(cycles), 
    max_quantum(max_quantum),
    timestamp(timestamp),
    priority(priority),
    type(type){
        this->status = STATUS_READY;
    }

void Process::add_timestamp(){this->timestamp++;}
void Process::sub_cycles(int quantum_drawn){
    float sub = (float) quantum_drawn / (float) this->max_quantum;
    this->cycles = (this->cycles - sub) >= 0 ? (this->cycles - sub) : 0;
}