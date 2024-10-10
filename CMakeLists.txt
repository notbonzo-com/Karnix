# Root CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(Karnix)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/toolchains/linux_toolchain.cmake")
set(CMAKE_C_STANDARD 23)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-D_DEBUG)
endif()

find_package(SDL3 REQUIRED)
find_package(Vulkan REQUIRED)

include_directories(include ${SDL2_INCLUDE_DIRS} ${Vulkan_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES src/*.c)

add_library(Karnix SHARED ${SOURCES})

target_link_libraries(Karnix ${SDL2_LIBRARIES} ${Vulkan_LIBRARIES})

set_target_properties(Karnix PROPERTIES
    OUTPUT_NAME "Karnix"
    LIBRARY_OUTPUT_DIRECTORY "${BINARY_DIR}"
)

add_subdirectory(editor)
# add_subdirectory(tests)