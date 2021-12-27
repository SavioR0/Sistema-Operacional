#include "../include/kernel.hpp"
#include "../include/json.hpp"

using json = nlohmann::json;

Kernel::Kernel(){}

void Kernel::initialize(){
    json hardwareInfo;
    ifstream(FileName) >> hardwareInfo;
    this->setCore          ( hardwareInfo["cores"]   );
    this->setBlocksStorage ( hardwareInfo["storage"] );
    
    this->cpu     = new Cpu( this->getCore() );
    this->storage = new Storage( this->getBlocksStorage() );

}


void Kernel::setCore          (int number){this->cores         = number;}
void Kernel::setBlocksStorage (int number){this->blocksStorage = number;}

int  Kernel::getCore          (){return this->cores;}
int  Kernel::getBlocksStorage (){return this->blocksStorage;}