
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include "gfx/init.h"

#include "core/log.h"
#include "core/opts.h"

static void sdlk_signal_handle_quit(int sig);

static sdlk_status_t sdlk_signal_init();

int main(int argc, char **argv) {
  // initializations
  sdlk_signal_init();
  sdlk_gfx_init(NULL);

  // add default stderr file sink for logging
  sdlk_logger_add_stderr_sink(&SDLK_DEFAULT_LOGGER);

  sdlk_opts_parse(&SDLK_DEFAULT_CONFIG, argc, argv);

  raise(SIGQUIT);
}

static void sdlk_signal_handle_quit(int sig) {
  SDLK_LOGGER_DEBUG("(Core) Gracefully shutting down sdl-lock daemon...\n");

  // resources clean up
  sdlk_logger_free(&SDLK_DEFAULT_LOGGER);
  sdlk_gfx_free(NULL);

  exit(EXIT_SUCCESS);
}

static sdlk_status_t sdlk_signal_init() {
  SDLK_LOGGER_DEBUG("(Core) Initializing signal handlers...\n");

  // quit action
  struct sigaction quit_action = {.sa_handler = sdlk_signal_handle_quit,
                                  .sa_flags = SA_RESTART,
                                  .sa_mask = 0};

  if (sigaction(SIGQUIT, &quit_action, NULL) < 0) {
    SDLK_LOGGER_FATAL(
        "(Core) Failed to register signal handler for 'quit' action: %s\n",
        strerror(errno));

    return SDLK_STATUS_FAILURE;
  }

  return SDLK_STATUS_SUCCESS;
}
