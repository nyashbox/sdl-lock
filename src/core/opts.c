
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

#include "core/status.h"
#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <core/log.h>
#include <core/opts.h>

#include <config.h>

// long options
static struct option LONGOPTS[] = {{"version", no_argument, NULL, 'v'},
                                   {"help", no_argument, NULL, 'h'},
                                   {"log-level", required_argument, NULL, 'L'},
                                   {"background", required_argument, NULL, 'b'},
                                   {NULL, no_argument, NULL, 0}};

// help message
static const char HELP_MSG[] =
    "Usage: sdl-lock [OPTION...]\n\n"
    "Options:\n"
    "\t-b, --background IMAGE Set background image.\n"
    "\n"
    "\t-L, --log-level LEVEL Logging level (default: warn)\n"
    "                        Available levels are: \n"
    "                             debug, info, warn, error, fatal\n"
    "\n"
    "\t-h, --help    Display this help message and exit.\n"
    "\t-v, --version Display version and exit.\n";

void sdlk_opts_parse(sdlk_config_t *conf, int argc, char **argv) {
  const char *shortopts = "vhb:L:";

  int o;
  int longindex = 0;
  while ((o = getopt_long(argc, argv, shortopts, LONGOPTS, &longindex)) != -1) {
    switch (o) {
    case 'v': {
      printf("sdl-lock version %s\n", SDL_LOCK_VERSION);

      exit(EXIT_SUCCESS);
    }
    case 'b': {
      conf->background_img = optarg;

      break;
    }
    case 'L': {
      const char *level = optarg;

      sdlk_status_t res;

      sdlk_logger_level_t lvl = sdlk_logger_level_from_str(level, &res);
      if (res != SDLK_STATUS_SUCCESS) {
        SDLK_LOGGER_FATAL(
            "(Core/Opts) Invalid logger level: %s\n\n"
            "Available levels are: debug, info, warn, error, fatal\n",
            level);

        exit(EXIT_FAILURE);
      }

      // set default logger level
      sdlk_logger_set_level(&SDLK_DEFAULT_LOGGER, lvl);
      SDLK_LOGGER_DEBUG("(Core/Opts) Setting log level to %s!\n", level);

      break;
    }
    case 'h':
      /* fallthrough */
    default: {
      printf(HELP_MSG);
      exit(EXIT_SUCCESS);
    }
    }
  }
  return;
}
