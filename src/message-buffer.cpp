#include <iostream>
#include <map>
#include <vector>
#include <mutex>
#include <unistd.h>
using namespace std;
class MessagesBuffer{
    private:
    map<string,string> messages;
    mutex m;
    public:
    void init(void){

    }
    void write(string IP, string message){
        messages.insert(pair<string, string>(IP, message));
    }
    void read(vector<string> &transmission){
        lock_guard<mutex> lock(m);
        for(auto it = messages.begin(); it!= messages.end(); it = messages.begin()){
            sleep(1);
            transmission.push_back(it->second);
            messages.erase(it->first);
        }
    }
};

