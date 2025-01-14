#include "../include/world.hpp"
#include "../include/engine.hpp"
#include "../include/perlin.hpp"
#include <iostream>

World::World(v2 size) : size(size) {
    map_data = std::vector<std::vector<Tile>>(size.y, std::vector<Tile>(size.x));
    z = 0;

    PerlinNoise pn(rand01()); // Seed value
    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            map_data[y][x] = Tile::DEEP_WATER;
        }
    }
}

void World::update(SDL_Renderer *renderer) {
    draw(renderer);
}

void World::draw(SDL_Renderer *renderer) {
    PerlinNoise pn(rand01()); // Seed value

    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            z += 0.0000003;
            // Tile tile = map_data[y][x];
            int blit_x = x * TILE_SIZE;
            int blit_y = y * TILE_SIZE;
            SDL_Rect rect = {blit_x, blit_y, TILE_SIZE, TILE_SIZE};

            float mult = 0.04;
            // (-1, 1) interval
            double h = (pn.noise(x * mult, y * mult, z) + 1) * 0.5;
            Tile tile;
            if (h <= 0.4) {
                tile = Tile::DEEP_WATER;
            } else if (h <= 0.5) {
                tile = Tile::WATER;
            } else if (h <= 0.53) {
                tile = Tile::SAND;
            } else {
                tile = Tile::GRASS;
            }
            map_data[y][x] = tile;

            switch (tile) {
                case Tile::DEEP_WATER:
                    SDL_SetRenderDrawColor(renderer, 23, 80, 172, 255);
                    break;
                case Tile::WATER:
                    SDL_SetRenderDrawColor(renderer, 70, 130, 180, 255);
                    break;
                case Tile::SAND:
                    SDL_SetRenderDrawColor(renderer, 231, 215, 190, 255);
                    break;
                case Tile::GRASS:
                    SDL_SetRenderDrawColor(renderer, 86, 125, 70, 255);
                    break;
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}
