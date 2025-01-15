#include "../include/world.hpp"
#include "../include/engine.hpp"
#include "../include/perlin.hpp"
#include <iostream>

World::World(v2 size, Settings settings) : size(size) {
    map_data = std::vector<std::vector<Tile>>(size.y, std::vector<Tile>(size.x));
    z = 0;

    int64_t seed = randint(0, SDL_MAX_UINT16);

    printf("Seed %lld\n", seed);
    
    const int octaves = settings.world_generation.octaves;
    const float pers = settings.world_generation.persistence;
    const float lac = settings.world_generation.lacunarity;
            
    PerlinNoise pn(seed); // Seed value
    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            // (-1, 1) interval
            z += 3 * pow(10, -7);

            float freq = settings.world_generation.frequency;
            float total = 0.0f;
            float amp = 1.0f;
            float max_value = 0.0f;

            float nx, ny;
            for (int i = 0; i < octaves; i++) {
                nx = x * freq;
                ny = y * freq;

                total += amp * pn.noise(nx, ny, z);

                max_value += amp;
                amp *= pers;
                freq *= lac;
            }
            // printf("%f %f \n", total, max_value);
            total = (total + max_value) / (max_value * 2);

            float h = total;
            Tile tile;
            if (h <= 0.4) {
                tile = Tile::DEEP_WATER;
            } else if (h <= 0.5) {
                tile = Tile::WATER;
            } else if (h <= 0.52) {
                tile = Tile::SAND;
            } else {
                tile = Tile::GRASS;
            }
            map_data[y][x] = tile;
        }
    }
}

void World::update(SDL_Renderer *renderer) {
    draw(renderer);
}

void World::draw(SDL_Renderer *renderer) {
    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            Tile tile = map_data[y][x];
            int blit_x = x * TILE_SIZE;
            int blit_y = y * TILE_SIZE;
            SDL_Rect rect = {blit_x, blit_y, TILE_SIZE, TILE_SIZE};

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
