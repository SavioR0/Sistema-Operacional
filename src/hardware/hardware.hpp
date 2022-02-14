#pragma once
#include <iostream>
#include "../Process/process.hpp"
#include <vector>
#include <list>

class Hadware{
    public:
        virtual void insert_process(std::list<Process>::iterator iterator) = 0;
        virtual void remove_process(int id) = 0;
        virtual void generate_report() const = 0;
        virtual void remove_ready_process() = 0;
        
        
        struct ContentData{
            int         id;                // ID do processo
            int         time;              // Tempo máximo de castigo
            int         current_time;      // Tempo que ele está na memoria
            bool        alocated;          // variável que define se está alocado ou não 
            std::string description;       // Tipo do processo 
            
            ContentData(){this->alocated = false;}
            ContentData(int id, int time, int current_time, std::string description):
                id(id),
                time(time),
                current_time(current_time),
                description(description)
            {
                this->alocated = false;
            }
            ContentData(int id, int time, int current_time, bool alocated, std::string description):
                id(id),
                time(time),
                current_time(current_time),
                alocated(alocated),
                description(description)
            {}
        };
    protected:
        ContentData convert_iterator_to_contentData(std::list<Process>::iterator iterator){
            return ContentData(
                iterator->get_id(),
                iterator->get_penalty_time(),
                0,
                true,
                iterator->get_type()
            );
        }
};