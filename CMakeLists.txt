cmake_minimum_required(VERSION 3.26)
project(Akari)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(vendor)
add_subdirectory(src)

set(RESOURCE_DEST_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res")

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        "${CMAKE_SOURCE_DIR}/res"
        "${RESOURCE_DEST_DIR}"
        COMMENT "Copying resource directory to ${RESOURCE_DEST_DIR}"
)
