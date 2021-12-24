#include "../../include/hardware/memory.hpp"
#include "/home/savio/Sistema-Operacional/include/hardware/memory.hpp"


Hash::Hash(int segmentos){ //definindo o tamanho da tabela hash
    seg = segmentos;
    ram = new MemoryContent[segmentos];
    qtd = 0;
    Hash::clearHash(segmentos);  
}

void Hash::clearHash(int segmentos){
    for(int i=0; i<segmentos; i++){
        ram[i].value = 0;
        ram[i].description = "";
    }
}

//int Hash::insereHash(MemoryContent mc){} 
//int Hash::buscaHash(int mat,MemoryContent mc){} 

void Hash::printHash(){
    cout<<"-Numero de Segmentos:"<<seg <<endl;
    cout<<"\nSEGMENTO\tDESCRIÇÃO\tCONTEÚDO MEMORIA\tESTADO"<<endl;
    for(int i = 0; i<seg; i++){
        if(ram[i].value == 0 && ram[i].description=="")
            cout<<"  ["<<i+1<<"]\t\t "<<"NULL"/* ram[i].description */<<"\t\t\t"<<ram[i].value<<"\t\t Livre"<<endl;
        else
            cout<<"  ["<<i+1<<"]\t\t "<<ram[i].description<<"\t\t\t"<<ram[i].value<<"\t\tEm uso"<<endl;
    }
    cout<<endl;
}
