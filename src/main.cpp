#include <iostream>
#include <fstream>
#include <string.h>
#include <pthread.h>

#include "kernel/kernel.hpp"
#include "shell/shell.hpp"
#include "scheduler/scheduler.hpp"

#define quantum_time 1.2
 

void* execute(void* scheduler);
void* thread_shell(void* Shell);
void  create_thread(pthread_t *__restrict__ __newthread, const pthread_attr_t *__restrict__ __attr, void *(*__start_routine)(void *), void *__restrict__ __arg);


int main(){
    system("clear");

    Kernel*    kernel    = new Kernel;
    Scheduler* scheduler = new Scheduler(kernel, quantum_time, fifo_policie_string);
    Shell*     shell     = new Shell;

    pthread_t thread_execute_process; 
    pthread_t thread_shell_option; 

    kernel->initialize();

    create_thread(&thread_shell_option, NULL, thread_shell, shell);

    while(shell->get_option()!= -2){
        if(shell->get_execute_status() == true){
            switch(shell->get_option()){
                case 0:                                                                      // 0-> help 
                    shell->help_command();       
                    shell->set_execute_status(false);  
                break; 
                case 1:                                                                      // 1-> meminfo 
                    kernel->memory->print();     
                    shell->message_exit();
                    if(quantum_time <= 1) usleep(1000000);             
                break; 
                case 2:                                                                      // 2-> meminfo 
                    kernel->storage->print();    
                    shell->message_exit();             
                    if(quantum_time <= 1) usleep(1000000);             
                break; 
                case 3:                                                                      // 3-> cpuinfo 
                    kernel->cpu->print();        
                    shell->message_exit();             
                    if(quantum_time <= 1) usleep(1000000);             
                break; 
                case 4:                                                                      // 4-> Load 
                    scheduler->load(); 
                    shell->set_execute_status(false);  
                break; 
                case 5:                                                                      // 5-> queueschell 
                    scheduler->report();
                    shell->message_exit();
                    if(quantum_time <= 1) usleep(1000000);             
                break; 
                case 6:                                                                      // 6-> execute 
                    create_thread(&thread_execute_process, NULL, execute, scheduler); 
                    shell->set_execute_status(false);
                break; 
                case 7:                                                                      // 7-> kill -9 
                    scheduler->restart();
                    shell->set_execute_status(false);   
                break; 
                case 8:                                                                      // 8-> Exit 
                    cout<<"\n -Saindo...\n"; 
                    shell->set_execute_status(false);      
                break;             
                
                default: 
                    cout<<"\n -[ERRO 00] -> O comando informado nao existe.\nTente o comando 'help' para obter ajuda. \n"<< endl;
                    shell->set_execute_status(false); 
            }
            usleep( ( (quantum_time/2) * 1000000) );
        }
    } 
    return 0;
}

void*  execute(void* scheduler){
    Scheduler* assist = (Scheduler*) scheduler;
    assist->execute();
    pthread_exit(NULL);
}
void* thread_shell(void* shell){
    Shell* assist = (Shell*) shell;
    while(assist->get_option()!= -2){ assist->selected_shell_option();  usleep( ( (quantum_time/1.5) * 1000000) ) ;} 
    pthread_exit(NULL);
}
void  create_thread(pthread_t *__restrict__ __newthread, const pthread_attr_t *__restrict__ __attr, void *(*__start_routine)(void *), void *__restrict__ __arg){
    if((pthread_create(__newthread, __attr, __start_routine, __arg) != 0)){
        printf("Erro ao criar a thread.");
        exit(EXIT_FAILURE);
    }
}

  