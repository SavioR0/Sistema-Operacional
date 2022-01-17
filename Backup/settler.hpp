#ifndef __SETTER_HPP__
#define __SETTER_HPP__

#include <iostream>
#include <fstream>
#include <queue>


#define File "processos.json"

using namespace std;

struct Process{
    int id;
    int ciclos;
    int maxQuantum;
    string initType;
    int timestamp;
    int prioridade;
    
    string estado;
    int startExecute;
    int quantumCount;

};

class Settler{ 
private:
    int numProcesses;
public:
    queue<Process> processes;
    Settler(int process);

    void executeQueue();
    void printProcess(Process proc);
    void printQueue();
};






#endif
