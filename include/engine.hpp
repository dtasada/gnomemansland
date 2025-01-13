#include "../include/v2.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <string>

struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
    float fps;
    float dt;
    bool running;

    Game();
    ~Game();
};

struct Sprite {
    SDL_Texture *tex;
    SDL_Rect rect;
    v2 pos;
    v2 vel;
    v2 acc;

    Sprite();
};

int exit_failure(std::string message);
