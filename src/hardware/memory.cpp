#include "../../include/hardware/memory.hpp"


Memory::Memory(int segments){ 
    this->segments           = segments;
    this->ram                = new MemoryContent[segments];
    this->allocated_segments = 0;
}

// Funções de gerenciamento
void Memory::addTimeMemory(){
    for(int i = 0 ; i < this->segments; i++)
        if(this->ram[i].alocated == true)
            this->ram[i].currentTime++;
}

void Memory::resetMemory(){
    this->allocated_segments = 0;
    for(int i=0; i<this->segments; i++) this->ram[i].alocated = false;
}

int Memory::check_time(int** ids){
    int size = 0;
    *ids = (int*) malloc(sizeof(int));
    for(int i = 0; i < this->segments; i++){
        if(this->ram[i].alocated == true)
            if(this->ram[i].currentTime >= this->ram[i].time){
                if(size == 0){
                    *ids[0] = ram[i].value;
                    size++;
                }else{
                   *ids = (int*) realloc(*ids, (size + 1) * sizeof(int));
                   (*ids)[size] =  ram[i].value;
                   size++;
                }
            }
    }
    return size;
}

int Memory::hashingFunction(int key, int size){
    return (key & 0x7FFFFFFF) % size;
}

//Funções de gerenciamento
int Memory::insertMemory(int value, string description, int time){
    if(allocated_segments == segments){ 
        cout<<"[Erro 011 -> Não foi possível alocar o valor: " << value << " na memŕia, pois não há segmentos disponíveis."<< endl;
        return 0;
    }

    MemoryContent assist;
    assist.value       = value;
    assist.description = description;
    assist.time        = time;
    assist.currentTime = 0;
    assist.alocated    = true;
    return this->addHash(assist);
}

int Memory::addHash(MemoryContent memory_content){    
    int key      = memory_content.value;
    int position = hashingFunction(key, this->segments);

    MemoryContent* assist;
    assist = new MemoryContent;
    *assist = memory_content;

    ram[position] = *assist;
    allocated_segments++;
    return 1;
}

int Memory::searchMemory(int id,MemoryContent* mc){
    int pos = hashingFunction(id, segments);
    if(ram[pos].alocated == false)
        return 0;
    *mc = ram[pos]; 
    return 1;
} 

int Memory::removeMemory(int id){    
    int pos = hashingFunction(id, this->segments);
    
    if(ram[pos].alocated == false){ 
        cout<<"Erro [0111] -> O contúdo não pôde ser removido pois não existe, ou não está alocado" << endl;
        return 0;
    }
        
    ram[pos].alocated    = false; 
    allocated_segments--;
    return 1;
} 

//Funções get
int Memory::get_segments(){ return this->segments;} 


//FUnções de relatório
void Memory::print(){
    system("clear");
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
