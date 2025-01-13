#pragma once

#include "../include/v2.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <vector>

struct World {
    v2 size;
    std::vector<std::vector<int>> map_data;

    World(v2 size);

    void draw();
    void update();
};
