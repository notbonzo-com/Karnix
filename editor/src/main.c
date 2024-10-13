#include <stdio.h>

#include <defines.h>
#include <core/log.h>
#include <core/assert.h>
#include <core/window.h>
#include <core/app.h>

#include <renderer/core.h>

int main() {
    init_log(LOG_TYPE_STDOUT, nullptr);

    app_config_t config = {0};
    if (init_app(&config, "Editor", 1280, 720) == false) {
        return -1;
    }

    struct app_event event;
    while (event.event.category != EVENT_CATEGORY_EXIT) {
        if (app_run(&event) == false) {
            static renderer_packet_t packed = {0};
            packed.delta_time = event.delta_time;

            // draw stuff

            renderer_present(&packed);
        }
        switch (event.event.category) {
            case EVENT_CATEGORY_KEY:
                if (event.event.key_event.type == KEY_EVENT_DOWN) {
                    if (event.event.key_event.key == KEY_ESCAPE) {
                        event.event.category = EVENT_CATEGORY_EXIT;
                    }
                }
                break;
            default:
                break;
        }
    }

    term_app();
    term_log(nullptr);
    return 0;
}
