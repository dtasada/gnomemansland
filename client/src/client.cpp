#include "../include/client.hpp"
#include "../include/engine.hpp"

#include <climits>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

Client::Client(Settings st) {
    connected = false;
    host      = st.multiplayer.server_host;
    port      = st.multiplayer.server_port;

    if (st.multiplayer.enable) start();
}

void Client::stop() {
    connected = false;
    if (listen_thread.joinable()) listen_thread.join();

    std::clog << "Closing network client" << std::endl;
    SDLNet_TCP_Close(socket);
    SDLNet_Quit();
}

int Client::start(void) {
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

    connected     = true;
    listen_thread = std::thread(&Client::listen, this);
    return 0;
}

void Client::listen(void) {
    std::vector<char> buffer(UINT32_MAX);

    while (connected) {
        if (SDLNet_CheckSockets(socket_set, 1000) > 0 && SDLNet_SocketReady(socket)) {
            size_t bytes_received = SDLNet_TCP_Recv(socket, buffer.data(), buffer.size());
            if (bytes_received > 0) {
                std::string message(buffer.data(), bytes_received);
                std::clog << "Server says: " << message << std::endl;
            } else {
                std::clog << "Connection lost or error while receiving data." << std::endl;
                connected = false;
            }
        }

        SDL_Delay(200);
    }
}

void Client::send(std::string message) {
    message += "\n";
    if (SDLNet_TCP_Send(socket, message.c_str(), message.length()) < message.length())
        std::cerr << "Failed to send message" << std::endl;
}

int Client::exit_failure(std::string message) {
    std::cerr << message << ": " << SDLNet_GetError() << std::endl;
    return EXIT_FAILURE;
}
