#include "../include/client.hpp"
#include "../include/engine.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <vector>

Client::Client(Settings settings) {
    connected = false;
    host = settings.multiplayer.server_host;
    port = settings.multiplayer.server_port;

    if (settings.multiplayer.enable)
        start();
}

Client::~Client() {
    connected = false;
    if (listen_thread.joinable())
        listen_thread.join();

    std::clog << "Client closing network client" << std::endl;
    SDLNet_TCP_Close(socket);
    SDLNet_Quit();
}

int Client::start() {
    if (SDLNet_Init() < 0) {
        return exit_failure("Failed to initialize SDL_net");
    } else {
        std::clog << "Client initialized SDL_net" << std::endl;
    }

    if (SDLNet_ResolveHost(&server_ip, host.c_str(), port) < 0) {
        return exit_failure("Failed to resolve host");
    } else {
        std::clog << "Client resolved host" << std::endl;
    }

    if (!(socket = SDLNet_TCP_Open(&server_ip))) {
        return exit_failure("Failed to open port");
    } else {
        std::clog << "Client opened port" << std::endl;
    }

    if (!(socket_set = SDLNet_AllocSocketSet(1))) {
        return exit_failure("Failed to allocate socket set");
    }

    SDLNet_TCP_AddSocket(socket_set, socket);

    connected = true;
    listen_thread = std::thread(&Client::listen, this);
    return 0;
}

void Client::listen() {
    std::vector<char> buffer(512);

    while (connected) {
        if (SDLNet_CheckSockets(socket_set, 1000) > 0 && SDLNet_SocketReady(socket)) {
            int bytes_received = SDLNet_TCP_Recv(socket, buffer.data(), buffer.size());
            if (bytes_received > 0) {
                std::string message(buffer.data(), bytes_received);
                std::clog << "Received message: " << message << std::endl;

                if (message.compare("ping")) {
                    std::clog << "compare" << std::endl;
                }
            } else {
                std::clog << "Connection lost or error while receiving data." << std::endl;
                connected = false;
            }
        }

        SDL_Delay(100);
    }

    delete this;
}

void Client::send(std::string message) {
    int len = message.length() + 1;
    if (SDLNet_TCP_Send(socket, (void *)message.c_str(), len) < len)
        std::cerr << "Failed to send message" << std::endl;
}

int Client::exit_failure(std::string message) {
    std::cerr << message << ": " << SDLNet_GetError() << std::endl;
    return 1;
}
