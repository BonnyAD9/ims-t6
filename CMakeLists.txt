# Author: Jakub Antonín Štigler (xstigl00)

cmake_minimum_required(VERSION 3.16)

project(ims-t6 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ims-t6)

file(GLOB ims-t6_files CONFIGURE_DEPENDS "src/**/*.cpp" "src/*.cpp")
target_sources(ims-t6 PRIVATE ${ims-t6_files})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -fsanitize=address")
    target_link_libraries(ims-t6 PRIVATE -fsanitize=address)
endif()

target_link_libraries(ims-t6 PRIVATE
    pcap
)
