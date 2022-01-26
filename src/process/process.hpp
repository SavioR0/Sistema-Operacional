#ifndef __PROCESS_HPP__
#define __PROCESS_HPP__

#include <iostream>
#include <string>
#include <vector>

#define status_ready    "Pronto"
#define status_await    "Em Execucao"
#define status_block    "Bloqueado"
#define status_finished "Finalizado"


using namespace std;

class Process{
    private:
        int      id;
        float    cycles;
        int      max_quantum;
        int      timestamp;
        int      priority;
        string*  status;
        string*  type;

        vector<int> tokensProcess;
    public:
        
        
        Process();
        Process( int id, float cycles, int max_quantum, int timesamp, int priority, string type);
        
        void set_id    (int value);
        void set_cycles(float value);
        void set_max_quantum(int value);
        void set_timestamp(int value);
        void set_priority(int value);
        void set_status(string value);
        void set_status_ready();
        void set_status_await();
        void set_status_block();
        void set_status_finished();

        void set_status_addres(string* value );
        void set_type(string value);
        void set_type_address(string* value );

        void sub_quantum(int current_quantum);
        void add_timestamp();


        int get_id();
        float get_cyles();
        int get_max_quantum();
        int get_timestamp();
        int get_priority();
        
        string get_status();
        string* get_status_adress();
        string get_type();
        string* get_type_adress();

};

#endif