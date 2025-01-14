
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _SDL_LOCK_AUTH_H_
#define _SDL_LOCK_AUTH_H_

#include <core/status.h>

//! @brief Authentication type
typedef enum {
  SDLK_AUTH_PASSWORD //!< Perform password-based authentication
} sdlk_auth_t;

//! @brief Perform user authentication
//!
//! This function performs user authentication. One may use different
//! authentication types.
//!
//! @param auth_type Authentication type
//! @param ctx Authentication context
//!
//! @return Authentication result (code)
sdlk_status_t sdlk_auth(sdlk_auth_t auth_type, void *ctx);

#endif // _SDL_LOCK_AUTH_H_
