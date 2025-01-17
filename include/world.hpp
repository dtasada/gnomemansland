#pragma once

#include "../include/v2.hpp"
#include "../include/engine.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <vector>

// enum class TileType {WATER, SAND, GRASS, MOUNTAIN, SNOW};

struct TileData {
    static constexpr float WATER = 0.5f;
    static constexpr float SAND = 0.54f;
    static constexpr float GRASS = 0.61f;
    static constexpr float MOUNTAIN = 0.68f;
    static constexpr float SNOW = 1.f;
};

class World {
  public:

    v2 size;
    std::vector<std::vector<v3>> map_data;
    double z;
    float render_scale;

    World(v2 size, Settings settings);

    void draw(SDL_Renderer *renderer);
    void update(SDL_Renderer *renderer);
};
