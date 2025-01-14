#include "../include/client.hpp"
#include "../include/engine.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Client::Client(std::string host, uint16_t port) : connected(false), host(host), port(port) {}

int Client::start() {
    if (SDLNet_Init() < 0) {
        exit_failure("Failed to initialize SDL_net");
        return EXIT_FAILURE;
    }

    if (SDLNet_ResolveHost(&server_ip, host.c_str(), port) < 0) {
        exit_failure("Failed to resovle host");
        return EXIT_FAILURE;
    }

    if (!(socket = SDLNet_TCP_Open(&server_ip))) {
        exit_failure("Failed to open port");
        return 1;
    }

    return 0;
}

Client::~Client() {
    std::cout << "Client closing network client" << std::endl;
    SDLNet_TCP_Close(socket);
    SDLNet_Quit();
}

void Client::send(std::string message) {
    int len = message.length() + 1;
    if (SDLNet_TCP_Send(socket, (void *)message.c_str(), len) < len)
        std::cerr << "Failed to send message" << std::endl;
}

void Client::exit_failure(std::string message) {
    std::cerr << message << ": " << SDLNet_GetError() << std::endl;
    delete this;
}
