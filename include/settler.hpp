#ifndef __SETTER_HPP__
#define __SETTER_HPP__

#include <iostream>
#include <fstream>
#include <queue>


#define File "processos.json"

using namespace std;

struct Process{
    int id;
    string estado;
    int ciclos;
    int maxQuantum;
    string initType;
    int timestamp;
    int prioridade;
};

class Settler{ 
public:
    queue<Process> processes;
    Settler();
    void printProcess(Process proc);
    void printQueue();
};






#endif
