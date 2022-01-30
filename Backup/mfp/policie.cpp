#include "mfp.hpp"

//O sistema de bilhete funciona da seguinte forma: temos um vetor, e as casas do vetor são os endereços- EX: tokens[0] significa o bilhete 0
// O conteudo (que incialmente é -1) é preenchido com o id do processo que sortear o bilhete - EX: Processo 15 ganhou o bilhete 0, então tokens[0]=15
//Quando o bilhete é sorteado, o processo dono do bilhete terá todos os seus cancelados. EX = processo 15 tem tokens[0] = 15 e tokens[20] = 15, ambos serão anulados, tokens[0] = -1 e tokens[20] = -1, ou seja , o 15 não tem mais bilhetes.


//Funções que inicializam a aplicação da politica
void MFP::change_empty_lists(){
    this->empty_lists = true;
}

void distribution_list(list<Process>* processes,list<Process>* priority0, list<Process>* priority1,
    list<Process>* priority2, list<Process>* priority3, list<Process>* priority4){
        
    while(!(*processes).empty()){
        if((*processes).front().get_priority() == 4)      (*priority4).push_back((*processes).front());
        else if((*processes).front().get_priority() == 3) (*priority3).push_back((*processes).front());
        else if((*processes).front().get_priority() == 2) (*priority2).push_back((*processes).front());
        else if((*processes).front().get_priority() == 1) (*priority1).push_back((*processes).front());
        else if((*processes).front().get_priority() == 0) (*priority0).push_back((*processes).front());

        (*processes).pop_front();
    }   
    
}

void add_main_process(list<Process>* processes, list<Process>* priority0,
        list<Process>* priority1, list<Process>* priority2, list<Process>* priority3, list<Process>* priority4){
    
    //Pode não ter nenhum processo nas filas de prioridade no começo, portanto analiso se estam vazias primeiro.
    if(!(*priority4).empty())
        while(!(*priority4).empty()){
            (*processes).push_back((*priority4).front());
            (*priority4).pop_front();
        }
    else if(!(*priority3).empty())
        while(!(*priority3).empty()){
            (*processes).push_back((*priority3).front());
            (*priority3).pop_front();
        }
    else if(!(*priority2).empty())
        while(!(*priority2).empty()){
            (*processes).push_back((*priority2).front());
            (*priority2).pop_front();
        }
    else if(!(*priority1).empty())
        while(!(*priority1).empty()){
            (*processes).push_back((*priority1).front());
            (*priority1).pop_front();
        }
    else if(!(*priority0).empty())
        while(!(*priority0).empty()){
            (*processes).push_back((*priority0).front());
            (*priority0).pop_front();
        }
    else
        cout<<"Não contém dados nas listas"<<endl;
    
}


void MFP::initialize_policie(){
    if(this-> processes.empty())
        return;
    //Faço a distribuição dos processos nas 5 listas - Prioridade de 0 a 4
    distribution_list(&(this->processes), &(this->priority0), &(this->priority1), &(this->priority2), &(this->priority3), &(this->priority4));
    //Adiciono na lista principal para execução
    add_main_process(&(this->processes),&(this->priority0), &(this->priority1), &(this->priority2), &(this->priority3), &(this->priority4));
}



//Funções que executam a politica em sí

void MFP::raffle_initialize(){
    //Todos os processos recebem um bilhete inicial. (O biblete é a posição no vetor)
    for(int i=0; i < (int )this->processes.size();i++){
        (this->tokens).push_back(processes.front().get_id());
        this->distribuited_tokens++;
        this->processes.push_back(this->processes.front());
        this->processes.pop_front();
    } 
}

//Função que realiza o sorteio dos bilhetes, atribuir -1 ao biblete sorteado, ou seja, aquele biblhete está apto a ser atribuido a outro processo
void MFP::raffle(){
    int available_tokens = 0;

    //Contando casas vazias, bilhetes sem processos
    for(int token : this->tokens)
        if(token == -1)
            available_tokens++;
    

    //Sorteando ficha
    int raffle_token =  rand()%this->distribuited_tokens;
    cout<<"Bilhete sorteado  "<< raffle_token<<endl;
    //Processo dono do bilhete e que será executado;
    int raffle_id=0;
    cout<<"Tokens distribuidos  "<< this->distribuited_tokens<<endl;
    //Pego o id do processo que contem o bilhete
    for(int i = 0; i < distribuited_tokens + available_tokens; i++){       
        if(this->tokens[i] == -1)
            raffle_token++;

        if(raffle_token == i){
            raffle_id = this->tokens[raffle_token];
            this->tokens[raffle_token] = -1;
            cout<<"Encontrou processo "<<raffle_id<<endl;
            i = distribuited_tokens + available_tokens;
        }
    }
    //Procurar o processo sorteado na lista de stopped.
    for(int i = 0; i < (int)stopped.size(); i++){
        if(stopped.front().get_id() == raffle_id){
            cout<<"Colocando o "<<stopped.front().get_id()<< " na fila de processos."<<endl;
            this->processes.push_front(stopped.front());
            this->last_process = this->processes.front().get_id();
            stopped.pop_front();
        }
        this->stopped.push_back(stopped.front());
        this->stopped.pop_front(); 
    }

    cout<<"Tamanho da lista principal "<<(int)processes.size()<<endl;


    //Tirar os bilhetes do processo sorteado.
    //Percorrer o vetor e colocar -1 no valor do bilhete



    //Sortear bilhetes para os demais.


    /* for(Process item: this->stopped)){
        if(item.get_id()!= raffle_id){
            (*tokens).push_back(item.get_id());
            (*distribuited_tokens)++;
        }
    }  */

}




void MFP::aplly_policie(){ 
    //Só entra nesse if, caso as filas de prioridade não estejam vazias, ou seja, apenas no começo, antes de se tornarem uma fila unica.
    if(!empty_lists){
        if(!priority4.empty())
            while (!priority4.empty()){
                processes.push_back(priority4.front());
                priority4.pop_front();
            }     
        else if(!priority3.empty())
            while (!priority3.empty()){
                processes.push_back(priority3.front());
                priority3.pop_front();
            }  
        else if(!priority2.empty())
            while (!priority2.empty()){
                processes.push_back(priority2.front());
                priority2.pop_front();
            }  
        else if(!priority1.empty())
            while (!priority1.empty()){
                processes.push_back(priority1.front());
                priority1.pop_front();
            } 
        else if(!priority0.empty()){
            while (!priority0.empty()){
                processes.push_back(priority0.front());
                priority0.pop_front();
            }  
            change_empty_lists();
            //Depois que todos possuem prioridade 0, os primeiros bilhetes são distribuidos
            //Distribuir bilhete para todos os processos
            raffle_initialize();
            //todos os processos são movidos para a lista stopped
            this->stopped = this->processes;
            //quando sorteados, os processos serão transferidos para a lista processes
            this->processes.clear(); 
            cout<<"Aplicando politica da loteria"<<endl;
            raffle();
        }
    //Só entra nesse else, caso a fila tenha se tornado unica e todos os processos tenham a mesma prioridade.
    }else {
        cout<<"Aplicando politica da loteria"<<endl;
        //POLITICA DA LOTERIA
        raffle();

    }
}