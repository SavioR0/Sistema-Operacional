#include "../../include/hardware/storage.hpp"

Storage::Storage(int size){
    this->size = size;
    BlockData assist;
    for(int i = 0; i < size; i++){
        assist.key = i;
        assist.value = NULL;
        this->blocks.push_back(assist);
    }
}

void Storage::print(){
    

    for( BlockData item : this->blocks ){
        cout << " Bloco: " << item.key << "\tValor: ";
        if(item.value == NULL) 
            cout << " NULL" << "\tStatus: " << "Disponivel" << endl;
        else
            cout << *item.value << "\tStatus: " << "Ocupado" << endl;
    }
    
    cout << endl;
}