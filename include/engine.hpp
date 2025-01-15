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

int64_t randint(int64_t min, int64_t max);
float rand01();

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
