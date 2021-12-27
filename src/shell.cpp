#include "../include/shell.hpp"

void Shell::setOption(int op){
    option = op;
}

int Shell::getOption(){
    return option;
}

Shell::Shell(){
    this->setOption(30);
}

void Shell::selectedShellOption(){
    string str;
    cout<<"\n $ ";
    getline( cin, str);// é capaz de ler o dado de entrada até que uma nova linha seja detectada

    if     (str == "help"       ) option = 0;
    else if(str == "meminfo"    ) option = 1;
    else if(str == "cpuinfo"    ) option = 2;
    else if(str == "queueschell") option = 3;
    else if(str == "execute"    ) option = 4;
    else if(str == "kill -9"    ) option = 5;
    else if(str == "exit"       ) option = 6;
    
    else option = -1; //caso errado 

}

void Shell::helpCommand(){
    cout<<"\n-> help\t\t -> Demonstra quais comandos podem ser executados pelo shell desenvolvido;\n"<<endl;
    cout<<"-> meminfo\t -> Detalha quantas unidades de memoria so sistema possui, quantas estão \n\t\t    livres e quantas estao alocadas e para quais processos.\n"<<endl;
    cout<<"-> cpuinfo\t -> Detalha qual processo esta em execucao, qual o timestamp e quantum desse.\n"<<endl;
    cout<<"-> queueschell\t -> Detalha quais processos estão sendo gerenciados pelo seu sistema, \n\t\t    quais estão em estado de pronto, bloqueado, execucao e/ou sendo criados e finalizados.\n"<<endl;
    cout<<"-> execute\t -> Executa a fila de processos definida conforme configuracao previa. \n"<<endl;
    cout<<"-> kill -9\t -> Finaliza a execucao do sistema operacional, voltando o mesmo para o \n\t\t    estado inicial, em que os processos estariam ainda em fase de criacao inicial.\n"<<endl;
}

void Shell::memInfoCommand(){
    
}