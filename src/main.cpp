#include <iostream>
#include <fstream>
#include <string.h>
#include <pthread.h>

#include "../include/kernel.hpp"
#include "../include/shell.hpp"

void * shellop(void* shell){
    
    Shell* aux = (Shell*) shell;
    while( aux->getOption()!= -1){
        aux->selectedShellOption(); 
    }
    pthread_exit(NULL);
}


int main(){
    system("clear");

    Kernel *kernel = new Kernel;
    Shell  *shell = new Shell();
    pthread_t thread_shell;

    kernel->initialize();
    

    if((pthread_create(&thread_shell, NULL,  shellop   , shell) != 0)){
        printf("Deu bizil");
        exit(EXIT_FAILURE);
    }

    cout<<"Vim pra ca" << endl;

    while( shell->getOption()!= -1){
  

        if(shell->execute == true){
            shell->execute = false;
            switch(shell->getOption()){
                case 0: shell->helpCommand();       break; // help
                case 1: kernel->memory->print();    break; // meminfo
                case 2: kernel->storage->print();   break; // meminfo
                case 3: kernel->cpu->print();       break; // cpuinfo
                case 4: kernel->cpu->loadProcess(); break; // Load
                case 5: kernel->cpu->printProcess();break; // queueschell
                case 6:                             break; // execute
                case 7:                             break; // kill -9
                case 8: cout<<"\n -Saindo...\n";    break; // Exit            
                default:
                    cout<<"\n -[ERRO 00] -> O comando informado nao existe.\nTente o comando 'help' para obter ajuda. \n"<< endl;    
            }
        }
    } 
    cout<<"Finalizei" << endl;




    return 0;
}


