#ifndef __SHELLhPP__
#define __SHELLhPP__

#include <iostream>
#include <string.h>

using namespace std;

class Shell{
    private:
        int option = 20;
    public:
        Shell();
        void setOption(int option);
        int getOption();
        void selectedShellOption();
        void helpCommand();
    };

#endif