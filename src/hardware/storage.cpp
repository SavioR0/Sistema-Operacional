#include "../../include/hardware/storage.hpp"

//Contrutor
Storage::Storage(int size){
    this->size_blocks = size;
    for(int i = 0; i < size; i++){
        BlockData* assist = new BlockData;
        /* assist->key = 0;
        assist->type = "";
        assist->time = 0; */
        assist->current_time=0;
        assist->alocated = false;
        this->blocks.push_back(*assist);
        free(assist);
    }
}

// Funções auxiliares
int Storage::check_time(int** ids){
    int size = 0;
    *ids = (int*) malloc(sizeof(int));
    for(int i = 0; i < this->size_blocks; i++){
        if(this->blocks.front().alocated == true)
            if(this->blocks.front().current_time >= this->blocks.front().time){
                if(size == 0){
                    *ids[0] = this->blocks.front().key;
                    size++;
                }else{
                   *ids = (int*) realloc(*ids, (size + 1) * sizeof(int));
                   (*ids)[size] =  this->blocks.front().key;
                   size++;
                }
            }
        this->blocks.push_back( this->blocks.front());
        this->blocks.pop_front();
    }
    return size;
}
void Storage::add_time_storage(){
    for(int i = 0 ; i < this->size_blocks; i++){
        if(this->blocks.front().alocated == true)
            this->blocks.front().current_time++;
        blocks.push_back(blocks.front());
        blocks.pop_front();
    }
}

//Funções de gerenciamento
void Storage::insert_block_data(int key, string type, int random_number){
    if(allocated_blocks == size_blocks){
        cout<<"Erro [012] -> Não foi possível adicionar pois não há espaço suficiente" << endl;
        return;
    }
    BlockData* assist = new BlockData;
    assist->key         = key;
    assist->type        = type;
    assist->time        = random_number;
    assist->current_time = 0;
    assist->alocated    = true;
    this->insert_storage(assist);
    free(assist);
}


int Storage::insert_storage(BlockData* bd){

    for( int i = 0 ; i< this->size_blocks; i++){
        if(blocks.front().alocated == false){
            blocks.pop_front();
            blocks.push_front(*bd);
            allocated_blocks++;
            return 1;
        }
        blocks.push_back(blocks.front());
        blocks.pop_front();
    }
    
    return 0;
}




int Storage::remove_storage(int id ){
    BlockData bd;
    for(int i = 0; i < this->size_blocks; i++){
       if(id == blocks.front().key){
            if(blocks.front().alocated == false)
                return 0;
            blocks.front().alocated=false; 
            blocks.front().current_time = 0;
            this->allocated_blocks--;
       }else{
            blocks.push_back(blocks.front());
            blocks.pop_front();
       }
    }
    return 1;
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
            cout << "  |\t" << item.key << "\t|" << "  "<<item.type << "\t|\t" << "Ocupado\t\t|\t"<<item.current_time<<"\t|\t"<<item.time<<"\t|" << endl;
    } 
    cout<<"  ---------------------------------------------------------------------------------------"<<endl;

}
