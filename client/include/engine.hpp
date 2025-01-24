#pragma once

#if defined(__linux)
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>
#elif defined(__APPLE__) || defined(_WIN32)
#include <SDL_image.h>
#include <SDL_net.h>
#endif

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <cstdint>
#include <string>

#include "v2.hpp"
#include "v3.hpp"

int64_t randint64(int64_t min, int64_t max);
float rand01();
v3 lerp_color(v3 c1, v3 c2, float m);
float rand01();

<<<<<<< HEAD:include/engine.hpp
// namespace Color {
//     inline v3 WATER_LOW = v3(0, 0, 50);
//     inline v3 WATER_HIGH = v3(30, 110, 140);
//     inline v3 SAND_LOW = v3(237, 206, 178);
//     inline v3 SAND_HIGH = v3(255, 245, 193);
//     inline v3 GRASS_LOW = v3(0, 140, 90);
//     inline v3 GRASS_HIGH = v3(0, 120, 80);
//     inline v3 MOUNTAIN_LOW = v3(80, 80, 80);
//     inline v3 MOUNTAIN_HIGH = v3(120, 120, 120);
// };

struct Color {
    static v3 WATER_LOW;
    static v3 WATER_HIGH;
    static v3 SAND_LOW;
    static v3 SAND_HIGH;
    static v3 GRASS_LOW;
    static v3 GRASS_HIGH;
    static v3 MOUNTAIN_LOW;
    static v3 MOUNTAIN_HIGH;
};
=======
inline namespace Color {
inline v3 WATER_LOW = v3(0, 0, 50);
inline v3 WATER_HIGH = v3(30, 110, 140);
inline v3 SAND_LOW = v3(237, 206, 178);
inline v3 SAND_HIGH = v3(255, 245, 193);
inline v3 GRASS_LOW = v3(0, 140, 90);
inline v3 GRASS_HIGH = v3(0, 120, 80);
inline v3 MOUNTAIN_LOW = v3(80, 80, 80);
inline v3 MOUNTAIN_HIGH = v3(120, 120, 120);
}; // namespace Color
>>>>>>> 6b01fd65cb64f4b7d02199ed09f385304c1b6f5d:client/include/engine.hpp

struct Settings {
    struct {
        v2 resolution = v2(1280, 720);
        uint16_t target_framerate = 60;
    } video;

    struct {
        bool enable = true;
        std::string server_host = "127.0.0.1";
        uint16_t server_port = 4444;
    } multiplayer;

    struct {
        v2 resolution = v2(800, 800);
        uint32_t seed = randint64(0, SDL_MAX_UINT32);
        int octaves = 10;
        float persistence = 0.5f;
        float lacunarity = 2.0f;
        float frequency = 0.004f;
    } world_generation;
};
