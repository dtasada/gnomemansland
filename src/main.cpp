#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>
#include <cstdint>
#include <cstdlib>

#include "../include/game.hpp"

int main() {
    Game* game = new Game();

    Sprite p1(game->renderer, "../resources/grass.png", {0, 0, 100, 100});
    Sprite p2(game->renderer, "../resources/grass.png", {0, 200, 200, 200});

    SDL_Event event;
    const uint8_t* scancodes = SDL_GetKeyboardState(NULL);

    while (game->running) {
        SDL_PollEvent(&event);
        SDL_PumpEvents();

        switch (event.type) {
            case SDL_QUIT:
                game->running = false;
                break;
        }

        if (scancodes[SDL_SCANCODE_ESCAPE])
            game->running = false;

        if (scancodes[SDL_SCANCODE_W])
            p1.rect.y -= 10;
        if (scancodes[SDL_SCANCODE_S])
            p1.rect.y += 10;
        if (scancodes[SDL_SCANCODE_A])
            p1.rect.x -= 10;
        if (scancodes[SDL_SCANCODE_D])
            p1.rect.x += 10;

        if (scancodes[SDL_SCANCODE_UP])
            p2.rect.y -= 10;
        if (scancodes[SDL_SCANCODE_DOWN])
            p2.rect.y += 10;
        if (scancodes[SDL_SCANCODE_LEFT])
            p2.rect.x -= 10;
        if (scancodes[SDL_SCANCODE_RIGHT])
            p2.rect.x += 10;

        SDL_Delay(1000.0f / game->fps);

        SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
        SDL_RenderClear(game->renderer);

        SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(game->renderer, &p1.rect);
        p1.copy(game->renderer);
        p2.copy(game->renderer);

        game->world.update();

        SDL_RenderPresent(game->renderer);
    }

    delete game;
    return EXIT_SUCCESS;
}
