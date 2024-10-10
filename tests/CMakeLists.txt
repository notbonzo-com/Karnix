# tests/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

file(GLOB TEST_SOURCES *.c)
add_executable(KarnixTest ${TEST_SOURCES})

set(KARNIX_LIB "${CMAKE_SOURCE_DIR}/build/libKarnix.so")

target_link_libraries(KarnixTest ${KARNIX_LIB} ${SDL2_LIBRARIES} ${Vulkan_LIBRARIES})
