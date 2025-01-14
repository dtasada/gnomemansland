#pragma once

#include "../include/v2.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <vector>

<<<<<<< HEAD
#define TILE_SIZE 30

struct World {
=======
class World {
>>>>>>> d1be5c599f801a769e5a26396f4c5ae8988ed56f
    v2 size;
    std::vector<std::vector<int>> map_data;

  public:
    World(v2 size);

    void draw();
    void update();
};
