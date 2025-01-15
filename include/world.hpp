#pragma once

#include "../include/v2.hpp"
#include "../include/engine.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <vector>

#define TILE_SIZE 1

enum class Tile {DEEP_WATER, WATER, SAND, GRASS};

class World {
  public:
    v2 size;
    std::vector<std::vector<Tile>> map_data;
    double z;

    World(v2 size, Settings settings);

    void draw(SDL_Renderer *renderer);
    void update(SDL_Renderer *renderer);
};
