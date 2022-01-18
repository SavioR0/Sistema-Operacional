#include "../../include/hardware/storage.hpp"

Storage::Storage(int size){
    this->size = size;
    BlockData assist;
    for(int i = 0; i < size; i++){
        assist.key = 0;
        assist.type = "";
        assist.currentTime=0;
        assist.time = 0;
        assist.alocated = false;
        this->blocks.push_back(assist);
    }
}

int Storage::insertStorage(BlockData bd){
    if(qtd == size)
        return 0;
    for( int i = 0 ; i< this->size; i++){
        if(blocks.front().alocated == false){
            blocks.pop_front();
            blocks.push_front(bd);
            return 1;
        }
        blocks.push_back(blocks.front());
        blocks.pop_front();
    }
    
    return 0;
}


int Storage::searchStorage(int id, BlockData* bd){
    for(int i = 0; i < this->size; i++){
       if(id == blocks.front().key){
           *bd = blocks.front();
           return 1;
       }
       blocks.push_back(blocks.front());
       blocks.pop_front();
    }
    return 0;
}

int Storage::removeStorage(int id ){
    BlockData bd;
    for(int i = 0; i < this->size; i++){
       if(id == blocks.front().key){
            if(blocks.front().alocated == false)
                return 0;
            blocks.front().alocated=false; 
            blocks.front().currentTime = 0;

       }else{
            blocks.push_back(blocks.front());
            blocks.pop_front();
       }
    }
    return 1;
}

void Storage::addTimeStorage(){
    for(int i = 0 ; i < this->size; i++){
        if(this->blocks.front().alocated == true)
            this->blocks.front().currentTime++;
        blocks.push_back(blocks.front());
        blocks.pop_front();
    }
}
void Storage::print(){
    
    cout<<"  ---------------------------------------------------------------------------------------"<<endl;
    cout<<"  |    ID\t|     Valor\t|\t Status\t\t|   Tempo\t|   Tempo maximo\t|"<<endl;
    cout<<"  ---------------------------------------------------------------------------------------"<<endl;
    for( BlockData item : this->blocks ){
        cout << "  |\t" << item.key << "\t|";
        if(item.alocated==false) 
            cout << "     NULL" << "\t|\t" << "Disponivel\t|\t-\t|\t-\t|" << endl;
        else
            cout << "  "<<item.type << "\t|\t" << "Ocupado\t\t|\t"<<item.currentTime<<"\t|\t"<<item.time<<"\t|" << endl;
    } 
    cout<<"  ---------------------------------------------------------------------------------------"<<endl;

}
