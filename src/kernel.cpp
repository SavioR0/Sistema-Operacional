#include "../include/kernel.hpp"
#include "../include/json.hpp"

using json = nlohmann::json;

Kernel::Kernel(){}

void Kernel::initialize(){
    json hardware_info;
    ifstream(FileName) >> hardware_info;
    this->set_core              ( hardware_info["cores"]    );
    this->set_blocks_storage    ( hardware_info["storage"]  );
    this->set_segments          ( hardware_info["segments"] );    
    this->storage = new Storage ( this->get_blocks_storage());
    this->memory  = new Memory  ( this->get_segments()      );
    this->cpu     = new Cpu     ( this->get_core()          );
}


void Kernel::set_core           (int number){this->cores         = number;  }
void Kernel::set_blocks_storage (int number){this->blocks_storage = number; }
void Kernel::set_segments       (int number){this->segments      = number;  }
void Kernel::set_process        (int number){this->num_process    = number; }

int  Kernel::get_core           (){return this->cores;          }
int  Kernel::get_blocks_storage (){return this->blocks_storage; }
int  Kernel::get_segments       (){return this->segments;       }
int  Kernel::get_process        (){return this->num_process;    }