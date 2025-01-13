#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>

#include "../include/engine.hpp"

int main() {
    Game *game = new Game();

    SDL_Rect rect = {0, 0, 100, 100};

    SDL_Event event;
    while (game->running) {
        SDL_PollEvent(&event);

        switch (event.type) {
        case SDL_QUIT:
            game->running = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                game->running = false;
                break;
            }
            break;
        }

        SDL_Delay(1000.0f / game->fps);

        SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
        SDL_RenderClear(game->renderer);

        SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(game->renderer, &rect);

        SDL_RenderPresent(game->renderer);
    }

    delete game;
    return EXIT_SUCCESS;
}
