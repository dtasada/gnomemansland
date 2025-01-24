#pragma once

#include "../include/engine.hpp"
#include "../include/v2.hpp"

#include <csignal>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <vector>

inline namespace Color {
    inline rgb WATER_LOW     = rgb(0, 0, 50);
    inline rgb WATER_HIGH    = rgb(30, 110, 140);
    inline rgb SAND_LOW      = rgb(237, 206, 178);
    inline rgb SAND_HIGH     = rgb(255, 245, 193);
    inline rgb GRASS_LOW    = rgb(10, 155, 104);
    inline rgb GRASS_HIGH     = rgb(0, 120, 80);
    inline rgb MOUNTAIN_LOW  = rgb(80, 80, 80);
    inline rgb MOUNTAIN_HIGH = rgb(120, 120, 120);
};

inline namespace TileData {
    inline float WATER    = 0.48f;
    inline float SAND     = 0.51;
    inline float GRASS    = 0.61f;
    inline float MOUNTAIN = 0.68f;
    inline float SNOW     = 1.f;
};

class World {
  public:
    World() = default;
    World(Settings, SDL_Renderer*);

    v2u   size;
    float render_scale;

    std::vector<std::vector<rgb>> map_data;

    SDL_Surface *surf;
    Uint32      *pixels;
    SDL_Texture *tex;
    SDL_Rect rect;

    int width;
    int height;

    void draw(SDL_Renderer *);
    void update(SDL_Renderer *);
};
