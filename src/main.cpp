#include <iostream>
#include <fstream>
#include <string.h>
#include "../include/shell.hpp"
#include "../include/json.hpp"

using namespace std;
using json = nlohmann::json;

int main(){
    Shell shell;
    json processos;
    ifstream("processo.json") >> processos;
    //cout<< processos["processos"]["numProcessos"].dump(4)<<endl;

    while(shell.getOption()!= 6){
        shell.selectedShellOption();
        //setbuf(stdin, NULL); 

        switch(shell.getOption()){
            case 0: // help 
                shell.helpCommand();
            
            break;
            case 1: // meminfo 
                
                cout<<"\n -Detalha quantas unidades de memória so sistema possui, quantas estão livres e quantas estão alocadas e para quais processos.\n";
            
            break;
            case 2: // cpuinfo 
                
                cout<<"\n -Detalha qual processo está em execução, qual o timestamp e quantum desse.\n";
            
            break;
            case 3: // queueschell 
                
                cout<<"\n -Detalha quais processos estão sendo gerenciados pelo seu sistema, quais estão em estado de pronto, bloqueado, execução e/ou sendo criados e finalizados.\n";
            
            break;
            case 4: // execute 
                
                cout<<"\n -Executa a fila de processos definida conforme configuração prévia.\n";
            
            break;
            case 5: // kill -9 
                
                cout<<"\n -Finaliza a execucao do sistema operacional, voltando o mesmo para o estado inicial, em que os processos estariam ainda em fase de criação inicial.\n";
            
            break;
            case 6: // exit 
            
                cout<<"\n -Saindo...\n";
            
            break;
            default:
            
                printf("\n -[ERRO 00] -> O comando informado nao existe.\nTente o comando 'help' para obter ajuda. \n");

        }



    };
    return 0;
}