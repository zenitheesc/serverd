#include <iostream>
#include <map>
#include <vector>
#include <mutex>
#include <unistd.h>
#include <thread>
using namespace std;
class MessagesBuffer{
    private:
    mutex m;
    public:
    map<string,string> messages;
    void init(void){
        thread t1(&MessagesBuffer::read, this);
        thread t2(&MessagesBuffer::write, this);
        t1.join();
        t2.join();
    }
    void write(){
        string IP, message;
        while(true){
            lock_guard<mutex> lock(m);
            cin>>IP;
            cin>>message;
            messages.insert(pair<string, string>(IP, message));
            lock_guard<mutex> unlock(m);   
        }
    }
    void read(){
        while(true){
            sleep(2);
            lock_guard<mutex> lock(m);
            auto val = this->messages["1"];
            cout<<val<<endl;
            //messages.erase(val->first);
            lock_guard<mutex> unlock(m);
        }
        
    }
};

int main(){
    MessagesBuffer msg;
    msg.messages["1"] = "Ola";
    msg.init();
    return 0;
}