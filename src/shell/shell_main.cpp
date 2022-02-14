#include "shell.hpp"
#include <pthread.h>
#include <unistd.h>

void  create_thread(pthread_t *__restrict__ __newthread, const pthread_attr_t *__restrict__ __attr, void *(*__start_routine)(void *), void *__restrict__ __arg){
    if((pthread_create(__newthread, __attr, __start_routine, __arg) != 0)){
        printf("Erro ao criar a thread.");
        exit(EXIT_FAILURE);
    }
}
void* thread_shell(void* shell){
    Shell* assist = (Shell*) shell;
    while(assist->get_selected_option() != -2){ assist->select_option();  usleep(250000)  ; } 
    pthread_exit(NULL);
}
void*  execute(void* scheduler){
    Scheduler* assist = (Scheduler*) scheduler;
    assist->execute_list_processes();
    pthread_exit(NULL);
}

void Shell::select_option(){
    std::string str;
    std::cout<<"\n $ ";
    std::cin >> str;

    if     (str == "help"       || str == "0" ) this->selected_option = 0;  
    else if(str == "meminfo"    || str == "1" ) this->selected_option = 1; 
    else if(str == "diskinfo"   || str == "2" ) this->selected_option = 2; 
    else if(str == "cpuinfo"    || str == "3" ) this->selected_option = 3; 
    else if(str == "load"       || str == "4" ) this->selected_option = 4; 
    else if(str == "queueschell"|| str == "5" ) this->selected_option = 5; 
    else if(str == "execute"    || str == "6" ) this->selected_option = 6;  
    else if(str == "kill -9"    || str == "7" ) this->selected_option = 7;  
    else if(str == "exit"                     ) this->selected_option = -2;
    
    this->ignore = false;    
    if(str == "x") this->ignore = true;
}

void Shell::init_ref(){
    this->cpu_ref = this->kernel_ref->get_cpu_ref();
    this->memory_ref = this->kernel_ref->get_memory_ref();
    this->storage_ref = this->kernel_ref->get_storage_ref();
}

void Shell::start_os(){
    this->init_ref();
    pthread_t thread_shell_option; 
    pthread_t thread_execute_process; 

    create_thread(&thread_shell_option, NULL, thread_shell, this);

    while(this->selected_option  != -2){
        if(this->ignore) continue;
            switch( this->selected_option ){
                case 0:                                                                      // 0-> help 
                    this->help_command();       
                    this->ignore = true;  
                break; 
                case 1:                                                                      // 1-> meminfo 
                    this->kernel_ref->report_component(*memory_ref);
                    this->message_exit();
                break; 
                case 2:                                                                      // 2-> meminfo 
                    this->kernel_ref->report_component(*storage_ref);    
                    this->message_exit();             
                break; 
                case 3:                                                                      // 3-> cpuinfo 
                    this->kernel_ref->report_component(*cpu_ref);        
                    this->message_exit();             
                break; 
                case 4:                                                                      // 4-> Load 
                    this->scheduler_ref->load_list_processes(); 
                    this->ignore = true;  
  
                break; 
                case 5:                                                                      // 5-> queueschell 
                    if(this->scheduler_ref->report_processes())
                        this->message_exit();
                    else              
                        this->ignore = true;  
                break; 
                case 6:                                                                      // 6-> execute 
                    create_thread(&thread_execute_process, NULL, execute, scheduler_ref); 
                    this->ignore = true;  
                break; 
                /*case 7:                                                                      // 7-> kill -9 
                    scheduler->restart();
                    shell->set_execute_status(false);   
                break; 
                case 8:                                                                      // 8-> Exit 
                    cout<<"\n -Saindo...\n"; 
                    shell->set_execute_status(false);      
                break;    */         
                
                default: 
                    std::cout<<"\n -[ERRO 00] -> O comando informado nao existe.\nTente o comando 'help' para obter ajuda. \n"<< std::endl;
                    this->ignore = true; 
            }
            usleep( 500000 );
        
    } 
}