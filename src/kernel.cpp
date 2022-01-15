#include "../include/kernel.hpp"
#include "../include/json.hpp"

using json = nlohmann::json;

Kernel::Kernel(){}

void Kernel::initialize(){
    json hardwareInfo;
    ifstream(FileName) >> hardwareInfo;
    this->setCore          ( hardwareInfo["cores"]    );
    this->setBlocksStorage ( hardwareInfo["storage"]  );
    this->setSegments      ( hardwareInfo["segments"] );
    //TODO: Fazer com que seja possivel ler o numero de processos no arquivo ao invés de passar diretamente
    this->setProcess       (15);
    
    this->cpu     = new Cpu     ( this->getCore()          );
    this->storage = new Storage ( this->getBlocksStorage() );
    this->memory  = new Memory  ( this->getSegments()      );
    this->settler = new Settler ( this->getProcess()         );
}


void Kernel::setCore          (int number){this->cores         = number;}
void Kernel::setBlocksStorage (int number){this->blocksStorage = number;}
void Kernel::setSegments      (int number){this->segments      = number;}
void Kernel::setProcess       (int number){this->numProcess    = number;}

int  Kernel::getCore          (){return this->cores;}
int  Kernel::getBlocksStorage (){return this->blocksStorage;}
int  Kernel::getSegments      (){return this->segments;}
int  Kernel::getProcess      (){return this->numProcess;}