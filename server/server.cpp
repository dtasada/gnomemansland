#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <iostream>

int exit_failure(std::string message) {
    std::cerr << message << ": " << SDLNet_GetError() << std::endl;
    SDL_Quit();
    return EXIT_FAILURE;
}

int main(int argc, char **argv) {
    TCPsocket sd, csd;
    IPaddress ip, *remoteIP;
    int quit, quit2;
    char buffer[512];

    if (SDLNet_Init() < 0)
        return exit_failure("Failure to initialize SDL_net");

    /* Resolving the host using NULL make network interface to listen */
    if (SDLNet_ResolveHost(&ip, NULL, 2000) < 0)
        return exit_failure("Failure to resolve host");

    /* Open a connection with the IP provided (listen on the host's port) */
    if (!(sd = SDLNet_TCP_Open(&ip)))
        return exit_failure("Failure to open port");

    /* Wait for a connection, send data and term */
    quit = 0;
    while (!quit) {
        /* This check the sd if there is a pending connection.
         * If there is one, accept that, and open a new socket for communicating
         */
        if ((csd = SDLNet_TCP_Accept(sd))) {
            /* Now we can communicate with the client using csd socket * sd will
               remain opened waiting other connections */

            /* Get the remote address */
            if ((remoteIP = SDLNet_TCP_GetPeerAddress(csd)))
                /* Print the address, converting in the host format */
                printf("Host connected: %x %d\n",
                       SDLNet_Read32(&remoteIP->host),
                       SDLNet_Read16(&remoteIP->port));
            else
                fprintf(stderr, "SDLNet_TCP_GetPeerAddress: %s\n",
                        SDLNet_GetError());

            quit2 = 0;
            while (!quit2) {
                if (SDLNet_TCP_Recv(csd, buffer, 512) > 0) {
                    printf("Client say: %s\n", buffer);

                    if (strcmp(buffer, "exit") == 0) {
                        /* Terminate this connection */
                        quit2 = 1;
                        printf("Terminate connection\n");
                    }
                    if (strcmp(buffer, "quit") == 0) {
                        /* Quit the program */
                        quit2 = 1;
                        quit = 1;
                        printf("Quit program\n");
                    }
                }
            }

            /* Close the client socket */
            SDLNet_TCP_Close(csd);
        }
    }

    SDLNet_TCP_Close(sd);
    SDLNet_Quit();

    return EXIT_SUCCESS;
}
