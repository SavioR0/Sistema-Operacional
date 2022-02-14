#include "storage.hpp"

void Storage::header_report()const{
    std::cout<<"\n\n  |-------------------------------------------------------------------------------------------------------------|"<<std::endl;
    std::cout<<"  |\t\t\t\t\t\tInformações do Disco\t\t\t\t\t\t|"<<std::endl;
    std::cout<<"  |-------------------------------------------------------------------------------------------------------------|"<<std::endl;
    std::cout<<"  |\tDisco\t|\tId Processo\t|\t\tEstado\t\t|\tTempo\t|\tTempo Máximo\t|" << std::endl;
    std::cout<<"  |-------------------------------------------------------------------------------------------------------------|"<<std::endl;

}
void print_line_storage( int segment){
    std::cout<<"  |\t" << segment <<"\t|\t    None   \t|\t   Disponível   \t|\tNone\t|\t   None   \t|"<<std::endl;
}
void print_line_storage(Hadware::ContentData data, int segment){
    std::cout<<"  |\t" << segment <<"\t|\t    "<< data.id <<"   \t|\t   Indisponível    \t|\t"<< data.current_time<<"\t|\t    " << data.time << "    \t|" <<std::endl;
}

void Storage::generate_report() const {
    system("clear");
    this->header_report();
    this->print_list();


    std::cout<<"  |-------------------------------------------------------------------------------------------------------------|"<<std::endl;
}


void Storage::print_list() const {
    int current_blcok = 0;
    for(Hadware::ContentData item : this->blocks){
        if(!item.alocated) print_line_storage(current_blcok);
        else print_line_storage(item, current_blcok);
        current_blcok++;
    }
}
