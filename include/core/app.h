#ifndef _APP_H
#define _APP_H

#include <defines.h>
#include <core/window.h>
#include <core/event.h>

typedef struct app_config
{
    b8 running;
    f64 last_frame_time;
    char* name;
    HANDLE window;
} app_config_t;

/**
 * @warning Assumes that `config` is allocated by caller, unlike init_window!
 */
b8 init_app(app_config_t* config, const char* name, s32 w, s32 h);
void term_app();

typedef struct app_event {
    EVENT event;
    f32 delta_time;
    f32 fps;
} app_event_t;

b8 app_run(app_event_t* event);

#endif // _APP_H