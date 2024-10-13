#ifndef _RENDERER_TYPES_H
#define _RENDERER_TYPES_H

#include <defines.h>
#include <vulkan/vulkan.h>
#include <SDL3/SDL_vulkan.h>

typedef struct vulkan_context {
    VkInstance instance;
#ifdef _DEBUG
    VkDebugUtilsMessengerEXT debug_messenger;
#endif
} vulkan_context_t;

#endif // _RENDERER_TYPES_H