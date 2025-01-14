#include "../include/server.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <algorithm>
#include <iostream>

RemoteClient::RemoteClient(TCPsocket socket, IPaddress address)
    : socket(socket), address(address), connected(true) {}

Server::Server(uint16_t port) : port(port) {
    if (SDLNet_Init() < 0)
        exit_failure("Failure to initialize SDL_net");

    /* Resolving the host using NULL make network interface to listen */
    if (SDLNet_ResolveHost(&address, NULL, port) < 0)
        exit_failure("Failure to resolve host");

    /* Open a connection with the IP provided (listen on the host's port) */
    if (!(socket = SDLNet_TCP_Open(&address)))
        exit_failure("Failure to open port");

    running = true;
}

Server::~Server() {
    running = false;
    SDLNet_TCP_Close(socket);
    SDLNet_Quit();
    std::cout << "Closed SDL_net." << std::endl;
}

void Server::exit_failure(std::string message) {
    std::cerr << message << ": " << SDLNet_GetError() << std::endl;
    delete this;
}

void Server::handle_client(RemoteClient &client) {
    if (SDLNet_SocketReady(client.socket)) {
        std::vector<char> buffer(512);
        int bytes_received =
            SDLNet_TCP_Recv(client.socket, buffer.data(), buffer.size());
        if (bytes_received > 0) {
            std::string message(buffer.data(), bytes_received);
            std::cout << "Client says: " << message << std::endl;

            if (message == "exit") {
                client.connected = false;
                SDLNet_TCP_DelSocket(socket_set, client.socket);
                SDLNet_TCP_Close(client.socket);
                std::cout << "Client disconnected.\n";
            }
        } else {
            client.connected = false;
            SDLNet_TCP_DelSocket(socket_set, client.socket);
            SDLNet_TCP_Close(client.socket);
        }
    }
}

void Server::listen() {
    std::cout << "SDL_net server listening on port " << port << std::endl;

    // Create a socket set for the server and clients
    const int max_clients = 32;
    socket_set = SDLNet_AllocSocketSet(max_clients);
    if (!socket_set)
        exit_failure("Failed to allocate socket set");

    SDLNet_TCP_AddSocket(socket_set, socket);

    while (running) {
        // Check sockets for activity
        if (SDLNet_CheckSockets(socket_set, 1000) <= 0) {
            continue; // No activity
        }

        // Accept new client connections
        if (SDLNet_SocketReady(socket)) {
            TCPsocket client_socket = SDLNet_TCP_Accept(socket);
            if (client_socket) {
                IPaddress *client_ip = SDLNet_TCP_GetPeerAddress(client_socket);
                if (client_ip) {
                    std::cout << "New client connected: "
                              << SDLNet_Read32(&client_ip->host) << ":"
                              << SDLNet_Read16(&client_ip->port) << std::endl;

                    RemoteClient client(client_socket, *client_ip);
                    SDLNet_TCP_AddSocket(socket_set, client_socket);

                    {
                        std::lock_guard<std::mutex> lock(client_mutex);
                        client_connections.push_back(client);
                    }
                }
            }
        }

        // Check for activity on client sockets
        for (RemoteClient &client : client_connections) {
            handle_client(client);
        }

        // Remove disconnected clients
        client_connections.erase(std::remove_if(client_connections.begin(),
                                                client_connections.end(),
                                                [](const RemoteClient &client) {
                                                    return !client.connected;
                                                }),
                                 client_connections.end());
    }

    SDLNet_FreeSocketSet(socket_set);
}

int main() {
    Server server(1234);
    server.listen();
    return 0;
}
