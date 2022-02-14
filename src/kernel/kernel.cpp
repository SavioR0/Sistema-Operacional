#include "kernel.hpp"

Kernel::Kernel(){
    nlohmann::json hardware_info;
    std::ifstream file;
    file.open(FILENAME);
    if(file.fail()){
        std::cout<<"Erro [00] -> Não iniciar o sistema devido a falta do arquivo: " << FILENAME << ". \n \tVerifique se ele existe e se está correto." << std::endl;
        exit(1);
    } 
    file >> hardware_info;
    this->cpu    = Cpu     ( hardware_info["cores"]    );
    this->memory = Memory  ( hardware_info["segments"] );
    this->storage = Storage( hardware_info["storage"]);
    this->quantum_time = (unsigned int)  hardware_info["quantum_time"] * 1000000; 
}

Cpu*      Kernel::get_cpu_ref()         { return &this->cpu;        }
Memory*   Kernel::get_memory_ref()      { return &this->memory;     }
Storage*  Kernel::get_storage_ref()     { return &this->storage;    }
unsigned int Kernel::get_quantum_time() { return this->quantum_time;}

void Kernel::report_component(const Hadware& component)const{ component.generate_report();  }