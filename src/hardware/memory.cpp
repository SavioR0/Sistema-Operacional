#include "../../include/hardware/memory.hpp"


Memory::Memory(int segments){ 
    this->segments         = segments;
    this->ram              = new MemoryContent[segments];
    this->allocated_amount = 0;
}


void Memory::resetMemory(){
    for(int i=0; i<this->segments; i++) this->ram[i].alocated = false;
}

void Memory::addTimeMemory(){
    for(int i = 0 ; i < this->segments; i++)
        if(this->ram[i].alocated == true)
            this->ram[i].currentTime++;
}

int Memory::hashingFunction(int key, int size){
    return (key & 0x7FFFFFFF) % size;
}

void Memory::insertMemory(int value, string description, int time){
    MemoryContent assist;
    assist.value       = value;
    assist.description = description;
    assist.time        = time;
    assist.currentTime = 0;
    assist.alocated    = true;
    this->addHash(assist);
}

int Memory::addHash(MemoryContent memory_content){
    if(allocated_amount == segments) return 0;

    
    int key      = memory_content.value;
    int position = hashingFunction(key, this->segments);

    MemoryContent* assist;
    assist = new MemoryContent;
    *assist = memory_content;

    ram[position] = *assist;
    allocated_amount++;
    return 1;
}

int Memory::searchMemory(int id,MemoryContent* mc){
    int pos = hashingFunction(id-1, segments);
    if(ram[pos].alocated == false)
        return 0;
    *mc = ram[pos]; 
    return 1;
} 

int Memory::removeMemory(int id){
    int pos = hashingFunction(id-1, segments);
    if(ram[pos].alocated == false)
        return 0;
    ram[pos].alocated=false; 
    ram[pos].currentTime=0;
    return 1;
} 

int Memory::get_segments(){
    return this->segments;
} 

/* int Memory::get_position_ram(int id){
    for(int i = 0; i < this->get_segments(); i++){
        if(this->ram[i].value == id) return i;
    }
    return -1;
} */



void Memory::print(){
    cout<<"  -----------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"  |\t\t\t\t\t\tINFORMACOES DA MEMORIA\t\t\t\t\t\t\t|"<<endl;
    cout<<"  -----------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"  |  Segmento\t|   Descricao\t|\t   Key\t\t|        Estado      \t|   Tempo\t|   Tempo maximo\t|"<<endl;
    cout<<"  -----------------------------------------------------------------------------------------------------------------------"<<endl;
    for(int i = 0; i<segments; i++){
        if(ram[i].alocated == false)
            cout<<"  |   ["<<i+1<<"]\t| "<<"     NULL"<<"\t|\t    -\t\t|\t Livre  \t|\t-\t|\t    -\t\t|"<<endl;
        else
            cout<<"  |   ["<<i+1<<"]\t|  "<<ram[i].description<<"\t|\t    "<<ram[i].value<<"\t\t|\t Em uso   \t|\t" << ram[i].currentTime << "\t|\t    " << ram[i].time <<"\t\t|"<<endl;
    }
    cout<<"  -----------------------------------------------------------------------------------------------------------------------"<<endl;
    
}
