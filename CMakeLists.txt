
# SPDX-License-Identifier: Apache-2.0
# Copyright (c) 2025 nyashbox and Contributors

cmake_minimum_required(VERSION 3.25.1)

project(
    sdl-lock 
    DESCRIPTION "SDL-based screen locker for UNIX-like operating systems"
    HOMEPAGE_URL "https://github.com/nyashbox/sdl-lock"
    VERSION 0.1.0
    LANGUAGES C
)

list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

add_subdirectory(src)
