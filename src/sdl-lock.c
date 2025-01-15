
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

#include <stdlib.h>

#include "core/log.h"

int main(int argc, char **argv) {
  // add default stderr file sink for logging
  sdlk_logger_add_stderr_sink(&SDLK_DEFAULT_LOGGER);

  // close all opened log files
  sdlk_logger_close_file_sinks(&SDLK_DEFAULT_LOGGER);

  return EXIT_SUCCESS;
}
