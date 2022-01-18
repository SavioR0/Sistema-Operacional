#include "../../include/hardware/storage.hpp"

Storage::Storage(int size){
    this->size = size;
    BlockData assist;
    for(int i = 0; i < size; i++){
        assist.key = i;
        assist.type = NULL;
        this->blocks.push_back(assist);
    }
}

int Storage::insertStorage(BlockData bd){
    if(qtd == size)
        return 0;
    struct BlockData* newbd;
    newbd = (struct BlockData*)malloc(sizeof(struct BlockData));
    if(newbd == NULL)
        return 0;
    *newbd = bd;
    blocks.push_back(*newbd);
    qtd++;
    //cout<<"\t-Inserçao na memoria concluída com sucesso!"<<endl; 
    return 1;
}


/* int Memory::insertMemory(MemoryContent mc){
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
    //cout<<"\t-Inserçao na memoria concluída com sucesso!"<<endl; 
    return 1;
} */

void Storage::print(){
    
    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"  +    BLOCO\t|     VALOR\t|\t STATUS\t\t+"<<endl;
    cout<<"-----------------------------------------------------------"<<endl;
    for( BlockData item : this->blocks ){
        cout << "  +\t" << item.key << "\t|";
        if(item.type == NULL) 
            cout << "     NULL" << "\t|\t" << "Disponivel\t+" << endl;
        else
            cout << "\t"<<*item.type << "\t|\t" << "Ocupado\t+" << endl;
    } 
    cout<<"-----------------------------------------------------------\n"<<endl;

}