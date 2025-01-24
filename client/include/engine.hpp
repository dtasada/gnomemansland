#pragma once

#if defined(__linux)
#    include <SDL2/SDL_image.h>
#    include <SDL2/SDL_net.h>
#elif defined(__APPLE__) || defined(_WIN32)
#    include <SDL_image.h>
#    include <SDL_net.h>
#endif

#ifdef _WIN32
#    include <SDL.h>
#else
#    include <SDL2/SDL.h>
#endif

#include "v2.hpp"
#include "v3.hpp"

#include <cstdint>
#include <string>

rgb     lerp_color(rgb c1, rgb c2, float m);
int64_t randint64(int64_t min, int64_t max);
float   rand01();

inline namespace Color {
    inline rgb WATER_LOW     = rgb(0, 0, 50);
    inline rgb WATER_HIGH    = rgb(30, 110, 140);
    inline rgb SAND_LOW      = rgb(237, 206, 178);
    inline rgb SAND_HIGH     = rgb(255, 245, 193);
    inline rgb GRASS_LOW     = rgb(0, 140, 90);
    inline rgb GRASS_HIGH    = rgb(0, 120, 80);
    inline rgb MOUNTAIN_LOW  = rgb(80, 80, 80);
    inline rgb MOUNTAIN_HIGH = rgb(120, 120, 120);
};

struct Settings {
    struct {
        v2u      resolution       = v2u(1280, 720);
        uint16_t target_framerate = 60;
    } video;

    struct {
        bool        enable                  = true;
        std::string server_host             = "127.0.0.1";
        uint16_t    server_port             = 4444;
        uint32_t    server_polling_interval = 200;
    } multiplayer;

    struct {
        v2u      resolution  = v2u(800, 800);
        uint32_t seed        = randint64(0, UINT32_MAX);
        int      octaves     = 10;
        float    persistence = 0.5f;
        float    lacunarity  = 2.0f;
        float    frequency   = 0.004f;
    } world_generation;
};
