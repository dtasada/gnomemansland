#include "../include/engine.hpp"
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
