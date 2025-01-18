
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

#include <malloc.h>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "gfx/window.h"

#include "core/log.h"
#include "core/status.h"

typedef struct sdlk_window_t {
  SDL_Window *sdl_window;   //!< SDL Window
  SDL_Renderer *sdl_render; //!< SDL Renderer
  SDL_Texture *background;  //!< Locker background
  int width;                //!< Screen width
  int height;               //!< Screen heigh
} sdlk_window_t;

sdlk_status_t sdlk_window_create(sdlk_window_t **window, const char *title,
                                 int width, int height) {
  sdlk_window_t *win = malloc(sizeof(struct sdlk_window_t));
  if (!win) {
    SDLK_LOGGER_FATAL(
        "(Graphics/SDL3) Failed to allocate memory for window structure!\n");

    window = NULL;

    return SDLK_STATUS_ERROR;
  }

  win->width = width;
  win->height = height;

  // create SDL window
  win->sdl_window = SDL_CreateWindow(
      title, width, height,
      SDL_WINDOW_FULLSCREEN             // make window fullscreen
          | SDL_WINDOW_BORDERLESS       // window should be borderless
          | SDL_WINDOW_MOUSE_GRABBED    // grab mouse input
          | SDL_WINDOW_KEYBOARD_GRABBED // grab keyboard input
          | SDL_WINDOW_INPUT_FOCUS      // make window focused
          | SDL_WINDOW_MOUSE_FOCUS      // make window mouse focus
          | SDL_WINDOW_HIDDEN           // window should be hidden by default
          | SDL_WINDOW_MOUSE_CAPTURE    // capture mouse
  );
  if (!win->sdl_window) {
    SDLK_LOGGER_FATAL("(Graphics/SDL3) Failed to create window: %s\n",
                      SDL_GetError());

    win->sdl_window = NULL;

    return SDLK_STATUS_ERROR;
  }

  // create SDL renderer
  win->sdl_render = SDL_CreateRenderer(win->sdl_window, NULL);
  if (!win->sdl_render) {
    SDLK_LOGGER_FATAL("(Graphics/SDL3) Failed to create render: %s\n",
                      SDL_GetError());

    win->sdl_render = NULL;
    return SDLK_STATUS_ERROR;
  }

  // no background by default
  win->background = NULL;

  // fill background with black color
  SDL_SetRenderDrawColor(win->sdl_render, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(win->sdl_render);
  SDL_RenderPresent(win->sdl_render);

  (*window) = win;
  return SDLK_STATUS_SUCCESS;
}

sdlk_status_t sdlk_window_update(sdlk_window_t *window) {
  SDL_Renderer *render = window->sdl_render;
  SDL_Texture *background = window->background;

  SDL_RenderClear(render);

  // render background only if present
  if (background)
    SDL_RenderTexture(render, background, NULL, NULL);

  SDL_RenderPresent(window->sdl_render);

  return SDLK_STATUS_SUCCESS;
}

sdlk_status_t sdlk_window_show(sdlk_window_t *window) {
  if (SDL_ShowWindow(window->sdl_window)) {
    sdlk_window_update(window);
    return SDLK_STATUS_SUCCESS;
  } else {
    return SDLK_STATUS_FAILURE;
  }
}

sdlk_status_t sdlk_window_hide(sdlk_window_t *window) {
  if (SDL_HideWindow(window->sdl_window))
    return SDLK_STATUS_SUCCESS;
  else
    return SDLK_STATUS_FAILURE;
}

sdlk_status_t sdlk_window_set_background(sdlk_window_t *window,
                                         const char *path) {
  // free previous image (if was loaded)
  if (window->background)
    SDL_DestroyTexture(window->background);

  window->background = IMG_LoadTexture(window->sdl_render, path);
  if (!window->background) {
    SDLK_LOGGER_FATAL("(Graphics/SDL3) Failed to load background image: %s\n",
                      SDL_GetError());

    return SDLK_STATUS_ERROR;
  }

  return SDLK_STATUS_SUCCESS;
}

void sdlk_window_free(sdlk_window_t *window) {
  SDLK_LOGGER_DEBUG("(Graphics/SDL3) Cleaning up window...\n");

  SDL_Window *win = window->sdl_window;
  SDL_Renderer *render = window->sdl_render;
  SDL_Texture *background = window->background;

  if (win)
    SDL_DestroyWindow(win);

  if (background)
    SDL_DestroyTexture(background);

  if (render)
    SDL_DestroyRenderer(render);
}
