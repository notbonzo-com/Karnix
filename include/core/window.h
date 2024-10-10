#ifndef _WINDOW_H
#define _WINDOW_H

#include <defines.h>
#include <SDL3/SDL.h>
#include <core/event.h>

#ifdef __GET_INTERNALS__
struct Window {
    SDL_Window *window;
    SDL_Renderer *renderer;
    int w, h;
    char* title;
    b8 fullscreen;
};
#define H2W(h) ((struct Window*)h->handle)
#define W2H(w) ((HANDLE){ .handle = ((void*)w) })
#endif

typedef struct {
    u64 handle;
} HANDLE;

b8 init_window(HANDLE* window, const char* title, int w, int h);
void destroy_window(HANDLE* window);

b8 window_set_fullscreen(HANDLE* window, b8 fullscreen);
b8 window_set_title(HANDLE* window, const char* title);

b8 window_get_position(HANDLE* window, int* x, int* y);
b8 window_get_size(HANDLE* window, int* w, int* h);
b8 window_get_fullscreen(HANDLE* window);

b8 window_set_position(HANDLE* window, int x, int y);
b8 window_set_size(HANDLE* window, int w, int h);

#endif // _WINDOW_H