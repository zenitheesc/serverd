#include <httplib.h>
#include <nlohmann/json.hpp>
#include <thread>
#include <exception>

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
    
    svr.set_error_handler([](const httplib::Request&, httplib::Response &res) {
        std::string html = R"(<h1>NADA PARA VER AQUI</h1><a><img src="https://zenith.eesc.usp.br/images/Footer/logo.svg" alt="Zenith Logo" width="148px" height="79px" style="background-color: black;"></a>)";
        res.set_content(html, "text/html");
    });

    svr.set_exception_handler([](const httplib::Request& req, httplib::Response& res, std::exception& e){
            std::cout << e.what() << std::endl;
            res.set_content("alguma coisa n funcionou, vai reclamar com o Matheus", "text/plain");
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
