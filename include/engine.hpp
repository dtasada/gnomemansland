#pragma once

#include <SDL2/SDL.h>
#include <cstdint>
#include <string>
#include <iostream>

#ifdef __linux
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>
#elif __APPLE__
#include <SDL_image.h>
#include <SDL_net.h>
#endif

#include "v2.hpp"
#include "v3.hpp"

int64_t randint(int64_t min, int64_t max);
v3 lerp_color(v3 c1, v3 c2, float m);
float rand01();

namespace Color {
    inline v3 WATER_LOW = v3(0, 0, 50);
    inline v3 WATER_HIGH = v3(30, 110, 140);
    inline v3 SAND_LOW = v3(237, 206, 178);
    inline v3 SAND_HIGH = v3(255, 245, 193);
    inline v3 GRASS_LOW = v3(0, 140, 90);
    inline v3 GRASS_HIGH = v3(0, 120, 80);
    inline v3 MOUNTAIN_LOW = v3(80, 80, 80);
    inline v3 MOUNTAIN_HIGH = v3(120, 120, 120);
};

struct Settings {
    struct {
        v2 resolution = v2(1280, 720);
    } video;

    struct {
        bool enable = true;
        std::string server_host = "127.0.0.1";
        uint16_t server_port = 4444;
    } multiplayer;

    struct {
        int octaves = 10;
        float persistence = 0.5f;
        float lacunarity = 2.0f;
        float frequency = 0.004f;
    } world_generation;
};
