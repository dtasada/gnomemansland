#pragma once

#include <SDL2/SDL.h>
#include <cstdint>
#include <string>

#ifdef __linux
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>
#elif __APPLE__
#include <SDL_image.h>
#include <SDL_net.h>
#endif

#include "v2.hpp"

int randint(int min, int max);
int rand01();

struct Settings {
    struct {
        v2 resolution = v2(1280, 720);
    } video;

    struct {
        bool enable = true;
        std::string server_host = "127.0.0.1";
        uint16_t server_port = 4444;
    } multiplayer;
};
