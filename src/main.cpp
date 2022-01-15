#include <iostream>
#include <fstream>
#include <string.h>

#include "../include/kernel.hpp"
#include "../include/shell.hpp"


int main(){
    system("clear");

    Kernel *kernel = new Kernel;
    Shell  *shell = new Shell();

    (*kernel).initialize();
    (*kernel).initialize();


   /* (*kernel).settler->executeQueue();
    (*kernel).settler->printQueue();*/
     


    while( (*shell).getOption()!= -1){
        (*shell).selectedShellOption(); 

        switch((*shell).getOption()){
            case 0: (*shell).helpCommand();     break; // help
            case 1: (*kernel).memory->print();  break; // meminfo
            case 2: (*kernel).storage->print(); break; // meminfo
            case 3: (*kernel).cpu->print();     break; // cpuinfo
            case 4: // queueschell 
                (*kernel).cpu->loadProcess();
                
                //cout<<"\n -Detalha quais processos estão sendo gerenciados pelo seu sistema, quais estão em estado de pronto, bloqueado, execução e/ou sendo criados e finalizados.\n";
            
            break;
            case 5: // execute 
                (*kernel).cpu->printProcess();
                
                //cout<<"\n -Executa a fila de processos definida conforme configuração prévia.\n";
            
            break;
            case 6: // kill -9 
                
                cout<<"\n -Finaliza a execucao do sistema operacional, voltando o mesmo para o estado inicial, em que os processos estariam ainda em fase de criação inicial.\n";
            
            break;
            case 7: // exit 
            
                cout<<"\n -Saindo...\n";
            
            break;
            default:
            
                printf("\n -[ERRO 00] -> O comando informado nao existe.\nTente o comando 'help' para obter ajuda. \n");

        }
    } 



    return 0;
}


