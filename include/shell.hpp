#ifndef __SHELL_HPP__
#define __SHELL_HPP__

#include <iostream>
#include <string>

using namespace std;

class Shell{
    private:
        int option = 20;
    public:

        Shell();
        void set_option(int option);
        int  get_option();
        void selected_shell_option();
        void help_command();
        void mem_info_command();
    };


#endif