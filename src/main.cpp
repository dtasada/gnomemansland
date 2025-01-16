#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <toml++/toml.hpp>

#include "../include/game.hpp"

int main() {
    srand(time(nullptr));

    Settings settings;
    try {
        auto settings_t = toml::parse_file("../settings.toml");
        if(!settings_t.empty()) {
            settings = {
                .video =
                    {
                        .resolution = v2(settings_t["video"]["resolution"][0].value_or(settings.video.resolution.x),
                                         settings_t["video"]["resolution"][1].value_or(settings.video.resolution.y)),
                    },
                .multiplayer =
                    {
                        .enable = settings_t["multiplayer"]["enable"].value_or(settings.multiplayer.enable),
                        .server_host = settings_t["multiplayer"]["server_host"].value_or(settings.multiplayer.server_host),
                        .server_port = settings_t["multiplayer"]["server_port"].value_or(settings.multiplayer.server_port),
                    },
                .world_generation =
                    {
                        .seed = settings_t["world_generation"]["seed"].value_or(settings.world_generation.seed),
                        .octaves = settings_t["world_generation"]["octaves"].value_or(settings.world_generation.octaves),
                        .persistence =
                            settings_t["world_generation"]["persistence"].value_or(settings.world_generation.persistence),
                        .lacunarity =
                            settings_t["world_generation"]["lacunarity"].value_or(settings.world_generation.lacunarity),
                        .frequency = settings_t["world_generation"]["frequency"].value_or(settings.world_generation.frequency),
                    },
            };
        }
    } catch(const toml::parse_error &err) {
        std::cerr << "Failed to parse config file: " << err.what()
                  << std::endl;
    }

    Game *game = new Game(settings);

    Sprite p1(game->renderer, "../resources/grass.png", {0, 0, 100, 100});
    Sprite p2(game->renderer, "../resources/grass.png", {0, 200, 200, 200});

    SDL_Event event;
    const uint8_t *scancodes = SDL_GetKeyboardState(NULL);

    game->world.update(game->renderer);

    while(game->running) {
        SDL_PollEvent(&event);
        SDL_PumpEvents();

        switch(event.type) {
        case SDL_QUIT: game->running = false; break;
        }

        if(scancodes[SDL_SCANCODE_ESCAPE])
            game->running = false;

        if(scancodes[SDL_SCANCODE_W])
            p1.rect.y -= 10;
        if(scancodes[SDL_SCANCODE_S])
            p1.rect.y += 10;
        if(scancodes[SDL_SCANCODE_A])
            p1.rect.x -= 10;
        if(scancodes[SDL_SCANCODE_D])
            p1.rect.x += 10;

        if(scancodes[SDL_SCANCODE_UP])
            p2.rect.y -= 10;
        if(scancodes[SDL_SCANCODE_DOWN])
            p2.rect.y += 10;
        if(scancodes[SDL_SCANCODE_LEFT])
            p2.rect.x -= 10;
        if(scancodes[SDL_SCANCODE_RIGHT])
            p2.rect.x += 10;

        if(scancodes[SDL_SCANCODE_UP])
            game->world.render_scale += 1;

        if(scancodes[SDL_SCANCODE_DOWN] && game->world.render_scale > 1)
            game->world.render_scale -= 1;

        SDL_Delay(1000.0f / game->fps);

        game->world.update(game->renderer);

        SDL_RenderPresent(game->renderer);
    }

    delete game;
    return EXIT_SUCCESS;
}
