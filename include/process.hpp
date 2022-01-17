#include <iostream>


using namespace std;

class Process{
    private:
        int      id;
        int      cycles;
        int      maxQuantum;
        int      timestamp;
        int      priority;
        string*  status;
        string*  type;
    public:
        
        
        Process();
        Process( int id, int cycles, int maxQuantum, int timesamp, int priority, string type);
        
        void setId    (int value);
        void setCycles(int value);
        void setMaxQuantum(int value);
        void setTimestamp(int value);
        void setPriority(int value);
        void setStatus(string value);
        void setStatusAddres(string* value );
        void setType(string value);
        void setTypeAddress(string* value );


        int getId();
        int getcyles();
        int getMaxQuantum();
        int getTimestamp();
        int getPriority();
        
        string getStatus();
        string* getStatusAdress();
        string getType();
        string* getTypeAdress();

};
