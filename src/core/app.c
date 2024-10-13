#include <core/app.h>
#include <core/window.h>
#include <core/log.h>
#include <stdlib.h>

#define FRAME_DELAY 0.001 // (1.0 / 1000)

static app_config_t* current_app = nullptr;

static f64 calculate_delta_time() {
    f64 current_time = (f64)SDL_GetPerformanceCounter() / (f64)SDL_GetPerformanceFrequency();
    f64 delta_time = current_time - current_app->last_frame_time;
    current_app->last_frame_time = current_time;
    return delta_time;
}

b8 init_app(app_config_t* config, const char* name, s32 w, s32 h)
{
    if (current_app != nullptr) {
        LOGE("Application already initialised");
        return false;
    }
    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0) {
        LOGE("Failed to initialize SDL: %s\n", SDL_GetError());
        return false;
    }
    current_app = config;
    config->name = strdup(name);
    config->running = false;
    config->last_frame_time = 0.0;
    if (init_window(&config->window, config->name, w, h) == false) {
        LOGE("Failed to initialise window: %s", SDL_GetError());
        return false;
    }
    config->last_frame_time = (f64)SDL_GetPerformanceCounter() / (f64)SDL_GetPerformanceFrequency();
    return true;
}

void term_app()
{
    free(current_app->name);
    term_window(&current_app->window);
    current_app = nullptr;
}

b8 app_run(app_event_t* event)
{
    event->delta_time = calculate_delta_time();
    if (event->delta_time < FRAME_DELAY) {
        SDL_Delay((u32)((FRAME_DELAY - event->delta_time) * 1000)); 
        event->delta_time = FRAME_DELAY;
    }
    event->event.category = EVENT_CATEGORY_NONE;

    SDL_Event sdl_event;
    while (SDL_PollEvent(&sdl_event)) {
        if (event_decode(&sdl_event, &event->event)) {
            return true;
        }
    }
    event->fps = 1.0 / event->delta_time;

    return false;
}