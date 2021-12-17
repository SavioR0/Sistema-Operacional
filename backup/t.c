#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void selectOption(char option[20],int *numpt){
    /* printf("Number: %d\n", *numpt);
    (*numpt) = 10;
    printf("Option: %s\n", option); */
    (*numpt) =-1;
    
    if(strcmp(option, "help") == 0)
        (*numpt) = 0;
    else if(strcmp(option, "meminfo") == 0)
        (*numpt) = 1;
    else if(strcmp(option, "cpuinfo") == 0)
        (*numpt) = 2;
    else if(strcmp(option, "queueschell") == 0)
        (*numpt) = 3;
    else if(strcmp(option, "execute") == 0)
        (*numpt) = 4;
    else if(strcmp(option, "kill -9") == 0)
        (*numpt) = 5;
    else if(strcmp(option, "exit") == 0)
        (*numpt) = 6;
}

void helpCommand(){
    printf("\n-> help\t\t -> Demonstra quais comandos podem ser executados pelo shell desenvolvido;\n");
    printf("-> meminfo\t -> Detalha quantas unidades de memoria so sistema possui, quantas estão \n\t\t    livres e quantas estao alocadas e para quais processos.\n");
    printf("-> cpuinfo\t -> Detalha qual processo esta em execucao, qual o timestamp e quantum desse.\n");
    printf("-> queueschell\t -> Detalha quais processos estão sendo gerenciados pelo seu sistema, \n\t\t    quais estão em estado de pronto, bloqueado, execucao e/ou sendo criados e finalizados.\n");
    printf("-> execute\t -> Executa a fila de processos definida conforme configuracao previa. \n");
    printf("-> kill -9\t -> Finaliza a execucao do sistema operacional, voltando o mesmo para o \n\t\t    estado inicial, em que os processos estariam ainda em fase de criacao inicial.\n");
}

int main(){
    char option[20];
    int number = 0;
    int *numpt;
    numpt = &number;

    /*Compara o conteudo das duas string,se forem iguais, retorna 0*/
    while (number != 6){
        printf("\n$");
        gets(option);

        selectOption(option, numpt);
        switch (number){
            case 0: /* help */
                helpCommand();
                break;
            case 1: /* meminfo */
                printf("\n -Detalha quantas unidades de memória so sistema possui, quantas estão livres e quantas estão alocadas e para quais processos.\n");
                break;
            case 2: /* cpuinfo */
                printf("\n -Detalha qual processo está em execução, qual o timestamp e quantum desse.\n");
                break;
            case 3: /* queueschell */
                printf("\n -Detalha quais processos estão sendo gerenciados pelo seu sistema, quais estão em estado de pronto, bloqueado, execução e/ou sendo criados e finalizados.\n");
                break;
            case 4: /* execute */
                printf("\n -Executa a fila de processos definida conforme configuração prévia.\n");
                break;
            case 5: /* kill -9 */
                printf("\n -Finaliza a execucao do sistema operacional, voltando o mesmo para o estado inicial, em que os processos estariam ainda em fase de criação inicial.\n");
                break;
            case 6: /* exit */
                printf("\n -Saindo...\n");
                break;
            default:
                printf("\n -[ERROR] Comando inexistente\n");
                break;
        }
    }
    

    return 0;
}