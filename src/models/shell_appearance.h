#ifndef _SHELL_
#define _SHELL_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 20

typedef struct shell_appearance Shell;

struct shell_appearance{
    int   option;
};

Shell* initializeShell(){  //Função de inicialização 
    Shell* shell = (Shell*) malloc(sizeof(Shell));
    shell-> option = 20;

    return shell;
}

void selectShellOption(Shell* shell){
    char str[SIZE];
    printf("\n>> ");
    scanf ( "%20[^\n]", str);

    
    if     (strcmp(str, "help")        == 0) shell->option = 0;
    else if(strcmp(str, "meminfo")     == 0) shell->option = 1;
    else if(strcmp(str, "cpuinfo")     == 0) shell->option = 2;
    else if(strcmp(str, "queueschell") == 0) shell->option = 3;
    else if(strcmp(str, "execute")     == 0) shell->option = 4;
    else if(strcmp(str, "kill -9")     == 0) shell->option = 5;
    else if(strcmp(str, "exit")        == 0) shell->option = 6;
    
    else shell->option = -1; //caso errado 

}

void helpCommand(){
    printf("\n-> help\t\t -> Demonstra quais comandos podem ser executados pelo shell desenvolvido;\n");
    printf("-> meminfo\t -> Detalha quantas unidades de memoria so sistema possui, quantas estão \n\t\t    livres e quantas estao alocadas e para quais processos.\n");
    printf("-> cpuinfo\t -> Detalha qual processo esta em execucao, qual o timestamp e quantum desse.\n");
    printf("-> queueschell\t -> Detalha quais processos estão sendo gerenciados pelo seu sistema, \n\t\t    quais estão em estado de pronto, bloqueado, execucao e/ou sendo criados e finalizados.\n");
    printf("-> execute\t -> Executa a fila de processos definida conforme configuracao previa. \n");
    printf("-> kill -9\t -> Finaliza a execucao do sistema operacional, voltando o mesmo para o \n\t\t    estado inicial, em que os processos estariam ainda em fase de criacao inicial.\n");
}

#endif