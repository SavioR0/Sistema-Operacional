#include <iostream>
#include <fstream>
#include <string.h>
#include <pthread.h>

#include "../include/kernel.hpp"
#include "../include/shell.hpp"
#include "../include/scheduler.hpp"


void*  execute(void* scheduler);
void* thread_shell(void* Shell);


int main(){
    system("clear");

    Kernel*    kernel    = new Kernel;
    Scheduler* scheduler = new Scheduler(kernel);
    Shell*     shell     = new Shell;

    pthread_t thread_execute_process; 
    pthread_t thread_shell_option; 


    kernel->initialize();
    

    //shell->selected_shell_option();
    if((pthread_create(&thread_shell_option, NULL, thread_shell, shell) != 0)){
        cout<<"Entrei"<<endl;
        printf("Erro ao criar a thread.");
        exit(EXIT_FAILURE);
    }   

    while(shell->get_option()!= -2){
        if(shell->get_execute_status() == true){
            switch(shell->get_option()){
                case 0: shell->help_command(); shell->set_execute_status(false);        break; // help
                case 1: kernel->memory->print(); shell->message_exit();                 break; // meminfo
                case 2: kernel->storage->print(); shell->message_exit();                                       break; // meminfo
                case 3: kernel->cpu->print();   shell->message_exit();                                           break; // cpuinfo
                case 4: scheduler->read_processes(); shell->set_execute_status(false);  break; // Load
                case 5: scheduler->report(); shell->message_exit();                                            break; // queueschell
                case 6:    
                    if((pthread_create(&thread_execute_process, NULL, execute, scheduler) != 0)){
                        printf("Erro ao criar a thread.");
                        exit(EXIT_FAILURE);
                    }  
                    shell->set_execute_status(false);
                                                                                        break; // execute
                case 7:                          shell->set_execute_status(false);      break; // kill -9
                case 8: cout<<"\n -Saindo...\n"; shell->set_execute_status(false);      break; // Exit            
/*                 default:
                    cout<<"\n -[ERRO 00] -> O comando informado nao existe.\nTente o comando 'help' para obter ajuda. \n"<< endl;  */   
            }
            usleep(300000);
        }
    } 




    return 0;
}

void*  execute(void* scheduler){
    Scheduler* assist = (Scheduler*) scheduler;
    assist->execute_processes();
    pthread_exit(NULL);
}
void* thread_shell(void* shell){
    Shell* assist = (Shell*) shell;
    while(assist->get_option()!= -2){ assist->selected_shell_option();  usleep(350000);} 
    pthread_exit(NULL);
}

  