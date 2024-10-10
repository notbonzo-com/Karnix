# editor/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

file(GLOB EDITOR_SOURCES src/*.c)

include_directories(include ${CMAKE_SOURCE_DIR}/include)

set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/editor/res")
set(HEADER_FILE "${CMAKE_SOURCE_DIR}/editor/include/res.h")
set(SOURCE_FILE "${CMAKE_SOURCE_DIR}/editor/src/res.c")

add_custom_command(
    OUTPUT ${HEADER_FILE} ${SOURCE_FILE}
    COMMAND ${CMAKE_COMMAND} -E env python3 ${CMAKE_SOURCE_DIR}/tools/embed_resources.py
            ${RESOURCE_DIR} ${HEADER_FILE} ${SOURCE_FILE}
    DEPENDS ${RESOURCE_DIR}
    COMMENT "Embedding editor resources..."
)

add_executable(KarnixEditor ${EDITOR_SOURCES} ${HEADER_FILE} ${SOURCE_FILE})

set(KARNIX_LIB "${CMAKE_SOURCE_DIR}/build/libKarnix.so")

target_link_libraries(KarnixEditor ${KARNIX_LIB} ${SDL2_LIBRARIES} ${Vulkan_LIBRARIES})

set_target_properties(KarnixEditor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)
