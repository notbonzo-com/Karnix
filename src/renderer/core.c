#include <SDL3/SDL.h>
#include <stdlib.h>
#include <string.h>

#include <core/log.h>
#include <core/assert.h>
#include <core/app.h>
#define __GET_INTERNALS__
#include <renderer/core.h>
#include <core/window.h>
#undef __GET_INTERNALS__
#include <renderer/types.h>

struct {
    u64 frame_number;
    vulkan_context_t* vk;
} backend;

VKAPI_ATTR VkBool32 debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType,
                            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void*)
{
    switch (messageSeverity) {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            LOGE(pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            LOGW(pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            LOGI(pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            LOGD(pCallbackData->pMessage);
            break;
        default:
            LOGW(pCallbackData->pMessage);
            break;
    }
    return VK_FALSE;
}

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

    const char* extensions[] = {
        VK_KHR_SURFACE_EXTENSION_NAME,
#ifdef _DEBUG
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME
#endif
    };
    create_info.enabledExtensionCount = (sizeof(extensions) / sizeof(extensions[0]));
#ifdef _DEBUG
    LOGD("Enabled extensions:");
    for (u32 i = 0; i < create_info.enabledExtensionCount; i++) {
        LOGD(extensions[i]);
    }
#endif
    create_info.ppEnabledExtensionNames = extensions;
    
    const char* validation_layers[] = {
#ifdef _DEBUG
        "VK_LAYER_KHRONOS_validation"
#endif
    };
    u32 validation_layers_count = (sizeof(validation_layers) / sizeof(validation_layers[0]));
#ifdef _DEBUG
    for (u32 i = 0; i < validation_layers_count; i++) {
        LOGD("Enabled validation layer: %s", validation_layers[i]);
    }

    u32 available_layers = 0;
    VK_CHECK(vkEnumerateInstanceLayerProperties(&available_layers, nullptr));
    VkLayerProperties* properties = (VkLayerProperties*)malloc(sizeof(VkLayerProperties) * available_layers);
    VK_CHECK(vkEnumerateInstanceLayerProperties(&available_layers, properties));

    for (int i = 0; i < validation_layers_count; i++) {
        b8 found = false;
        for (int j = 0; j < available_layers; j++) {
            if (strcmp(validation_layers[i], properties[j].layerName) == 0) {
                found = true;
                LOGD("Found required validation layer: %s", validation_layers[i]);
                break;
            }
        }
        if (!found) {
            LOGE("Failed to find required validation layer: %s", validation_layers[i]);
            return false;
        }
    }
#endif

    create_info.enabledLayerCount = validation_layers_count;
    create_info.ppEnabledLayerNames = validation_layers;

    VK_CHECK(vkCreateInstance(&create_info, nullptr, &backend.vk->instance));

#ifdef _DEBUG
    u32 log_level = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT \
                    | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT ;//| VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;

    VkDebugUtilsMessengerCreateInfoEXT debug_info = { VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT };
    debug_info.messageSeverity = log_level;
    debug_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
                             | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    debug_info.pfnUserCallback = debug_callback;
    debug_info.pUserData = nullptr;

    PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT)
                                        vkGetInstanceProcAddr(backend.vk->instance, "vkCreateDebugUtilsMessengerEXT");
    ASSERT(func != nullptr, "Failed to get vkCreateDebugUtilsMessengerEXT");
    VK_CHECK(func(backend.vk->instance, &debug_info, nullptr, &backend.vk->debug_messenger));
#endif

    LOGI("Initialised renderer with instance 0x%llx", backend.vk->instance);
    return true;
}

void term_renderer()
{
    if (backend.vk->debug_messenger != nullptr) {
        PFN_vkDestroyDebugUtilsMessengerEXT destroy_func = (PFN_vkDestroyDebugUtilsMessengerEXT)
            vkGetInstanceProcAddr(backend.vk->instance, "vkDestroyDebugUtilsMessengerEXT");
        ASSERT(destroy_func != nullptr, "Failed to get vkDestroyDebugUtilsMessengerEXT");
        destroy_func(backend.vk->instance, backend.vk->debug_messenger, nullptr);
    }
    vkDestroyInstance(backend.vk->instance, nullptr);
    free(backend.vk);
    LOGI("Terminated renderer");
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