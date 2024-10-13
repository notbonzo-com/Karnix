#ifndef _EVENT_H
#define _EVENT_H

#include <defines.h>
#include <SDL3/SDL_events.h>

#define MAX_TEXT_INPUT_LENGTH 32

typedef enum event_category {
    EVENT_CATEGORY_NONE,
    EVENT_CATEGORY_EXIT,
    EVENT_CATEGORY_KEY,
    EVENT_CATEGORY_MOUSE,
    EVENT_CATEGORY_WINDOW,
    EVENT_CATEGORY_TEXT_INPUT,
} event_category_t;

typedef enum key_event_type {
    KEY_EVENT_NONE,
    KEY_EVENT_DOWN,
    KEY_EVENT_UP,
} key_event_type_t;

typedef enum mouse_event_type {
    MOUSE_EVENT_NONE,
    MOUSE_EVENT_MOVE,
    MOUSE_EVENT_CLICK,
    MOUSE_EVENT_MIDDLE_CLICK,
    MOUSE_EVENT_RIGHT_CLICK,
    MOUSE_EVENT_BUTTON_UP,
} mouse_event_type_t;

typedef enum window_event_type {
    WINDOW_EVENT_NONE,
    WINDOW_EVENT_RESIZE
} window_event_type_t;

typedef enum focus_event_type {
    FOCUS_EVENT_NONE,
    FOCUS_EVENT_GAINED,
    FOCUS_EVENT_LOST,
} focus_event_type_t;

typedef u32 KEYSYM;

enum KEYSYM_E {
    // Alphanumeric keys
    KEY_NONE = 0,
    KEY_A = 4,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,

    KEY_1 = 30,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_0,

    // Special characters
    KEY_RETURN = 40,  // Enter
    KEY_ESCAPE,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_SPACE,

    KEY_MINUS = 45,  // '-'
    KEY_EQUALS,
    KEY_LEFTBRACKET,
    KEY_RIGHTBRACKET,
    KEY_BACKSLASH,
    KEY_SEMICOLON = 51,
    KEY_APOSTROPHE,
    KEY_GRAVE,  // `
    KEY_COMMA,
    KEY_PERIOD,
    KEY_SLASH,  // /

    // Function keys
    KEY_F1 = 58,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,

    // Control keys
    KEY_PRINTSCREEN = 70,
    KEY_SCROLLLOCK,
    KEY_PAUSE,
    KEY_INSERT,
    KEY_HOME,
    KEY_PAGEUP,
    KEY_DELETE,
    KEY_END,
    KEY_PAGEDOWN,

    // Arrow keys
    KEY_RIGHT = 79,
    KEY_LEFT,
    KEY_DOWN,
    KEY_UP,

    // Keypad
    KEY_NUMLOCK = 83,
    KEY_KP_DIVIDE,
    KEY_KP_MULTIPLY,
    KEY_KP_MINUS,
    KEY_KP_PLUS,
    KEY_KP_ENTER,
    KEY_KP_1,
    KEY_KP_2,
    KEY_KP_3,
    KEY_KP_4,
    KEY_KP_5,
    KEY_KP_6,
    KEY_KP_7,
    KEY_KP_8,
    KEY_KP_9,
    KEY_KP_0,
    KEY_KP_PERIOD,

    // Modifier keys
    KEY_CTRL_LEFT = 224,
    KEY_SHIFT_LEFT,
    KEY_ALT_LEFT,
    KEY_GUI_LEFT,  // Windows/Super key
    KEY_CTRL_RIGHT,
    KEY_SHIFT_RIGHT,
    KEY_ALT_RIGHT,
    KEY_GUI_RIGHT,

    // Media keys
    KEY_MEDIA_PLAYPAUSE = 258,
    KEY_MEDIA_STOP,
    KEY_MEDIA_PREVIOUS,
    KEY_MEDIA_NEXT,
    KEY_MEDIA_MUTE,
    KEY_VOLUME_UP,
    KEY_VOLUME_DOWN,

    // Additional special keys
    KEY_CAPSLOCK = 57,
    KEY_APPLICATION = 101,  // Context menu key
    KEY_POWER
};

typedef struct key_event_data {
    key_event_type_t type;              // 4 bytes
    int scancode;                       // 4 bytes
    KEYSYM key;                         // 4 bytes
    b8 pressed;                         // 1 byte
    u8 padding[19];                     // 19 bytes (total: 32 bytes)
} key_event_data_t;

typedef struct mouse_event_data {
    mouse_event_type_t type;            // 4 bytes
    int x, y;                           // 8 bytes (2 * 4 bytes)
    int button;                         // 4 bytes
    b8 pressed;                         // 1 byte
    u8 padding[15];                     // 15 bytes (total: 32 bytes)
} mouse_event_data_t;

typedef struct window_event_data {
    window_event_type_t type;           // 4 bytes
    int width, height;                  // 8 bytes (2 * 4 bytes)
    u8 padding[20];                     // 20 bytes (total: 32 bytes)
} window_event_data_t;

typedef struct focus_event_data {
    focus_event_type_t type;            // 4 bytes
    b8 focused;                         // 1 byte
    u8 padding[27];                     // 27 bytes (total: 32 bytes)
} focus_event_data_t;

typedef struct text_input_event_data {
    char text[MAX_TEXT_INPUT_LENGTH];   // 32 bytes (fixed-size buffer)
} text_input_event_data_t;

typedef struct EVENT {
    event_category_t category;
    u8 padding[28];                     // most likely added by gcc anyways
    union {
        key_event_data_t key_event;
        mouse_event_data_t mouse_event;
        window_event_data_t window_event;
        focus_event_data_t focus_event;
        text_input_event_data_t text_input_event;
    };
} EVENT;

b8 decode_sdl_event(SDL_Event* sdl_event, EVENT* custom_event);

#endif // _EVENT_H