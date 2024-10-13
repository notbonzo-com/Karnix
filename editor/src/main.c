#include <stdio.h>

#include <defines.h>
#include <core/log.h>
#include <core/assert.h>
#include <core/window.h>
#include <core/app.h>

int main() {
    init_log(LOG_TYPE_STDOUT, nullptr);

    app_config_t config = {0};
    if (init_app(&config, "Editor", 1280, 720) == false) {
        return -1;
    }

    struct app_event event;
    while (event.event.category != EVENT_CATEGORY_EXIT) {
        if (app_run(&event) == false) {
            // rendering
        }
        LOGD("Frames per second: %f", event.fps);
    }

    term_app();
    term_log(nullptr);
    return 0;
}
