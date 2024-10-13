#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <core/event.h>

static KEYSYM sdl_to_keysym(SDL_Keycode sdl_key) {
    switch (sdl_key) {
        case SDLK_A: return KEY_A;
        case SDLK_B: return KEY_B;
        case SDLK_C: return KEY_C;
        case SDLK_D: return KEY_D;
        case SDLK_E: return KEY_E;
        case SDLK_F: return KEY_F;
        case SDLK_G: return KEY_G;
        case SDLK_H: return KEY_H;
        case SDLK_I: return KEY_I;
        case SDLK_J: return KEY_J;
        case SDLK_K: return KEY_K;
        case SDLK_L: return KEY_L;
        case SDLK_M: return KEY_M;
        case SDLK_N: return KEY_N;
        case SDLK_O: return KEY_O;
        case SDLK_P: return KEY_P;
        case SDLK_Q: return KEY_Q;
        case SDLK_R: return KEY_R;
        case SDLK_S: return KEY_S;
        case SDLK_T: return KEY_T;
        case SDLK_U: return KEY_U;
        case SDLK_V: return KEY_V;
        case SDLK_W: return KEY_W;
        case SDLK_X: return KEY_X;
        case SDLK_Y: return KEY_Y;
        case SDLK_Z: return KEY_Z;

        case SDLK_1: return KEY_1;
        case SDLK_2: return KEY_2;
        case SDLK_3: return KEY_3;
        case SDLK_4: return KEY_4;
        case SDLK_5: return KEY_5;
        case SDLK_6: return KEY_6;
        case SDLK_7: return KEY_7;
        case SDLK_8: return KEY_8;
        case SDLK_9: return KEY_9;
        case SDLK_0: return KEY_0;

        case SDLK_RETURN: return KEY_RETURN;
        case SDLK_ESCAPE: return KEY_ESCAPE;
        case SDLK_BACKSPACE: return KEY_BACKSPACE;
        case SDLK_TAB: return KEY_TAB;
        case SDLK_SPACE: return KEY_SPACE;

        case SDLK_MINUS: return KEY_MINUS;
        case SDLK_EQUALS: return KEY_EQUALS;
        case SDLK_LEFTBRACKET: return KEY_LEFTBRACKET;
        case SDLK_RIGHTBRACKET: return KEY_RIGHTBRACKET;
        case SDLK_BACKSLASH: return KEY_BACKSLASH;
        case SDLK_SEMICOLON: return KEY_SEMICOLON;
        case SDLK_APOSTROPHE: return KEY_APOSTROPHE;
        case SDLK_GRAVE: return KEY_GRAVE;
        case SDLK_COMMA: return KEY_COMMA;
        case SDLK_PERIOD: return KEY_PERIOD;
        case SDLK_SLASH: return KEY_SLASH;

        case SDLK_F1: return KEY_F1;
        case SDLK_F2: return KEY_F2;
        case SDLK_F3: return KEY_F3;
        case SDLK_F4: return KEY_F4;
        case SDLK_F5: return KEY_F5;
        case SDLK_F6: return KEY_F6;
        case SDLK_F7: return KEY_F7;
        case SDLK_F8: return KEY_F8;
        case SDLK_F9: return KEY_F9;
        case SDLK_F10: return KEY_F10;
        case SDLK_F11: return KEY_F11;
        case SDLK_F12: return KEY_F12;

        case SDLK_PRINTSCREEN: return KEY_PRINTSCREEN;
        case SDLK_SCROLLLOCK: return KEY_SCROLLLOCK;
        case SDLK_PAUSE: return KEY_PAUSE;
        case SDLK_INSERT: return KEY_INSERT;
        case SDLK_HOME: return KEY_HOME;
        case SDLK_PAGEUP: return KEY_PAGEUP;
        case SDLK_DELETE: return KEY_DELETE;
        case SDLK_END: return KEY_END;
        case SDLK_PAGEDOWN: return KEY_PAGEDOWN;

        case SDLK_RIGHT: return KEY_RIGHT;
        case SDLK_LEFT: return KEY_LEFT;
        case SDLK_DOWN: return KEY_DOWN;
        case SDLK_UP: return KEY_UP;

        case SDLK_NUMLOCKCLEAR: return KEY_NUMLOCK;
        case SDLK_KP_DIVIDE: return KEY_KP_DIVIDE;
        case SDLK_KP_MULTIPLY: return KEY_KP_MULTIPLY;
        case SDLK_KP_MINUS: return KEY_KP_MINUS;
        case SDLK_KP_PLUS: return KEY_KP_PLUS;
        case SDLK_KP_ENTER: return KEY_KP_ENTER;
        case SDLK_KP_1: return KEY_KP_1;
        case SDLK_KP_2: return KEY_KP_2;
        case SDLK_KP_3: return KEY_KP_3;
        case SDLK_KP_4: return KEY_KP_4;
        case SDLK_KP_5: return KEY_KP_5;
        case SDLK_KP_6: return KEY_KP_6;
        case SDLK_KP_7: return KEY_KP_7;
        case SDLK_KP_8: return KEY_KP_8;
        case SDLK_KP_9: return KEY_KP_9;
        case SDLK_KP_0: return KEY_KP_0;
        case SDLK_KP_PERIOD: return KEY_KP_PERIOD;

        case SDLK_LCTRL: return KEY_CTRL_LEFT;
        case SDLK_LSHIFT: return KEY_SHIFT_LEFT;
        case SDLK_LALT: return KEY_ALT_LEFT;
        case SDLK_LGUI: return KEY_GUI_LEFT;
        case SDLK_RCTRL: return KEY_CTRL_RIGHT;
        case SDLK_RSHIFT: return KEY_SHIFT_RIGHT;
        case SDLK_RALT: return KEY_ALT_RIGHT;
        case SDLK_RGUI: return KEY_GUI_RIGHT;

        case SDLK_MEDIA_PLAY: return KEY_MEDIA_PLAYPAUSE;
        case SDLK_MEDIA_STOP: return KEY_MEDIA_STOP;
        case SDLK_MEDIA_PREVIOUS_TRACK: return KEY_MEDIA_PREVIOUS;
        case SDLK_MEDIA_NEXT_TRACK: return KEY_MEDIA_NEXT;
        case SDLK_MUTE: return KEY_MEDIA_MUTE;
        case SDLK_VOLUMEUP: return KEY_VOLUME_UP;
        case SDLK_VOLUMEDOWN: return KEY_VOLUME_DOWN;

        case SDLK_CAPSLOCK: return KEY_CAPSLOCK;
        case SDLK_APPLICATION: return KEY_APPLICATION;
        case SDLK_POWER: return KEY_POWER;

        default: return KEY_NONE;
    }
}

static void decode_sdl_key_event(SDL_Event* sdl_event, EVENT* karnix_event) {
    SDL_KeyboardEvent* keyboard_event = &sdl_event->key;

    karnix_event->category = EVENT_CATEGORY_KEY;
    karnix_event->key_event.type = (keyboard_event->type == SDL_EVENT_KEY_DOWN) ? KEY_EVENT_DOWN : KEY_EVENT_UP;
    karnix_event->key_event.scancode = keyboard_event->scancode;
    karnix_event->key_event.key = sdl_to_keysym(keyboard_event->key);
    karnix_event->key_event.pressed = keyboard_event->down;
}

static void decode_sdl_mouse_event(SDL_Event* sdl_event, EVENT* karnix_event) {
    karnix_event->category = EVENT_CATEGORY_MOUSE;

    if (sdl_event->type == SDL_EVENT_MOUSE_BUTTON_DOWN || sdl_event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
        karnix_event->mouse_event.x = sdl_event->button.x;
        karnix_event->mouse_event.y = sdl_event->button.y;
        karnix_event->mouse_event.button = sdl_event->button.button;

        if (sdl_event->button.button == SDL_BUTTON_LEFT) {
            karnix_event->mouse_event.type = (sdl_event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) 
                                             ? MOUSE_EVENT_CLICK 
                                             : MOUSE_EVENT_BUTTON_UP;
        } else if (sdl_event->button.button == SDL_BUTTON_MIDDLE) {
            karnix_event->mouse_event.type = (sdl_event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) 
                                             ? MOUSE_EVENT_MIDDLE_CLICK 
                                             : MOUSE_EVENT_BUTTON_UP;
        } else if (sdl_event->button.button == SDL_BUTTON_RIGHT) {
            karnix_event->mouse_event.type = (sdl_event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) 
                                             ? MOUSE_EVENT_RIGHT_CLICK 
                                             : MOUSE_EVENT_BUTTON_UP;
        }
        
        karnix_event->mouse_event.pressed = (sdl_event->type == SDL_EVENT_MOUSE_BUTTON_DOWN);
    } else if (sdl_event->type == SDL_EVENT_MOUSE_MOTION) {
        karnix_event->mouse_event.type = MOUSE_EVENT_MOVE;
        karnix_event->mouse_event.x = sdl_event->motion.x;
        karnix_event->mouse_event.y = sdl_event->motion.y;
    }
}

static void decode_sdl_window_event(SDL_Event* sdl_event, EVENT* karnix_event) {
    karnix_event->category = EVENT_CATEGORY_WINDOW;

    if (sdl_event->window.type == SDL_EVENT_WINDOW_RESIZED) {
        karnix_event->window_event.type = WINDOW_EVENT_RESIZE;
        karnix_event->window_event.width = sdl_event->window.data1;
        karnix_event->window_event.height = sdl_event->window.data2;
    }
}

static void decode_sdl_text_input_event(SDL_Event* sdl_event, EVENT* karnix_event) {
    karnix_event->category = EVENT_CATEGORY_TEXT_INPUT;
    strncpy(karnix_event->text_input_event.text, sdl_event->text.text, sizeof(karnix_event->text_input_event.text) - 1);
    karnix_event->text_input_event.text[sizeof(karnix_event->text_input_event.text) - 1] = '\0';
}

b8 event_decode(SDL_Event* sdl_event, EVENT* karnix_event) {
    switch (sdl_event->type) {
        case SDL_EVENT_QUIT:
            karnix_event->category = EVENT_CATEGORY_EXIT;
            break;
        case SDL_EVENT_KEY_DOWN:
        case SDL_EVENT_KEY_UP:
            decode_sdl_key_event(sdl_event, karnix_event);
            break;
        
        case SDL_EVENT_MOUSE_MOTION:
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        case SDL_EVENT_MOUSE_BUTTON_UP:
            decode_sdl_mouse_event(sdl_event, karnix_event);
            break;
        
        case SDL_EVENT_WINDOW_RESIZED:
            decode_sdl_window_event(sdl_event, karnix_event);
            break;

        case SDL_EVENT_TEXT_INPUT:
            decode_sdl_text_input_event(sdl_event, karnix_event);
            break;
        
        default:
            karnix_event->category = EVENT_CATEGORY_NONE;
            return false;
    }
    return true;
}
