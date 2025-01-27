#pragma once

#if defined(__linux)
#    include <nlohmann/json.hpp>
#    include <SDL2/SDL_net.h>
#elif defined(__APPLE__) || defined(_WIN32)
#    include <nlohmann/json.hpp>
#    include <SDL_net.h>
#endif

#include <string>
#include <vector>

using json = nlohmann::json;

struct RemoteClient {
    TCPsocket socket;
    IPaddress address;
    bool      connected;

    RemoteClient(TCPsocket socket, IPaddress address);
};

class Server {
    bool running;

    uint16_t port;

    IPaddress                 address;
    TCPsocket                 socket;
    SDLNet_SocketSet          socket_set;
    std::vector<RemoteClient> client_connections;

    void exit_failure(std::string message);
    void new_client(TCPsocket socket, IPaddress address);

  public:
    Server(uint16_t port);
    ~Server();

    json        database;
    std::string database_path;

    void listen(void);
    void handle_clients(void);
    void send_to_all(std::string message);
};
