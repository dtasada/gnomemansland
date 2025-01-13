#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <vector>

struct World {
    int width, height;
    std::vector<std::vector<int>> mapData;

    World(int width, int height);

    void draw();
    void update();
};
