#pragma once

#include "../include/client.hpp"
#include "../include/engine.hpp"
#include "../include/v2.hpp"
#include "../include/world.hpp"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <string>

struct Game {
    SDL_Window   *window;
    SDL_Renderer *renderer;
    float         target_framerate;
    float         dt;
    bool          running;

    World    world;
    Client   client;
    Settings settings;

    Game(Settings);
    ~Game(void);
};

struct Sprite {
    SDL_Texture *tex;
    SDL_Rect     rect;
    v2f          vel;
    v2f          acc;

    Sprite(
        SDL_Renderer *renderer,
        std::string   image_path,
        SDL_Rect      rect,
        v2f           vel = {0, 0},
        v2f           acc = {0, 0}
    );
    ~Sprite(void);

    void copy(SDL_Renderer *);
};

int exit_failure(std::string message);
