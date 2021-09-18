#include <httplib.h>
#include <nlohmann/json.hpp>
#include <thread>

void printJSON(nlohmann::json json){
    if(json.is_object()){
        for(auto& el : json.items()){
            if (el.value().is_structured()) printJSON(el.value());
            else std::cout << el.key() << ":" << el.value() << std::endl;
        }
    }else {
        for(auto& el : json){
            if (el.is_structured()) printJSON(el);
            else std::cout << el << std::endl;
        }
    }
    
}

void server(){
    httplib::Server svr;

    svr.Post("/", [](const httplib::Request& req, httplib::Response& res){
        nlohmann::json receivedJson;
        receivedJson = nlohmann::json::parse(req.body);
        printJSON(receivedJson);
        res.set_content("mensagem recebida ^-^","text/plain");
    });
    
    svr.listen("localhost", 1234);
}

int main(void){
    std::thread thread(server);
    while (true) {
        sleep(5);
        std::cout << "\toi\n";
    }
    thread.join();
}
