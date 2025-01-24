#pragma once

#if defined(__linux)
#include <SDL2/SDL_net.h>
#include <nlohmann/json.hpp>
#elif defined(__APPLE__) || defined(_WIN32)
#include <SDL_net.h>
#include <nlohmann/json.hpp>
#endif

#include <mutex>
#include <string>
#include <vector>

struct RemoteClient {
    TCPsocket socket;
    IPaddress address;
    bool connected;

    RemoteClient(TCPsocket socket, IPaddress address);
};

class Server {
    bool running;

    uint16_t port;

    IPaddress address;
    TCPsocket socket;
    SDLNet_SocketSet socket_set;
    std::vector<RemoteClient> client_connections;
    std::mutex client_mutex;

    void exit_failure(std::string message);

  public:
    Server(uint16_t port);
    ~Server();

    void listen(void);
    void handle_clients(void);
    void send_to_all(std::string message);
};
