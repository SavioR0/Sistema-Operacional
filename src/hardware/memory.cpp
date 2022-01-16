#include "../../include/hardware/memory.hpp"


Memory::Memory(int segmentos){ //definindo o tamanho da tabela hash
    segments = segmentos;
    ram = new MemoryContent[segmentos];
    qtd = 0;
    Memory::clearMemory(segmentos);  
}

void Memory::clearMemory(int segmentos){
    for(int i=0; i<segmentos; i++){
        ram[i].value = -1;
        ram[i].description = "";
    }
}

int Memory::hashingFunction(int key, int size){
    return (key & 0x7FFFFFFF) % size;
}

int Memory::insertMemory(MemoryContent mc){
    if(qtd == segments)
        return 0;
    cout<<""<<endl;
    int key = mc.value;
    int position = hashingFunction(key, segments);
    struct MemoryContent* newmc;
    newmc = (struct MemoryContent*)malloc(sizeof(struct MemoryContent));
    if(newmc == NULL)
        return 0;
    *newmc = mc;
    ram[position] = *newmc;
    qtd++;
    /* cout<<"\t-Inserçao na memoria concluída com sucesso!"<<endl; */
    return 1;
}

int Memory::searchMemory(int id,MemoryContent* mc){
    int pos = hashingFunction(id-1, segments);
    if(ram[pos].value == -1)
        return 0;
    *mc = ram[pos]; 
    return 1;
} 

void Memory::print(){
    /* cout<<"-Numero de Segmentos:"<<segments <<endl;
    cout<<"\nSEGMENTO\tDESCRIÇÃO\tCONTEÚDO MEMORIA\tESTADO"<<endl;
    for(int i = 0; i<segments; i++){
        if(ram[i].value == 0 && ram[i].description=="")
            cout<<"  ["<<i+1<<"]\t\t "<<"NULL"<<"\t\t\t"<<ram[i].value<<"\t\t Livre"<<endl;
        else
            cout<<"  ["<<i+1<<"]\t\t "<<ram[i].description<<"\t\t\t"<<ram[i].value<<"\t\tEm uso"<<endl;
    }
    cout<<endl; */
    cout<<"---------------------------------------------------------------------------------"<<endl;
    cout<<"  +  SEGMENTO\t|   DESCRIÇÃO\t|   CONTEÚDO MEMORIA\t|        ESTADO      \t+"<<endl;
    cout<<"---------------------------------------------------------------------------------"<<endl;
    for(int i = 0; i<segments; i++){
        if(ram[i].value == -1 && ram[i].description=="")
            cout<<"  +   ["<<i+1<<"]\t| "<<"     NULL"<<"\t|\t    -\t\t|\t Livre  \t+"<<endl;
        else
            cout<<"  +   ["<<i+1<<"]\t|  "<<ram[i].description<<"\t|\t    "<<ram[i].value<<"\t\t|\t  Em uso   \t+"<<endl;
    }
    cout<<"---------------------------------------------------------------------------------"<<endl;
}
