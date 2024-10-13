#ifndef _WINDOW_H
#define _WINDOW_H

#include <defines.h>
#include <SDL3/SDL.h>

/**
 * These macros and structs should not be used by the users as touching them directly may cause undefined behavior.
 * So no touchy things!
 */
#ifdef __GET_INTERNALS__
/**
 * @struct Window
 * @brief Internal structure representing a window and its properties.
 * 
 * @details
 * Contains the SDL window and renderer along with basic window properties like
 * dimensions, title, and fullscreen status.
 */
typedef struct Window {
    SDL_Window *window;     ///< Pointer to the SDL window.
    SDL_Renderer *renderer; ///< Pointer to the SDL renderer.
    u16 w, h;               ///< Width and height of the window.
    char* title;            ///< Title of the window.
    b8 fullscreen;          ///< Indicates if the window is in fullscreen mode.
} Window_t;

#define H2W(h) ((struct Window*)h->handle)              ///< Macro to convert HANDLE to Window pointer.
#define W2H(w) ((HANDLE){ .handle = ((void*)w) })       ///< Macro to convert Window pointer to HANDLE.
#endif

/**
 * @struct HANDLE
 * @brief Opaque handle structure for window management.
 */
typedef struct _HANDLE {
    u64 handle;         ///< Modifiable pointer value.
} HANDLE;

/**
 * @name init_window
 * @brief Initializes a window with the specified parameters.
 * @param window - Pointer to the HANDLE to be initialized.
 * @param title - Title of the window.
 * @param w - Width of the window.
 * @param h - Height of the window.
 * 
 * @returns `true` if the window is successfully created, `false` otherwise.
 */
b8 init_window(HANDLE* window, const char* title, u16 w, u16 h);

/**
 * @name term_window
 * @brief Destroys the specified window and cleans up resources.
 * @param window - Pointer to the HANDLE of the window to be destroyed.
 */
void term_window(HANDLE* window);

/**
 * @name window_set_fullscreen
 * @brief Sets the fullscreen status of the window.
 * @param window - Pointer to the HANDLE of the window.
 * @param fullscreen - Boolean value to set or unset fullscreen.
 * 
 * @returns `true` if successful, `false` otherwise.
 */
b8 window_set_fullscreen(HANDLE* window, b8 fullscreen);

/**
 * @name window_set_title
 * @brief Sets the title of the specified window.
 * @param window - Pointer to the HANDLE of the window.
 * @param title - New title to set for the window.
 * 
 * @returns `true` if successful, `false` otherwise.
 */
b8 window_set_title(HANDLE* window, const char* title);

/**
 * @name window_get_position
 * @brief Retrieves the position of the window.
 * @param window - Pointer to the HANDLE of the window.
 * @param x - Pointer to store the x-coordinate of the window position.
 * @param y - Pointer to store the y-coordinate of the window position.
 * 
 * @returns `true` if successful, `false` otherwise.
 */
b8 window_get_position(HANDLE* window, u16* x, u16* y);

/**
 * @name window_get_size
 * @brief Retrieves the size of the window.
 * @param window - Pointer to the HANDLE of the window.
 * @param w - Pointer to store the width of the window.
 * @param h - Pointer to store the height of the window.
 * 
 * @returns `true` if successful, `false` otherwise.
 */
b8 window_get_size(HANDLE* window, u16* w, u16* h);

/**
 * @name window_get_fullscreen
 * @brief Retrieves the fullscreen status of the window.
 * @param window - Pointer to the HANDLE of the window.
 * 
 * @returns `true` if the window is in fullscreen mode, `false` otherwise.
 */
b8 window_get_fullscreen(HANDLE* window);

/**
 * @name window_set_position
 * @brief Sets the position of the specified window.
 * @param window - Pointer to the HANDLE of the window.
 * @param x - x-coordinate to set the window position.
 * @param y - y-coordinate to set the window position.
 * 
 * @returns `true` if successful, `false` otherwise.
 */
b8 window_set_position(HANDLE* window, u16 x, u16 y);

/**
 * @name window_set_size
 * @brief Sets the size of the specified window.
 * @param window - Pointer to the HANDLE of the window.
 * @param w - New width of the window.
 * @param h - New height of the window.
 * 
 * @returns `true` if successful, `false` otherwise.
 */
b8 window_set_size(HANDLE* window, u16 w, u16 h);

#endif // _WINDOW_H