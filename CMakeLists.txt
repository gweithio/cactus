cmake_minimum_required(VERSION 3.2)

project(cactus)

message("Generating for system " ${CMAKE_SYSTEM_key})

set(CONAN_DISABLE_CHECK_COMPILER true)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_C_STANDARD 99)

include_directories(include/)
include_directories(include/cactus/)
set(CMAKE_EXPORT_NO_PACKAGE_REGISTRY OFF)

set(PREBUILT_MODULE_PATH ${CMAKE_BINARY_DIR}/modules)

FILE(GLOB SOURCES src/*.c)

add_library(cactus_lib STATIC ${SOURCES})
add_executable(cactus ${SOURCES})
target_link_libraries(cactus ${CONAN_LIBS})

set(CMAKE__FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -O3 -ggdb -pedantic")
