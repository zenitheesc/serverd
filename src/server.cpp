#include "message-buffer.hpp"
#include "utils.hpp"
#include <exception>
#include <frameworkd/classes/daemon/daemon.hpp>
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>

class ServerdService : public RoutineService {
    const char* m_host;
    int m_port;

    httplib::Server m_svr;
    MessagesBuffer m_buffer;

    static const int buffer_size = 10;

public:
    explicit ServerdService(const char* host, const int port, const nlohmann::json data)
        : RoutineService { "serverd" }
        , m_host { host }
        , m_port { port }
        , m_buffer { data["numBytes"] }
    {
    }

    const DBusHandler::Path m_requestPath {
        "zfkd.dbus.serverd",
        "/zfkd/dbus/serverd",
        "zfkd.dbus.serverd",
        "request"
    };

    void setup() override
    {

        m_svr.Post("/", [&](const httplib::Request& req, httplib::Response& res) {
            nlohmann::json receivedJson;
            receivedJson = nlohmann::json::parse(req.body);

            std::uint8_t id = receivedJson["equipe"];
            nlohmann::json payload = receivedJson["payload"];

            m_buffer.write(id, payload);
            utils::saveJson(receivedJson, std::to_string(id));

            res.set_content("received message", "text/plain");
        });

        m_svr.set_error_handler([](const httplib::Request&, httplib::Response& res) {
            std::string error = "Error:" + std::to_string(res.status);
            res.set_content(error, "text/plain");
        });

        m_svr.set_exception_handler([](const httplib::Request&, httplib::Response& res, std::exception& e) {
            std::cout << e.what() << std::endl;
            res.set_content("exception raised", "text/plain");
        });

        DBusHandler::registerMethod(m_requestPath, [&](nlohmann::json) {
            return m_buffer.getCurrMessage();
        });
    }

    void routine() override
    {
        m_svr.listen(m_host, m_port);
    }

    void destroy() override
    {
    }
};

auto main(int argc, char* argv[]) -> int
{
    const char* host;
    int port;

    if (argc < 2) {
        host = "localhost";
        port = 8080;
    } else if (argc == 3) {
        host = argv[1];
        port = atoi(argv[2]);
    } else {
        throw std::invalid_argument("invalid number of arguments");
    }

    Daemon serverd { "serverd" };
    ServerdService serverdService { host, port, serverd.getConfigHandler()["data"] };
    serverd.deploy(serverdService);
    serverd.run();

    return 0;
}
