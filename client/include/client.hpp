#pragma once

#include "../include/engine.hpp"

#include <string>
#include <thread>

class Client {
    bool connected;

    std::string host;
    uint16_t    port;
    uint32_t    timeout;

    IPaddress        server_ip;
    TCPsocket        socket;
    SDLNet_SocketSet socket_set;

    std::thread listen_thread;

    void exit_failure(std::string message);

  public:
    Client(Settings);
    ~Client(void);

    void start(void);
    void stop(void);
    void listen(void);
    void send(std::string message);
};
