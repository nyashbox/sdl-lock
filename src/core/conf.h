
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _SDL_LOCK_CORE_CONF_H_
#define _SDL_LOCK_CORE_CONF_H_

#include <stdbool.h>

#include <core/log.h>
#include <core/status.h>

//! @brief config structure
typedef struct {
  char *background_img; //!< locker background image
} sdlk_config_t;

extern sdlk_config_t SDLK_DEFAULT_CONFIG;

#endif // _SDL_LOCK_CORE_CONF_H_
