#include "../include/shell.hpp"

void Shell::set_option(int op){
    option = op;
}

int Shell::get_option(){
    return option;
}

Shell::Shell(){
    this->set_option(30);
}

bool Shell::get_execute_status()   { return this->execute; }
void Shell::set_execute_status(bool value){ this->execute = value;}

void Shell::selected_shell_option(){
    string str;
    cout<<"\n $ ";
    getline( cin, str);

    if     (str == "help"       || str == "0" ) option = 0;  
    else if(str == "meminfo"    || str == "1" ) option = 1; 
    else if(str == "diskinfo"   || str == "2" ) option = 2; 
    else if(str == "cpuinfo"    || str == "3" ) option = 3; 
    else if(str == "load"       || str == "4" ) option = 4; 
    else if(str == "queueschell"|| str == "5" ) option = 5; 
    else if(str == "execute"    || str == "6" ) option = 6;  
    else if(str == "kill -9"    || str == "7" ) option = 7;  
    else if(str == "exit"                     ) option = -2;
    
    this->execute = true;    
    if(str == "x") this->execute = false;


}

void Shell::message_exit(){
    cout<<"\n\n\t Precione 'x' para voltar ao shell." << endl;
}

void Shell::help_command(){
    
    cout << "\x1b[1;92m \n\thelp\t\t \x1b[0m\x1b[3m Demonstra quais comandos podem ser executados pelo shell desenvolvido;\n \x1b[0m" << endl;
    cout << "\x1b[1;92m \n\tmeminfo\t\t \x1b[0m\x1b[3m Detalha quantas unidades de memoria so sistema possui, quantas estão \n\t\t\t livres e quantas estao alocadas e para quais processos.\n \x1b[0m" << endl;
    cout << "\x1b[1;92m \n\tdiskinfo\t \x1b[0m\x1b[3m Detalha qual e quantos blocos estão alocados em disco.\n \x1b[0m" << endl;
    cout << "\x1b[1;92m \n\tcpuinfo\t\t \x1b[0m\x1b[3m Detalha qual processo esta em execucao, qual o timestamp e quantum desse.\n \x1b[0m" << endl;
    cout << "\x1b[1;92m \n\tload\t\t \x1b[0m\x1b[3m Carrega informações de processos na CPU.\n \x1b[0m" << endl;
    cout << "\x1b[1;92m \n\tqueueschell\t \x1b[0m\x1b[3m Detalha quais processos estão sendo gerenciados pelo seu sistema, \n\t\t\t quais estão em estado de pronto, bloqueado, execucao e/ou sendo criados e finalizados. \x1b[0m" << endl;
    cout << "\x1b[1;92m \n\texecute\t\t \x1b[0m\x1b[3m Executa a fila de processos definida conforme configuracao previa. \n \x1b[0m" << endl;
    cout << "\x1b[1;92m \n\tkill -9\t\t \x1b[0m\x1b[3m Finaliza a execucao do sistema operacional, voltando o mesmo para o \n\t\t\t estado inicial, em que os processos estariam ainda em fase de criacao inicial.\n \x1b[0m" << endl;
    cout << "\x1b[1;92m \n\texit\t\t \x1b[0m\x1b[3m Finaliza a execução do  programa como um todo.\n \x1b[0m" << endl;
}

void Shell::mem_info_command(){
    
}