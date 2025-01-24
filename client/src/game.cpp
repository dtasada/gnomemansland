#include "../include/engine.hpp"
#include "../include/game.hpp"
#include "../include/world.hpp"

#include <cstddef>
#include <iostream>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

Game::Game(Settings st) :
    target_framerate(st.video.target_framerate),
    client(st),
    settings(st) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
        exit_failure("Failed to initialize SDL");

    if (!(window = SDL_CreateWindow(
              "PO6",
              SDL_WINDOWPOS_UNDEFINED,
              SDL_WINDOWPOS_UNDEFINED,
              st.video.resolution.x,
              st.video.resolution.y,
              0
          )))
        exit_failure("Failed to create SDL Window");

    if (!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)))
        exit_failure("Failed to create SDL Renderer");

    world = World(st, renderer);

    running = true;
}

Game::~Game() {
    client.stop();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

Sprite::Sprite(SDL_Renderer *renderer, std::string image_path, SDL_Rect rect, v2f vel, v2f acc) :
    rect(rect),
    vel(vel),
    acc(acc) {
    tex = IMG_LoadTexture(renderer, image_path.c_str());
    SDL_Point size;
    SDL_QueryTexture(tex, NULL, NULL, &size.x, &size.y);
}

Sprite::~Sprite() { SDL_DestroyTexture(tex); }

void Sprite::copy(SDL_Renderer *renderer) { SDL_RenderCopy(renderer, tex, NULL, &rect); }

int exit_failure(std::string message) {
    std::cerr << message << ": " << SDL_GetError() << std::endl;
    SDL_Quit();
    return EXIT_FAILURE;
}
