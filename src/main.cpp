#include <iostream>
#include <fstream>
#include <string.h>
#include <pthread.h>

#include "../include/kernel.hpp"
#include "../include/shell.hpp"
#include "../include/scheduler.hpp"


void*  execute(void* scheduler);

int main(){
    system("clear");

    Kernel*    kernel    = new Kernel;
    Scheduler* scheduler = new Scheduler(kernel);
    Shell*     shell     = new Shell;

    pthread_t thread_execute_process; 

    kernel->initialize();
    


    while( shell->getOption()!= -1){
        shell->selectedShellOption(); 
        
            switch(shell->getOption()){
                case 0: shell->helpCommand();           break; // help
                case 1: kernel->memory->print();        break; // meminfo
                case 2: kernel->storage->print();       break; // meminfo
                case 3: kernel->cpu->print();           break; // cpuinfo
                case 4: scheduler->read_processes();    break; // Load
                case 5: scheduler->report();            break; // queueschell
                case 6:    
                    if((pthread_create(&thread_execute_process, NULL, execute, scheduler) != 0)){
                        printf("Erro ao criar a thread.");
                        exit(EXIT_FAILURE);
                    }  
                break; // execute
                case 7:                                 break; // kill -9
                case 8: cout<<"\n -Saindo...\n";        break; // Exit            
                default:
                    cout<<"\n -[ERRO 00] -> O comando informado nao existe.\nTente o comando 'help' para obter ajuda. \n"<< endl;    
            }
    } 




    return 0;
}

void*  execute(void* scheduler){
    Scheduler* assist = (Scheduler*) scheduler;
    assist->executeProcesses();
    pthread_exit(NULL);
}

  