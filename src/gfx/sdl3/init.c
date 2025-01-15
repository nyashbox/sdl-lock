
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

#include <malloc.h>
#include <stddef.h>

#include <SDL3/SDL.h>

#include "gfx/init.h"
#include "gfx/window.h"

#include "core/log.h"
#include "core/status.h"

typedef struct sdlk_gfx_t {
  sdlk_window_t *window;
} sdlk_gfx_t;

sdlk_status_t sdlk_gfx_init(sdlk_gfx_t **gfx) {
  SDLK_LOGGER_DEBUG("(Graphics/SDL3) Performing graphics initialization...\n");

  sdlk_gfx_t *graphics;
  sdlk_status_t res;

  if (!(graphics = malloc(sizeof(struct sdlk_gfx_t)))) {
    SDLK_LOGGER_FATAL(
        "(Graphics/SDL3) Failed to allocate memory for graphics object.\n");

    return SDLK_STATUS_ERROR;
  }

  // perform SDL3 subsystem initialization
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDLK_LOGGER_FATAL("(Graphics/SDL3) Failed to initialize SDL3 library\n");

    return SDLK_STATUS_ERROR;
  }

  // create default window
  res = sdlk_window_create(&graphics->window, "sdl-lock", 1920, 1080);
  if (res != SDLK_STATUS_SUCCESS) {
    return res;
  }

  (*gfx) = graphics;

  SDLK_LOGGER_DEBUG("(Graphics/SDL3) Graphics initialization done.\n");
  return SDLK_STATUS_SUCCESS;
}

sdlk_window_t *sdlk_gfx_get_window(sdlk_gfx_t *gfx) { return gfx->window; }

void sdlk_gfx_free(sdlk_gfx_t *gfx) {
  sdlk_window_free(gfx->window);

  // clean up all SDL subsystems
  SDL_Quit();
}
