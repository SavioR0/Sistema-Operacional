#include <stdio.h>
#include <stdlib.h>
#include "../include/shell.h"

int main(){
    // Declaração das variáveis
    Shell* shell;

    //Inicialização das Variáveis
    shell = initializeShell();

    do{
        selectShellOption(shell);
        setbuf(stdin, NULL);
        
        switch(shell->option){
            case 0: // help 
                
                helpCommand();
            
            break;
            case 1: // meminfo 
                
                printf("\n -Detalha quantas unidades de memória so sistema possui, quantas estão livres e quantas estão alocadas e para quais processos.\n");
            
            break;
            case 2: // cpuinfo 
                
                printf("\n -Detalha qual processo está em execução, qual o timestamp e quantum desse.\n");
            
            break;
            case 3: // queueschell 
                
                printf("\n -Detalha quais processos estão sendo gerenciados pelo seu sistema, quais estão em estado de pronto, bloqueado, execução e/ou sendo criados e finalizados.\n");
            
            break;
            case 4: // execute 
                
                printf("\n -Executa a fila de processos definida conforme configuração prévia.\n");
            
            break;
            case 5: // kill -9 
                
                printf("\n -Finaliza a execucao do sistema operacional, voltando o mesmo para o estado inicial, em que os processos estariam ainda em fase de criação inicial.\n");
            
            break;
            case 6: // exit 
            
                printf("\n -Saindo...\n");
            
            break;
            default:
            
                printf("\n -[ERRO 00] -> O comando informado nao existe.\nTente o comando 'help' para obter ajuda. \n");

        }



    }while(shell->option != 6);

    return 0;
}