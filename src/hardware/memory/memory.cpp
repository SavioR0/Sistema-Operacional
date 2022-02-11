#include "memory.hpp"


Memory::Memory(int segments){ 
    this->segments           = segments;
    this->ram                = new MemoryContent[segments];
    this->allocated_segments = 0;
}

// Funções de gerenciamento
void Memory::add_time_memory(){
    for(int i = 0 ; i < this->segments; i++)
        if(this->ram[i].alocated == true)
            this->ram[i].current_time++;
}

void Memory::reset_memory(){
    this->allocated_segments = 0;
    for(int i=0; i<this->segments; i++) this->ram[i].alocated = false;
}

int Memory::check_time(int** ids){
    int size = 0;
    *ids = (int*) malloc(sizeof(int));
    for(int i = 0; i < this->segments; i++){
        if(this->ram[i].alocated == true)
            if(this->ram[i].current_time >= this->ram[i].time){
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

//Funções de gerenciamento
int Memory::insert_memory(int value, string description, int size,int time){
    int position = search_position_memory(size);
    if(allocated_segments == segments || position == -1){ 
        cout<<"[Erro 011 -> Não foi possível alocar o valor: " << value << " na memória, pois não há segmentos disponíveis."<< endl;
        return 0;
    }

    MemoryContent assist;
    assist.value       = value;
    assist.description = description;
    assist.time        = time;
    assist.current_time = 0;
    assist.alocated    = true;
    return this->add(assist, position, size);
}

int Memory::search_position_memory(int size){
    int current_position = 0, counter = 0;

    while (current_position < this->segments)
        if(ram[current_position].alocated == false){
            counter++;
            if(counter >= size)
                return current_position;
        }else
            current_position ++;      
    return -1;
}

int Memory::add(MemoryContent memory_content, int position, int size){    
    MemoryContent* assist;
    assist = new MemoryContent;
    *assist = memory_content;

    for(int i = 0 ; i<size; i++){
        ram[position + i] = *assist;
    }
    
    allocated_segments += size;
    return 1;
}

int Memory::search_memory(int id){
    for(int i = 0; i<segments; i++){
        if(ram[i].alocated == true && ram[i].value == id){
            return i;
        }
    }
    return -1;
} 



int Memory::remove_memory(int id){    
    int pos = search_memory(id);
    
    if(pos == -1){ 
        cout<<"Erro [0111] -> O conteúdo não pôde ser removido pois não existe, ou não está alocado" << endl;
        return 0;
    }
    while(ram[pos].alocated == true && ram[pos].value == id){  
        ram[pos].alocated    = false; 
        allocated_segments--;
    }
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
            cout<<"  |   ["<<i+1<<"]\t|  "<<ram[i].description<<"\t|\t    "<<ram[i].value<<"\t\t|\t Em uso   \t|\t" << ram[i].current_time << "\t|\t    " << ram[i].time <<"\t\t|"<<endl;
    }
    cout<<"  -----------------------------------------------------------------------------------------------------------------------"<<endl;
    
}
