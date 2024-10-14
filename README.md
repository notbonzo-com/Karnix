# Game Engine / Library (Vulkan + SDL3)

This game engine/library is designed to be lightweight and customizable, allowing developers to directly control the flow of their game from the `main()` function. Unlike traditional game engines that use `Update()` and `Start()` methods, this engine gives full control to the developer for managing the game loop and event handling.

## Features
- **Vulkan for rendering**: High-performance rendering with full control over Vulkan API calls.
- **SDL for window and input management**: Simple abstraction for handling window creation, input events, and more.
- **Customizable**: No predefined `Update()` or `Start()` functions. You decide how the game runs.

## Example Usage
Here's an example program that demonstrates how to use the engine. The program initializes the engine, handles events like key presses, and renders frames:

```c
#include <defines.h>
#include <core/app.h>
#include <core/event.h>
#include <renderer/core.h>

int main() {
    // Initialize logging system
    init_log(LOG_TYPE_STDOUT, nullptr);

    // Configure and initialize the app (window, title, resolution)
    app_config_t config = {0};
    if (init_app(&config, "Window Title", 1280, 720) == false) {
        return -1;
    }

    // Main event loop
    struct app_event event;
    while (event.event.category != EVENT_CATEGORY_EXIT) {
        if (app_run(&event) == false) { // if app_run() returns false, no events occured and frame ended
            static renderer_packet_t packed = {0};
            packed.delta_time = event.delta_time;

            // Render logic
            renderer_present(&packed);
        }
        if (event.event.category == EVENT_CATEGORY_NONE) {
            // alternative to check if app_run() returned false
        }
        
        // Event handling
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

    // Cleanup
    term_app();
    term_log(nullptr);
    return 0;
}
```

### Key Components of the Example:
- **Logging**: The `init_log()` initializes the log system to output information.
- **App Initialization**: `init_app()` configures and sets up the application window and context.
- **Event Handling**: The main loop checks for events (like key presses) and responds accordingly.
- **Rendering**: The `renderer_present()` function is called to present the frame.
- **Cleanup**: `term_app()` and `term_log()` ensure proper termination and cleanup before exiting.

## Getting Started
1. **Initialize the log system**: Use `init_log()` to set up the logging system.
2. **Configure and initialize the app**: Create an `app_config_t` and pass it to `init_app()` to configure window size and title.
3. **Handle events**: Use `app_run()` to get the next event and manage input or rendering accordingly.
4. **Render and present**: Use the Vulkan renderer to handle drawing and present the rendered frame with `renderer_present()`.
5. **Terminate**: Clean up with `term_app()` and `term_log()` before exiting.

## Event Handling
Events are handled using a custom event system that allows direct control of key presses, mouse events, window focus and resize and event text input.

## Building with CMake
To build the project using CMake, follow these steps:

1. **Install dependencies**: Ensure that you have the Vulkan SDK, SDL3, and CMake installed on your system.
2. **Generate the build files**: From the project root directory, run the following command:
    ```bash
    cmake -S . -B build
    ```
3. **Build the project**: Once the build files are generated, navigate to the build directory and run:
    ```bash
    cmake --build build
    ```
4. **Run the application**: After the build is successful, the library libKarnix.so should be found in the build directory.

Make sure your system is properly configured with Vulkan and SDL3 before building.

---