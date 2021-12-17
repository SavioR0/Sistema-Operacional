#ifndef _SHELL_
#define _SHELL_

typedef struct shell_appearance Shell;

struct shell_appearance{
    int   option;
};

Shell* initializeShell();  //Função de inicialização 
void selectShellOption(Shell* shell);
void helpCommand();


#endif