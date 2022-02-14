#include "memory.hpp"

void Memory::header_report()const{
    std::cout<<"\n\n  |-------------------------------------------------------------------------------------------------------------|"<<std::endl;
    std::cout<<"  |\t\t\t\t\t\tInformações da Memória\t\t\t\t\t\t|"<<std::endl;
    std::cout<<"  |-------------------------------------------------------------------------------------------------------------|"<<std::endl;
    std::cout<<"  |  Segmento   |\tId Processo\t|\t\tEstado\t\t|\tTempo\t|\tTempo Máximo\t|" << std::endl;
    std::cout<<"  |-------------------------------------------------------------------------------------------------------------|"<<std::endl;

}
void print_line_memory( int segment){
    std::cout<<"  |\t" << segment <<"\t|\t    None   \t|\t   Disponível   \t|\tNone\t|\t   None   \t|"<<std::endl;
}
void print_line_memory(Hadware::ContentData data, int segment){
    std::cout<<"  |\t" << segment <<"\t|\t    "<< data.id <<"   \t|\t   Indisponível    \t|\t"<< data.current_time<<"\t|\t    " << data.time << "    \t|" <<std::endl;
}

void Memory::generate_report() const {
    system("clear");
    this->header_report();
    this->print_list();


    std::cout<<"  |-------------------------------------------------------------------------------------------------------------|"<<std::endl;
}


void Memory::print_list() const {
    for(int current_segment = 0; current_segment < this->segments; current_segment++ ){
        if(!ram[current_segment].alocated) print_line_memory(current_segment);
        else print_line_memory(ram[current_segment], current_segment);
    }
}
