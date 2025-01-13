#include "../include/engine.hpp"
#include <iostream>

Game::Game() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
        exit_failure("Failed to initialize SDL");

    window = SDL_CreateWindow("PO6", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
    if (!window)
        exit_failure("Failed to create SDL Window");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
        exit_failure("Failed to create SDL Renderer");

    running = true;
}

Game::~Game() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

int exit_failure(std::string message) {
    std::cerr << message << ": " << SDL_GetError() << std::endl;
    SDL_Quit();
    return EXIT_FAILURE;
}
