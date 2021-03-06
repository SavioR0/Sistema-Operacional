# Sistema-Operacional

## Introdução

Atividade da disciplica de Sistema operacionais. O objetivo desse trabalho é simular um sistema operacional em C++. Nesse sentido foram simulados os hadwares - memória, CPU e disco.

Os processos "executados" pelo sistema Operacional são lidos de um arquivo json contendo todas as informações para a execução dos processos. Para a simulação foi necessário criar um escalonador de processos responsável por gerenciar toda a fila de processos. 

- Gustavo Rodrigues Barcelos
- Sávio Rodrigues

## Instalação, compilação e execução

- ### Instalação
    Para instalar o reposiório use o comando: (Necessário git)
    ~~~
    git clone https://github.com/SavioR0/Sistema-Operacional.git
    ~~~
- ### Compilação
    Abra o diretório baixado:
    ~~~
    cd Sistema-Operacional
    ~~~
    Execute o seguinte comando para compilar:
    ~~~
    make
    ~~~

- ### Execução
    Após baixar e compilar o arquvo execute-o com o comando:
    ~~~
    make run
    ~~~

    Inicialmente o quantum - tempo respeitado pelo escalonador para a execução dos processos- é setado com um valor fixo de 1 segundo(s). Caso seja necessario alteração para melhor visualização dos resultados, faça a modificação no arquivo "main.cpp" na linha 10.
- ### Comando para executar todos os passos acima:
    ~~~
    git clone https://github.com/SavioR0/Sistema-Operacional.git && cd Sistema-Operacional && make $$ make run
    ~~~
- ### Informações do compilador
    ~~~
    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
    ~~~

## Estrutura de pastas
<br/>
<p align="center">

![definaçãopasta](https://user-images.githubusercontent.com/62517334/150654451-4aa15ef2-1bc1-4763-a4af-ed369939343b.svg)

</p>
