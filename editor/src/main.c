#include <stdio.h>
#include <SDL3/SDL.h>

#include <defines.h>
#include <core/log.h>
#include <core/assert.h>
#include <core/window.h>


int main(int, char*[]) {
    init_log(LOG_TYPE_STDOUT, nullptr);

    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return -1;
    }
    HANDLE window = {0};
    if (init_window(&window, "Editor", 1280, 720) == false) {
        return -1;
    }

    b8 running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
    }

    destroy_window(&window);
    term_log(nullptr);
    return 0;
}
