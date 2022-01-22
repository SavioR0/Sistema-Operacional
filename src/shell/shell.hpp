#ifndef __SHELL_HPP__
#define __SHELL_HPP__

#include <iostream>
#include <string>

using namespace std;

class Shell{
    private:
        int option   = 20;
        bool execute = false;
    public:

        Shell();
        void set_option(int option);
        int  get_option();
        void set_execute_status(bool value);
        bool get_execute_status();
        void selected_shell_option();
        void help_command();
        void mem_info_command();
        void message_exit();
    };


#endif