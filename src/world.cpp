#include "../include/world.hpp"
#include "../include/engine.hpp"
#include "../include/perlin.hpp"
#include <iostream>

World::World(v2 size, Settings settings) : size(size) {
    map_data = std::vector<std::vector<v3>>(size.y, std::vector<v3>(size.x));
    z = 0;
    render_scale = 1.0f;

    int64_t seed = randint(0, SDL_MAX_UINT16);

    printf("Seed %lld\n", seed);
    
    const int octaves = settings.world_generation.octaves;
    const float pers = settings.world_generation.persistence;
    const float lac = settings.world_generation.lacunarity;
            
    PerlinNoise pn(seed); // Seed value
    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            z += 3 * pow(10, -7);

            float freq = settings.world_generation.frequency;
            float total = 0.0f;
            float amp = 1.0f;
            float max_value = 0.0f;

            float nx, ny;
            for (int i = 0; i < octaves; i++) {
                nx = x * (freq * 1);
                ny = y * (freq * 1);

                total += amp * pn.noise(nx, ny, z);

                max_value += amp;
                amp *= pers;
                freq *= lac;
            }
            // normalize total height to (0, 1)
            total = (total + max_value) / (max_value * 2);

            v3 tile;
            if (total <= TileData::WATER) {
                tile = lerp_color(Color::WATER_LOW, Color::WATER_HIGH, total / TileData::WATER);
            } else if (total <= TileData::SAND) {
                tile = lerp_color(Color::SAND_LOW, Color::SAND_HIGH, (total - TileData::WATER) / (TileData::WATER - TileData::SAND));
            } else if (total <= TileData::GRASS) {
                tile = lerp_color(Color::GRASS_LOW, Color::GRASS_HIGH, (total - TileData::SAND) / (TileData::GRASS - TileData::SAND));
            } else if (total <= TileData::MOUNTAIN) {
                tile = lerp_color(Color::MOUNTAIN_LOW, Color::MOUNTAIN_HIGH, (total - TileData::GRASS) / (TileData::MOUNTAIN - TileData::GRASS));
            } else {
                tile = v3(255, 255, 255);
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
            v3 tile = map_data[y][x];
            int blit_x = x * render_scale;
        int blit_y = y * render_scale;
            SDL_Rect rect = {blit_x, blit_y, static_cast<int>(render_scale), static_cast<int>(render_scale)};

            SDL_SetRenderDrawColor(renderer, tile.x, tile.y, tile.z, 255);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}
