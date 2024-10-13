#ifndef _CORE_H
#define _CORE_H

#include <defines.h>
#include <core/window.h>
#include <core/app.h>

#ifdef __GET_INTERNALS__
#define VK_CHECK(x)                                           \
    do {                                                      \
        VkResult err = x;                                     \
        if (err) {                                            \
            LOGE("Vulkan error: %d", err);                    \
            return false;                                     \
        }                                                     \
    } while (0)
#endif

typedef struct renderer_packet {
    f32 delta_time;
} renderer_packet_t;

b8 init_renderer(app_config_t* state);
void term_renderer();

b8 renderer_resize(u16 w, u16 h);

b8 renderer_present(renderer_packet_t* packed);

#endif // _CORE_H