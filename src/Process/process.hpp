#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define STATUS_READY    "Pronto"
#define STATUS_AWAIT    "Em Execucao"
#define STATUS_BLOCK    "Bloqueado"
#define STATUS_FINISHED "Finalizado"

#define PROCESS_CPU "cpu-bound"
#define PROCESS_MEM "memory-bound"
#define PROCESS_STG "io-bound"



class Process{
    public:
        int assist;

    private:
        int          id;
        float        cycles;
        short int    max_quantum;
        int          timestamp;
        int          priority;
        std::string  status;
        std::string  type;
        int          penalty_time;

    public:
        Process(){}
        Process(int id):id(id){}
        Process( 
            int id, 
            float cycles, 
            const short int max_quantum, 
            int timestamp, 
            int priority, 
            std::string type);

    public:
        void set_penalty_time(int penalty_time);
        void set_status_ready();
        void set_status_await();
        void set_status_block();
        void set_status_finished();
        void sub_priority();



    public:
        int         get_id()           const;
        int         get_cycles()       const;
        int         get_penalty_time() const;
        short int   get_max_quantum()  const;
        int         get_timestamp()    const;
        int         get_priority()     const;
        std::string get_status()       const;
        std::string get_type()         const;        

    public:
        void add_timestamp();
        void sub_cycles(int quantum_drawn);
    
    //token management
    private:
        std::vector<int> tokens;
    public:
        void add_token(int token);
        bool contains_token(int token);
        std::vector<int> get_and_remove_tokens();


};
