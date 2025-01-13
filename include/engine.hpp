#include <SDL2/SDL.h>
#include <string>

struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
    float fps;
    float dt;
    bool running;

    Game();
    ~Game();
};

int exit_failure(std::string message);
