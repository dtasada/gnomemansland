#include "../../shared/include/engine.hpp"
#include "../include/game.hpp"
#include "../include/world.hpp"

#include <iostream>
#include <mutex>
#include <nlohmann/json_fwd.hpp>
#include <omp.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <thread>
#include <vector>

Game::Game(Settings st) : target_framerate(st.video.target_framerate), client(st), settings(st) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
        exit_failure("Failed to initialize SDL");

    if (!(window = SDL_CreateWindow(
              "PO6",
              SDL_WINDOWPOS_UNDEFINED,
              SDL_WINDOWPOS_UNDEFINED,
              st.video.resolution.x,
              st.video.resolution.y,
              0
          )))
        exit_failure("Failed to create SDL Window");

    if (!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)))
        exit_failure("Failed to create SDL Renderer");

    world  = World(st, renderer);
    scroll = v2f(0, 0);
    moving = false;

    running = true;
    fetch_world();
}

Game::~Game() {
    if (world_fetch_thread.joinable()) world_fetch_thread.join();

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::fetch_world(void) {
    if (world_fetch_thread.joinable()) world_fetch_thread.join();

    world_fetch_thread = std::thread([this]() {
        client.send(R"({"fetch":"world"})");

        bool handled = false;
        while (!handled) {
            {
                std::lock_guard<std::mutex> lock(message_handle_mutex);

                std::erase_if(client.message_handles, [this, &handled](nlohmann::json handle) {
                    if (handle["descriptor"] == "world") {
                        world.map_data = handle["map_data"].get<std::vector<std::vector<rgb>>>();
                        world.update_map();
                        handled = true;
                    }
                    return handled;
                });
            }

            std::this_thread::sleep_for(
                std::chrono::milliseconds(settings.multiplayer.server_polling_interval)
            );
        }
    });
}

void Game::update(void) { world.draw(scroll); }

int exit_failure(std::string message) {
    std::cerr << message << ": " << SDL_GetError() << std::endl;
    SDL_Quit();
    std::exit(EXIT_FAILURE);
}
