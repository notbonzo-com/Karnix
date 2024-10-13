#include <SDL3/SDL.h>
#include <stdlib.h>

#include <renderer/core.h>
#include <core/log.h>
#include <core/app.h>
#define __GET_INTERNALS__
#include <core/window.h>
#undef __GET_INTERNALS__
#include <renderer/types.h>


struct {
    u64 frame_number;
    vulkan_context_t* vk;
} backend;

b8 init_renderer(app_config_t* state)
{
    backend.frame_number = 0;
    backend.vk = malloc(sizeof(vulkan_context_t));

    VkApplicationInfo info = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
    info.apiVersion = VK_API_VERSION_1_2;
    info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    info.pApplicationName = state->name;
    info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    info.pEngineName = "Karnix Framework";
    
    VkInstanceCreateInfo create_info = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
    create_info.pApplicationInfo = &info;
    create_info.enabledLayerCount = 0;
    create_info.ppEnabledLayerNames = nullptr;
    create_info.enabledExtensionCount = 0;
    create_info.ppEnabledExtensionNames = nullptr;

    VkResult result = vkCreateInstance(&create_info, nullptr, &backend.vk->instance);
    if (result != VK_SUCCESS) {
        LOGE("Failed to create Vulkan instance: %d", result);
        return false;
    }

    LOGI("Initialised renderer with instance 0x%llx", backend.vk->instance);
    return true;
}

void term_renderer()
{
    vkDestroyInstance(backend.vk->instance, nullptr);
    free(backend.vk);
}

b8 renderer_resize(u16 w, u16 h)
{
    return true;
}

b8 renderer_present(renderer_packet_t* packed)
{
    backend.frame_number++;
    return true;
}