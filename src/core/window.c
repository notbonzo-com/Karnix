#define __GET_INTERNALS__
#include <core/window.h>
#include <core/assert.h>
#include <core/log.h>
#include <stdlib.h>
#include <SDL3/SDL_events.h>

// FIXME: Mutexes and threading for everything !

b8 init_window(HANDLE* window, const char* title, int w, int h)
{
    ASSERTF(SDL_WasInit(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_AUDIO), "SDL3 was not initialised, are you creating a window before initializing the engine?");
    ASSERTF(window->handle == 0, "Window already initialised");
    struct Window* win = (struct Window*)malloc(sizeof(struct Window));
    window->handle = (u64)(void*)win;
    win->window = SDL_CreateWindow(title, w, h, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
    if (win->window == nullptr) {
        LOGE("Failed to create window: %s", SDL_GetError());
        return false;
    }
    win->renderer = SDL_CreateRenderer(win->window, nullptr);
    if (win->renderer == nullptr) {
        LOGE("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(win->window);
        return false;
    }

    win->w = w;
    win->h = h;
    win->title = strdup(title);
    win->fullscreen = false;

    LOGD("Initialised window: %dx%d", w, h);
    return true;
}

void destroy_window(HANDLE* window)
{
    // FIXME: Assert if vulkan aint using this
    struct Window* win = H2W(window);
    if (win) {} else {
        LOGE("Not initialised!");
        return;
    }

    SDL_DestroyRenderer(win->renderer);
    SDL_DestroyWindow(win->window);
    free(win->title);
    free(win);
}

b8 window_set_fullscreen(HANDLE* window, b8 fullscreen)
{
    if (SDL_SetWindowFullscreen(H2W(window)->window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0) == 0) {
        LOGW("Failed to set fullscreen: %s", SDL_GetError());
        return false;
    }
    H2W(window)->fullscreen = fullscreen;
    return true;
}

b8 window_set_title(HANDLE* window, const char* title)
{
    if (SDL_SetWindowTitle(H2W(window)->window, title) == 0) {
        LOGW("Failed to set window title: %s", SDL_GetError());
        return false;
    }
    free(H2W(window)->title);
    H2W(window)->title = strdup(title);
    return true;
}

b8 window_get_position(HANDLE* window, int* x, int* y)
{
    if (SDL_GetWindowPosition(H2W(window)->window, x, y) == 0) {
        LOGW("Failed to get window position: %s", SDL_GetError());
        return false;
    }
    return true;
}

b8 window_get_size(HANDLE* window, int* w, int* h)
{
    if (SDL_GetWindowSize(H2W(window)->window, w, h) == 0) {
        LOGW("Failed to get window size: %s", SDL_GetError());
        return false;
    }
    return true;
}

b8 window_get_fullscreen(HANDLE* window)
{
    if (SDL_GetWindowFlags(H2W(window)->window) & SDL_WINDOW_FULLSCREEN) {
        return true;
    }
    return false;
}

b8 window_set_position(HANDLE* window, int x, int y)
{
    ASSERTF(window->handle != 0, "Window not initialised");
    if (SDL_SetWindowPosition(H2W(window)->window, x, y) == 0) {
        LOGW("Failed to set window position: %s", SDL_GetError());
        return false;
    }
    return true;
}

b8 window_set_size(HANDLE* window, int w, int h)
{
    if (SDL_SetWindowSize(H2W(window)->window, w, h) == 0) {
        LOGW("Failed to set window size: %s", SDL_GetError());
        return false;
    }
    return true;
}