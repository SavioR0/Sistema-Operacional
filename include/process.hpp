#ifndef __PROCESS_HPP__
#define __PROCESS_HPP__

#include <iostream>
#include <string>

using namespace std;

class Process{
    private:
        int      id;
        float    cycles;
        int      maxQuantum;
        int      timestamp;
        int      priority;
        string*  status;
        string*  type;
    public:
        
        
        Process();
        Process( int id, float cycles, int maxQuantum, int timesamp, int priority, string type);
        
        void setId    (int value);
        void setCycles(float value);
        void setMaxQuantum(int value);
        void setTimestamp(int value);
        void setPriority(int value);
        void setStatus(string value);
        void setStatusAddres(string* value );
        void setType(string value);
        void setTypeAddress(string* value );

        void sub_quantum(int current_quantum);
        void add_timestamp();


        int getId();
        float getcyles();
        int getMaxQuantum();
        int getTimestamp();
        int getPriority();
        
        string getStatus();
        string* getStatusAdress();
        string getType();
        string* getTypeAdress();

};

#endif