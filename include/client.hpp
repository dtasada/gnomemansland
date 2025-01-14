#include "../include/engine.hpp"

#include <sqlite3.h>
#include <string>

class Client {
    bool connected;

    std::string host;
    uint16_t port;

    IPaddress server_ip;
    TCPsocket socket;

    void exit_failure(std::string message);

  public:
    Client(std::string host, uint16_t port);
    ~Client();

    void send(std::string message);
};
