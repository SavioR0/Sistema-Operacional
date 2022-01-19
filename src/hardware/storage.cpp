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

int Storage::insertStorage(BlockData* bd){
    if(allocated_blocks == size)
        return 0;
    for( int i = 0 ; i< this->size; i++){
        if(blocks.front().alocated == false){
            blocks.pop_front();
            blocks.push_front(*bd);
            blocks.front().alocated= true;
            blocks.front().currentTime= 0;
            allocated_blocks++;
            return 1;
        }
        blocks.push_back(blocks.front());
        blocks.pop_front();
    }
    
    return 0;
}


int Storage::check_time(int** ids){
    int sizee = 0;
    *ids = (int*) malloc(sizeof(int));
    for(int i = 0; i < this->size; i++){
        if(this->blocks.front().alocated == true)
            if(this->blocks.front().currentTime >= this->blocks.front().time){
                if(sizee == 0){
                    *ids[0] = this->blocks.front().key;
                    sizee++;
                }else{
                   *ids = (int*) realloc(*ids, (sizee + 1) * sizeof(int));
                   (*ids)[sizee] =  this->blocks.front().key;
                   sizee++;
                }
            }
    }
    return sizee;
}

int Storage::removeStorage(int id ){
    BlockData bd;
    for(int i = 0; i < this->size; i++){
       if(id == blocks.front().key){
            if(blocks.front().alocated == false)
                return 0;
            blocks.front().alocated=false; 
            blocks.front().currentTime = 0;
            allocated_blocks--;
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
    cout<<"  |\t\t\t\t      STORAGE\t\t\t\t\t\t|"<<endl;
    cout<<"  ---------------------------------------------------------------------------------------"<<endl;
    cout<<"  ---------------------------------------------------------------------------------------"<<endl;
    cout<<"  |    ID\t|     Valor\t|\t Status\t\t|   Tempo\t|   Tempo maximo\t|"<<endl;
    cout<<"  ---------------------------------------------------------------------------------------"<<endl;
    for( BlockData item : this->blocks ){
        
        if(item.alocated==false) 
            cout << "  |\t" << 0 << "\t|" << "     NULL" << "\t|\t" << "Disponivel\t|\t-\t|\t-\t|" << endl;
        else
            cout << "  |\t" << item.key << "\t|" << "  "<<item.type << "\t|\t" << "Ocupado\t\t|\t"<<item.currentTime<<"\t|\t"<<item.time<<"\t|" << endl;
    } 
    cout<<"  ---------------------------------------------------------------------------------------"<<endl;

}
