#pragma once

#include "../include/engine.hpp"

#ifdef __linux
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>
#elif __APPLE__
#include <SDL_image.h>
#include <SDL_net.h>
#endif

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

    int start(void);
    void stop(void);
    void listen(void);
    void send(std::string message);
};
