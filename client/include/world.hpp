#pragma once

#include "../include/engine.hpp"
#include "../include/v2.hpp"

#include <csignal>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <vector>

inline namespace TileData {
    inline float WATER    = 0.5f;
    inline float SAND     = 0.54f;
    inline float GRASS    = 0.61f;
    inline float MOUNTAIN = 0.68f;
    inline float SNOW     = 1.f;
};

class World {
  public:
    World(Settings);

    v2u   size;
    float render_scale;

    std::vector<std::vector<rgb>> map_data;

    SDL_Surface *surf;
    Uint32      *pixels;
    SDL_Texture *tex;

    void draw(SDL_Renderer *);
    void update(SDL_Renderer *);
};
