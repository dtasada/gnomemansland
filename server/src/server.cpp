#include "../include/server.hpp"

#include <fstream>
#include <iostream>

RemoteClient::RemoteClient(TCPsocket socket, IPaddress address) :
    socket(socket),
    address(address),
    connected(true) {}

Server::Server(uint16_t port) : port(port) {
    if (SDLNet_Init() < 0) exit_failure("Failure to initialize SDL_net");

    /* Resolving the host using NULL make network interface to listen */
    if (SDLNet_ResolveHost(&address, NULL, port) < 0) exit_failure("Failure to resolve host");

    /* Open a connection with the IP provided (listen on the host's port) */
    if (!(socket = SDLNet_TCP_Open(&address))) exit_failure("Failure to open port");

    database_path = "server/db.json";
    std::ifstream database_file(database_path);

    if (database_file.is_open()) {
        try {
            database_file >> database;
            std::clog << "Loaded database from " << database_path << std::endl;
        } catch (json::parse_error &e) {
            std::cerr << "Failed to parse database: " << e.what() << std::endl;
            std::exit(EXIT_FAILURE);
        }
        database_file.close();
    } else {
        std::clog << database_path << " doesn't exist. Creating new database." << std::endl;
        database = {
            {"players", json::array()},
        };
        std::ofstream new_file(database_path);
        new_file << database.dump(4);
        new_file.close();
        std::clog << "Created new database at " << database_path << std::endl;
    }

    running = true;
}

Server::~Server() {
    running = false;
    SDLNet_FreeSocketSet(socket_set);
    SDLNet_TCP_Close(socket);
    SDLNet_Quit();
    std::clog << "Closed SDL_net." << std::endl;

    std::ofstream database_file(database_path);
    if (database_file.is_open()) {
        database_file << database.dump(4);
        database_file.close();
        std::clog << "Saved database at " << database_path << std::endl;
    } else {
        std::cerr << "Failed to save database." << std::endl;
    }
}

void Server::exit_failure(std::string message) {
    std::cerr << message << ": " << SDLNet_GetError() << std::endl;
    std::exit(EXIT_FAILURE);
}

void Server::handle_clients() {
    // Listen for incoming messages from clients
    for (RemoteClient &client : client_connections) {
        if (SDLNet_SocketReady(client.socket)) {
            std::vector<char> buffer(4096);
            size_t bytes_received = SDLNet_TCP_Recv(client.socket, buffer.data(), buffer.size());

            if (bytes_received > 0 && bytes_received < buffer.size()) {
                std::stringstream message_stream(std::string(buffer.data(), bytes_received));
                std::string       message;
                std::vector<std::string> messages;

                while (std::getline(message_stream, message, '\n')) {
                    std::clog << "Client says: " << message << std::endl;
                }
            } else {
                client.connected = false;
                SDLNet_TCP_DelSocket(socket_set, client.socket);
                SDLNet_TCP_Close(client.socket);
            }
        }
    }

    // Remove any disconnected clients
    std::erase_if(client_connections, [](const RemoteClient &client) {
        if (!client.connected)
            std::clog << "Client disconnected: " << client.address.host << ":"
                      << client.address.port << std::endl;
        return !client.connected;
    });

    // send_to_all(database.dump());
}

void Server::listen() {
    std::clog << "SDL_net server listening on port " << port << std::endl;

    // Create a socket set for the server and clients
    const int max_sockets = 32;
    if (!(socket_set = SDLNet_AllocSocketSet(max_sockets)))
        exit_failure("Failed to allocate socket set");

    SDLNet_TCP_AddSocket(socket_set, socket);

    const uint32_t timeout = 10;
    while (running) {
        handle_clients();

        if (SDLNet_CheckSockets(socket_set, timeout) > 0 && SDLNet_SocketReady(socket)) {
            TCPsocket client_socket = SDLNet_TCP_Accept(socket);
            if (client_socket) {
                IPaddress *client_ip = SDLNet_TCP_GetPeerAddress(client_socket);
                if (client_ip) new_client(client_socket, *client_ip);
            }
        }
    }
}

void Server::send_to_all(std::string message) {
    message += "\n";
    for (RemoteClient &client : client_connections) {
        std::clog << "Sending to client: " << message << std::endl;
        if (SDLNet_TCP_Send(client.socket, message.c_str(), message.length()) < message.length())
            std::cerr << "Failed to send message" << std::endl;
    }
}

void Server::new_client(TCPsocket client_socket, IPaddress client_address) {
    SDLNet_TCP_AddSocket(socket_set, client_socket);

    client_connections.emplace_back(client_socket, client_address);
    database["players"].push_back({
        {"host", client_address.host},
        {"port", client_address.port}
    });

    std::clog << "New client connected: " << client_address.host << ":" << client_address.port
              << std::endl;
}
