
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

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
                                   {NULL, no_argument, NULL, 0}};

// help message
static const char HELP_MSG[] =
    "Usage: sdl-lock [OPTION...]\n\n"
    "Options:\n"
    "\t-h, --help    Display this help message and exit.\n"
    "\t-v, --version Display version and exit.\n";

void sdlk_opts_parse(sdlk_config_t *conf, int argc, char **argv) {
  const char *shortopts = "vh";

  int o;
  int longindex = 0;
  while ((o = getopt_long(argc, argv, shortopts, LONGOPTS, &longindex)) != -1) {
    switch (o) {
    case 'v': {
      printf("sdl-lock version %s\n", SDL_LOCK_VERSION);

      exit(EXIT_SUCCESS);
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
