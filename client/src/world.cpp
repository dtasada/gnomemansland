#include "../include/engine.hpp"
#include "../include/perlin.hpp"
#include "../include/world.hpp"

#include <cstddef>
#include <iostream>
#include <omp.h>

World::World(Settings st, SDL_Renderer *renderer) : size(st.world_generation.resolution) {
    map_data     = std::vector<std::vector<rgb>>(size.y, std::vector<rgb>(size.x));
    render_scale = 1.0f;

    uint32_t seed = st.world_generation.seed;
    std::cout << "Seed: " << seed << std::endl;
    PerlinNoise pn(seed);

    const int   octaves = st.world_generation.octaves;
    const float pers    = st.world_generation.persistence;
    const float lac     = st.world_generation.lacunarity;

    width  = st.world_generation.resolution.x;
    height = st.world_generation.resolution.y;

    // create the map surface
    surf = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA8888);

    pixels = static_cast<uint32_t *>(surf->pixels);

#pragma omp parallel for collapse(2)
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            // get the terrain generation data form the settings file
            float freq      = 7.68f * st.world_generation.frequency / width;
            float height    = 0.0f;
            float amp       = 1.0f;
            float max_value = 0.0f;

            // calculate the noise octaves
            float nx, ny;
            for (int i = 0; i < octaves; i++) {
                nx = x * (freq * 1);
                ny = y * (freq * 1);

                height += amp * pn.noise(nx, ny, 0);

                max_value += amp;
                amp *= pers;
                freq *= lac;
            }
            // normalize total height to (0, 1)
            height = (height + max_value) / (max_value * 2);

            // create linearly interpolated colors for terrain
            rgb tile;

            if (height <= TileData::WATER) {
                tile = lerp_color(Color::WATER_LOW, Color::WATER_HIGH, height / TileData::WATER);
            } else if (height <= TileData::SAND) {
                tile = lerp_color(
                    Color::SAND_LOW,
                    Color::SAND_HIGH,
                    (height - TileData::WATER) / (TileData::SAND - TileData::WATER)
                );
            } else if (height <= TileData::GRASS) {
                tile = lerp_color(
                    Color::GRASS_LOW,
                    Color::GRASS_HIGH,
                    (height - TileData::SAND) / (TileData::GRASS - TileData::SAND)
                );
            } else if (height <= TileData::MOUNTAIN) {
                tile = lerp_color(
                    Color::MOUNTAIN_LOW,
                    Color::MOUNTAIN_HIGH,
                    (height - TileData::GRASS) / (TileData::MOUNTAIN - TileData::GRASS)
                );
            } else {
                tile = rgb(240, 240, 240);
            }


            // color the surface with given tile
            pixels[y * width + x] = SDL_MapRGBA(surf->format, tile.x, tile.y, tile.z, 255);

            // set the data
            map_data[y][x] = tile;
        }
    }

    tex    = SDL_CreateTextureFromSurface(renderer, surf);
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;
}

void World::update(SDL_Renderer *renderer) { draw(renderer); }

void World::draw(SDL_Renderer *renderer) {
    rect.w = width * render_scale;
    rect.h = height * render_scale;
    // std::cout << rect.w << std::endl;

    SDL_RenderCopy(renderer, tex, NULL, &rect);
}
