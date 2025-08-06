cmake_minimum_required(VERSION 3.31)
project(pong)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS OFF)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.2
)
FetchContent_MakeAvailable(SFML)

add_executable(pong src/main.cpp
        src/Game.cpp
        src/Game.h
        src/Ball.cpp
        src/Ball.h
        src/Paddle.cpp
        src/Paddle.h
        src/Window.cpp
        src/Window.h
        src/Settings.h
        src/Sound.cpp
        src/Sound.h
)

add_custom_command(TARGET pong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${sfml_SOURCE_DIR}/extlibs/bin/x64/openal32.dll"
        $<TARGET_FILE_DIR:pong>
)

target_link_libraries(pong PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
