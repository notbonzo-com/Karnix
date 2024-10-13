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

        switch (event.event.category) {
            case EVENT_CATEGORY_KEY:
                switch (event.event.key_event.type)
                {
                    case KEY_EVENT_DOWN:
                        printf("Key down: %d\n", event.event.key_event.scancode);
                        break;
                    case KEY_EVENT_UP:
                        printf("Key up: %d\n", event.event.key_event.scancode);
                        break;
                }
        }

    }

    term_app();
    term_log(nullptr);
    return 0;
}
