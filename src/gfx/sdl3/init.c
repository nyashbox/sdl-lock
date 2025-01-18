
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

#include <malloc.h>
#include <stddef.h>

#include <SDL3/SDL.h>

#include "gfx/init.h"

#include "core/log.h"
#include "core/status.h"

sdlk_status_t sdlk_gfx_init(void *ctx) {
  SDLK_LOGGER_DEBUG("(Graphics/SDL3) Performing graphics initialization...\n");

  sdlk_status_t res;

  // perform SDL3 subsystem initialization
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDLK_LOGGER_FATAL("(Graphics/SDL3) Failed to initialize SDL3 library\n");

    return SDLK_STATUS_ERROR;
  }

  SDLK_LOGGER_DEBUG("(Graphics/SDL3) Graphics initialization done.\n");
  return SDLK_STATUS_SUCCESS;
}

void sdlk_gfx_free(void *ctx) {
  // clean up all SDL subsystems
  SDL_Quit();
}
