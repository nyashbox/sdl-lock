
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _SDL_LOCK_GFX_INIT_H_
#define _SDL_LOCK_GFX_INIT_H_

#include "core/status.h"

//! @brief initialize graphics subsystem
//!
//! @param ctx backend-specific context
//!
//! @return Status Code
sdlk_status_t sdlk_gfx_init(void *ctx);

//! @brief terminate graphics subsystem
//!
//! @param ctx backend-specific context
//!
//! @return Nothing
void sdlk_gfx_free(void *ctx);

#endif // _SDL_LOCK_GFX_INIT_H_
