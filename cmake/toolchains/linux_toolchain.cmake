# cmake/toolchains/linux_toolchain.cmake

set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O2")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")

set(CMAKE_AR /usr/bin/ar)
set(CMAKE_RANLIB /usr/bin/ranlib)

set(CMAKE_BUILD_TYPE Debug)
