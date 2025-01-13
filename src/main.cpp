#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <cstdlib>
#include <iostream>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        std::cerr << "Failed to initialize SDL" << SDL_GetError() << std::endl;
        SDL_Quit();
        std::exit(EXIT_FAILURE);
    };

    SDL_Window *window = SDL_CreateWindow(
        "PO6", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
    if (!window) {
        std::cerr << "Failed to create SDL Window" << SDL_GetError()
                  << std::endl;
        SDL_Quit();
        std::exit(EXIT_FAILURE);
    }
    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Failed to create SDL Renderer" << SDL_GetError()
                  << std::endl;
        SDL_Quit();
        std::exit(EXIT_FAILURE);
    }

    bool running = true;
    SDL_Rect rect = {0, 0, 100, 100};

    SDL_Event event;
    while (running) {
        SDL_PollEvent(&event);

        switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                running = false;
                break;
            }
            break;
        }

        SDL_Delay(1000.0f / 60.0f);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return EXIT_SUCCESS;
}
