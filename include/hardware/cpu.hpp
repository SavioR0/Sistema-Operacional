#ifndef __CPU_HPP__
#define __CPU_HPP__

#include <iostream>

using namespace std;

class Cpu{
    private:
        int cores;
    public:

        Cpu(int cores);
        void print();
};


#endif