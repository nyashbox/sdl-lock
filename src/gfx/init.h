
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _SDL_LOCK_GFX_INIT_H_
#define _SDL_LOCK_GFX_INIT_H_

#include "gfx/window.h"

#include "core/status.h"

//! @brief graphics structure
typedef struct sdlk_gfx_t sdlk_gfx_t;

//! @brief initialize graphics subsystem
//!
//! @param gfx graphics object
//!
//! @return Status Code
sdlk_status_t sdlk_gfx_init(sdlk_gfx_t **gfx);

//! @brief get window object
//!
//! @param gfx graphics object
//!
//! @return window object (pointer)
sdlk_window_t *sdlk_gfx_get_window(sdlk_gfx_t *gfx);

//! @brief terminate graphics subsystem
//!
//! @param gfx graphics object
//!
//! @return Nothing
void sdlk_gfx_free(sdlk_gfx_t *gfx);

#endif // _SDL_LOCK_GFX_INIT_H_
