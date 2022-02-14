#include "shell.hpp"

void Shell::help_command(){    
    std::cout << "\x1b[1;92m \n\thelp\t\t \x1b[0m\x1b[3m Demonstra quais comandos podem ser executados pelo shell desenvolvido;\n \x1b[0m" << std::endl;
    std::cout << "\x1b[1;92m \n\tmeminfo\t\t \x1b[0m\x1b[3m Detalha quantas unidades de memoria so sistema possui, quantas estão \n\t\t\t livres e quantas estao alocadas e para quais processos.\n \x1b[0m" << std::endl;
    std::cout << "\x1b[1;92m \n\tdiskinfo\t \x1b[0m\x1b[3m Detalha qual e quantos blocos estão alocados em disco.\n \x1b[0m" << std::endl;
    std::cout << "\x1b[1;92m \n\tcpuinfo\t\t \x1b[0m\x1b[3m Detalha qual processo esta em execucao, qual o timestamp e quantum desse.\n \x1b[0m" << std::endl;
    std::cout << "\x1b[1;92m \n\tload\t\t \x1b[0m\x1b[3m Carrega informações de processos na CPU.\n \x1b[0m" << std::endl;
    std::cout << "\x1b[1;92m \n\tqueueschell\t \x1b[0m\x1b[3m Detalha quais processos estão sendo gerenciados pelo seu sistema, \n\t\t\t quais estão em estado de pronto, bloqueado, execucao e/ou sendo criados e finalizados. \x1b[0m" << std::endl;
    std::cout << "\x1b[1;92m \n\texecute\t\t \x1b[0m\x1b[3m Executa a fila de processos definida conforme configuracao previa. \n \x1b[0m" << std::endl;
    std::cout << "\x1b[1;92m \n\tkill -9\t\t \x1b[0m\x1b[3m Finaliza a execucao do sistema operacional, voltando o mesmo para o \n\t\t\t estado inicial, em que os processos estariam ainda em fase de criacao inicial.\n \x1b[0m" << std::endl;
    std::cout << "\x1b[1;92m \n\texit\t\t \x1b[0m\x1b[3m Finaliza a execução do  programa como um todo.\n \x1b[0m" << std::endl;
}
void Shell::message_exit(){
    std::cout<<"\n\n\t Precione 'x + Enter' para voltar ao shell." << std::endl;
}