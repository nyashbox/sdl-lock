
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _SDL_LOCK_CORE_UTILS_H_
#define _SDL_LOCK_CORE_UTILS_H_

#include <stddef.h>

//! @brief clear password memory
//!
//! This function wipes (overwrites) memory to mitigate different
//! security concerns.
//!
//! @param password password buffer (pointer)
//! @param sz password buffer size
//!
//! @return Nothing
__attribute__((used)) void sdlk_password_clear(char *password, const size_t sz);

#endif // _SDL_LOCK_CORE_UTILS_H_
