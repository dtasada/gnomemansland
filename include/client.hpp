#include <SDL2/SDL_net.h>
#include <sqlite3.h>
#include <string>

class Client {
    std::string host;
    uint16_t port;

    IPaddress server_ip;
    TCPsocket socket;

    void exit_failure(std::string message);
    void send(std::string message);

  public:
    Client(std::string host, uint16_t port);
    ~Client();
};
