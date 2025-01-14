
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _SDL_LOCK_AUTH_PAM_PASSWORD_H_
#define _SDL_LOCK_AUTH_PAM_PASSWORD_H_

#include <core/status.h>

//! @brief Perform password authentication using PAM
//!
//! @param password password string
//!
//! @return Status Code
sdlk_status_t sdlk_auth_pam_password(const char *password);

#endif // _SDL_LOCK_AUTH_PAM_PASSWORD_H_
