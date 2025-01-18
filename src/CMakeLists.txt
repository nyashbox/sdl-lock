
# SPDX-License-Identifier: Apache-2.0
# Copyright (c) 2025 nyashbox and Contributors

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(PAM REQUIRED)

set(SDL_LOCK_SRCS
    core/log.c
    core/conf.c
    core/opts.c
    core/utils.c

    auth/pam/password.c
    auth/auth.c

    gfx/sdl3/window.c
    gfx/sdl3/init.c
)

configure_file("config.h.in" "config.h" ESCAPE_QUOTES)

add_library(sdl_lock_obj OBJECT ${SDL_LOCK_SRCS})
add_library(sdl-lock::sdl-lock ALIAS sdl_lock_obj)
target_include_directories(sdl_lock_obj
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)

target_link_libraries(sdl_lock_obj
    PUBLIC 
        SDL3::SDL3
        SDL3_image::SDL3_image
        PAM::PAM
)

add_executable(sdl-lock sdl-lock.c)
target_link_libraries(sdl-lock
        sdl-lock::sdl-lock
)

install(TARGETS sdl-lock DESTINATION bin)
