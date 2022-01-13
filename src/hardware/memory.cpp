#include "../../include/hardware/memory.hpp"


Memory::Memory(int segmentos){ //definindo o tamanho da tabela hash
    segments = segmentos;
    ram = new MemoryContent[segmentos];
    qtd = 0;
    Memory::clearMemory(segmentos);  
}

void Memory::clearMemory(int segmentos){
    for(int i=0; i<segmentos; i++){
        ram[i].value = 0;
        ram[i].description = "";
    }
}

//int Memory::insereMemory(MemoryContent mc){} 
//int Memory::buscaMemory(int mat,MemoryContent mc){} 

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
        if(ram[i].value == 0 && ram[i].description=="")
            cout<<"  +   ["<<i+1<<"]\t| "<<"     NULL"<<"\t|\t   "<<ram[i].value<<"\t\t|\t Livre  \t+"<<endl;
        else
            cout<<"  +   ["<<i+1<<"]\t|\t "<<ram[i].description<<"\t|\t"<<ram[i].value<<"\t|\tEm uso   \t+"<<endl;
    }
}
