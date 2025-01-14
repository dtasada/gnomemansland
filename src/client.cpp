#include "../include/client.hpp"
#include "../include/engine.hpp"
#include <ctime>
#include <iostream>
#include <thread>

Client::Client(std::string host, uint16_t port) {
    if (SDLNet_Init() < 0)
        exit_failure("Failed to initialize SDL_net");

    if (SDLNet_ResolveHost(&server_ip, host.c_str(), port) < 0)
        exit_failure("Failed to resovle host");

    if (!(socket = SDLNet_TCP_Open(&server_ip)))
        exit_failure("Failed to open port");
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
