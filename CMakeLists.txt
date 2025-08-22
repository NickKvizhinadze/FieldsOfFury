cmake_minimum_required(VERSION 3.16)
project(FieldsOfFury)

set(CMAKE_CXX_STANDARD 17)

# Path to raylib
set(RAYLIB_PATH "C:/Dev/raylib")  # <-- Change this

# Include raylib source (header + static lib)
include_directories(${RAYLIB_PATH}/raylib/src)  # Include raymath.h from source
link_directories(${RAYLIB_PATH}/w64devkit/x86_64-w64-mingw32/lib)

# Add executable
file(GLOB SOURCES "*.cpp" "*.h")
add_executable(FieldsOfFury ${SOURCES}
        Character.cpp
        Prop.h
        Prop.cpp
        Enemy.h
        Enemy.cpp
        BaseCharacter.cpp
        BaseCharacter.h)

# Link libraries
target_link_libraries(FieldsOfFury raylib opengl32 gdi32 winmm)

# Copy assets to build directory
add_custom_command(TARGET FieldsOfFury POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/assets
)
