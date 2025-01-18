
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _SDL_LOCK_GFX_WINDOW_H_
#define _SDL_LOCK_GFX_WINDOW_H_

#include "core/status.h"

//! @brief window structure
typedef struct sdlk_window_t sdlk_window_t;

//! @brief create window
//!
//! @param window window object
//! @param name window name
//! @param width screen width (in pixels)
//! @param height screen height (in pixels)
//!
//! @return Status code
sdlk_status_t sdlk_window_create(sdlk_window_t **window, const char *name,
                                 int width, int height);

//! @brief update window
//!
//! @param window window object
//!
//! @return Status code
sdlk_status_t sdlk_window_update(sdlk_window_t *window);

//! @brief show window
//!
//! @param window window object (pointer)
//!
//! @return Status code
sdlk_status_t sdlk_window_show(sdlk_window_t *window);

//! @brief hide window
//!
//! @param window window object (pointer)
//!
//! @return Status code
sdlk_status_t sdlk_window_hide(sdlk_window_t *window);

//! @brief set background image of a window
sdlk_status_t sdlk_window_set_background(sdlk_window_t *window,
                                         const char *path);

//! @brief close (free) window
//!
//! @param window window object (pointer)
//!
//! @return Nothing
void sdlk_window_free(sdlk_window_t *window);

#endif // _SDL_LOCK_GFX_WINDOW_H_
