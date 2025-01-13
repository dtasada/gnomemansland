#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <iostream>

int exit_failure(std::string message) {
    std::cerr << message << ": " << SDLNet_GetError() << std::endl;
    SDL_Quit();
    return EXIT_FAILURE;
}

int main(int argc, char **argv) {
    IPaddress ip; /* Server address */
    TCPsocket sd; /* Socket descriptor */
    int quit, len;
    char buffer[512];

    /* Simple parameter checking */
    if (argc < 3) {
        fprintf(stderr, "Usage: %s host port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (SDLNet_Init() < 0)
        exit_failure("SDLNet_Init");

    /* Resolve the host we are connecting to */
    if (SDLNet_ResolveHost(&ip, argv[1], atoi(argv[2])) < 0)
        exit_failure("SDLNet_ResolveHost");

    /* Open a connection with the IP provided (listen on the host's port) */
    if (!(sd = SDLNet_TCP_Open(&ip)))
        exit_failure("SDLNet_TCP_Open");

    /* Send messages */
    quit = 0;
    while (!quit) {
        printf("Write something:\n>");
        scanf("%s", buffer);

        len = strlen(buffer) + 1;
        if (SDLNet_TCP_Send(sd, (void *)buffer, len) < len) {
            fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
            exit(EXIT_FAILURE);
        }

        if (strcmp(buffer, "exit") == 0)
            quit = 1;
        if (strcmp(buffer, "quit") == 0)
            quit = 1;
    }

    SDLNet_TCP_Close(sd);
    SDLNet_Quit();

    return EXIT_SUCCESS;
}
