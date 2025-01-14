#include "../include/world.hpp"
#include "../include/engine.hpp"

World::World(v2 size) : size(size) {
    map_data = std::vector<std::vector<int>>(size.y, std::vector<int>(size.x));

    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            map_data[y][x] = 3;
        }
    }
}

void World::update() {
    draw();
}

void World::draw() {
    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            int tile = map_data[y][x];
            int blit_x = x * TILE_SIZE;
            int blit_y = y * TILE_SIZE;
            SDL_Rect rect = {blit_x, blit_y, TILE_SIZE, TILE_SIZE};
            switch (tile) {
                case 3:
                    break;
                    // SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
                    // SDL_RenderFillRect(game->renderer, &p1.rect);
            }
        }
    }
}
