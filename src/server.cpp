#include "utils.hpp"
#include <exception>
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>

int main(int argc, char* argv[])
{
    constexpr int defaultPort = 8080;
    const char* host = "localhost";
    int port = defaultPort;

    if (argc == 3) {
        host = argv[1];
        port = atoi(argv[2]);
    }

    httplib::Server svr;

    svr.Post("/", [](const httplib::Request& req, httplib::Response& res) {
        nlohmann::json receivedJson;
        receivedJson = nlohmann::json::parse(req.body);
        utils::printJSON(receivedJson);
        std::string remote_addr = req.remote_addr;
        res.set_content("received message", "text/plain");
    });

    svr.set_error_handler(
        [](const httplib::Request& req, httplib::Response& res) {
            std::string error = "Error:" + std::to_string(res.status);
            res.set_content(error, "text/plain");
        });

    svr.set_exception_handler(
        [](const httplib::Request& req, httplib::Response& res, std::exception& e) {
            std::cout << e.what() << std::endl;
            res.set_content("exception raised", "text/plain");
        });

    svr.listen(host, port);
}
