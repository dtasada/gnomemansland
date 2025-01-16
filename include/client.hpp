#include "../include/engine.hpp"
#include <sqlite3.h>
#include <string>
#include <thread>

class Client {
    bool connected;

    std::string host;
    uint16_t port;

    IPaddress server_ip;
    TCPsocket socket;
    SDLNet_SocketSet socket_set;

    std::thread listen_thread;

    int exit_failure(std::string message);

  public:
    Client(Settings);
    ~Client();

    int start(void);
    void listen(void);
    void send(std::string message);
};
