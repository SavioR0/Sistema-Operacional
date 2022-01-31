#include "mfp.hpp"

//Constutores
MFP::MFP(list<Process> list_process, Cpu* cpu_ref, Memory* memory_ref, Storage* storage_ref, float quantum_time){
    this->cpu_ref = cpu_ref;
    this->memory_ref = memory_ref;
    this->storage_ref = storage_ref;
    this->quantum_time = quantum_time;
    this->distribution_list(list_process);
}
MFP::MFP(){}

void MFP::distribution_list(list<Process> processes){
    if(processes.empty()){
        cout << "\n\nNão foi possível concluir a operação, lista de processos vazia, retornando." << endl;
        return;
    }
    Process* current_process = new Process();

    while(!processes.empty()){
        current_process = &processes.front();
             if(current_process->get_priority() == 1) this->priority1.push_back( *current_process );
        else if(current_process->get_priority() == 2) this->priority2.push_back( *current_process );
        else if(current_process->get_priority() == 3) this->priority3.push_back( *current_process );
        else if(current_process->get_priority() == 4) this->priority4.push_back( *current_process );
        current_process = NULL;
        processes.pop_front();
    }
    free(current_process);
}


void MFP::execute(){
    this->execute_high_priority();
    this->execute_processes();
}



void MFP::report(){
    system("clear");
    cout<<"   ------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"   |\t\t\t\t\t    LISTA DE PROCESSOS    \t\t\t\t\t\t\t\t|"<<endl;
    cout<<"   ------------------------------------------------------------------------------------------------------------------------------"<<endl;
    if(!this->priority1.empty() || !this->priority2.empty() || !this->priority3.empty() || !this->priority4.empty() || !this->block.empty() || !this->finalized.empty()){
        cout<<"   |\tID\t|\tEstado\t\t|\t  Tipo     \t|\tTimestamp\t|\tCiclos    |\tPrioridade\t|"<<endl;
        cout<<"   ------------------------------------------------------------------------------------------------------------------------------"<<endl;
        for(Process item : this->priority4){
            cout<<"   |\t" << item.get_id() << "\t|\t" << item.get_status() << "    \t|\t"<< item.get_type() <<"\t|\t    " << item.get_timestamp() << "    \t|\t" << item.get_cyles() << "\t  |\t    " << item.get_priority()<<"\t\t|" << endl;
        }
        for(Process item : this->priority3){
            cout<<"   |\t" << item.get_id() << "\t|\t" << item.get_status() << "    \t|\t"<< item.get_type() <<"\t|\t    " << item.get_timestamp() << "    \t|\t" << item.get_cyles() << "\t  |\t    " << item.get_priority()<<"\t\t|" << endl;
        }
        for(Process item : this->priority2){
            cout<<"   |\t" << item.get_id() << "\t|\t" << item.get_status() << "    \t|\t"<< item.get_type() <<"\t|\t    " << item.get_timestamp() << "    \t|\t" << item.get_cyles() << "\t  |\t    " << item.get_priority()<<"\t\t|" << endl;
        }
        for(Process item : this->priority1){
            cout<<"   |\t" << item.get_id() << "\t|\t" << item.get_status() << "    \t|\t"<< item.get_type() <<"\t|\t    " << item.get_timestamp() << "    \t|\t" << item.get_cyles() << "\t  |\t    " << item.get_priority()<<"\t\t|" << endl;
        }
        for(Process item : this->block){
            cout<<"   |\t" << item.get_id() << "\t|\t" << item.get_status() << "    \t|\t"<< item.get_type() <<"\t|\t    " << item.get_timestamp() << "    \t|\t" << item.get_cyles() << "\t|" << endl;
        }
        for(Process item : this->finalized){
            cout<<"   |\t" << item.get_id() << "\t|\t" << item.get_status() << "    \t|\t"<< item.get_type() <<"\t|\t    " << item.get_timestamp() << "    \t|\t" << "--" << "\t|" << endl;
        }
    }else {
        cout<< " +\t\t\tEMPTY\t\t\t+"<<endl;
    }
    cout<<"   ------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"\n\nRANGE: " << this->range_tokens<<endl;
    int soma = 0;
    for(Process item : this->priority1){
        soma += (int) item.get_tokens().size();
        cout<<"\tProcesso: "<<item.get_id()<<"\tTamanho: "<< (int) item.get_tokens().size()<<endl;
    
    }
    cout<<"\n\nSoma: " <<soma;

    cout<<"\n"<<endl;
    if(this->fifo_policie != NULL ) this->fifo_policie->report_fifo();
}