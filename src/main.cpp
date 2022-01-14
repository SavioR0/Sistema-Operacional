#include <iostream>
#include <fstream>
#include <string.h>

#include "../include/kernel.hpp"
#include "../include/shell.hpp"


int main(){
    system("clear");
    Settler settler = Settler();

    /*
    Kernel *kernel = new Kernel;
    Shell  *shell = new Shell();

    (*kernel).initialize();

    while( (*shell).getOption()!= 7){
        (*shell).selectedShellOption(); 

        switch((*shell).getOption()){
            case 0: // help 
                (*shell).helpCommand();
            
            break;
            case 1: // meminfo 
                (*kernel).memory->print();
            
            break;
            case 2: //diskInfo
                (*kernel).storage->print();

            break;
            case 3: // cpuinfo 
                
                (*kernel).cpu->print();
            
            break;
            case 4: // queueschell 
                
                cout<<"\n -Detalha quais processos estão sendo gerenciados pelo seu sistema, quais estão em estado de pronto, bloqueado, execução e/ou sendo criados e finalizados.\n";
            
            break;
            case 5: // execute 
                
                cout<<"\n -Executa a fila de processos definida conforme configuração prévia.\n";
            
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
    } */



    return 0;
}


