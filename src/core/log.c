
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

#include "core/status.h"
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <core/log.h>

//! insert new sink
static int _sdlk_logger_insert_sink(sdlk_logger_t *logger, FILE *sink);

struct sdlk_logger_t {
  sdlk_logger_level_t level;
  FILE *sinks[SDLK_LOGGER_MAX_SINKS];
  size_t sinks_count;
};

struct sdlk_logger_t SDLK_DEFAULT_LOGGER = {
    .level = LOG_WARN, // log warning messages
    .sinks = {NULL},   // no sinks by default
    .sinks_count = 0};

sdlk_logger_level_t sdlk_logger_get_level(sdlk_logger_t *logger) {
  return logger->level;
}

sdlk_logger_level_t sdlk_logger_level_from_str(const char *level,
                                               sdlk_status_t *res) {
  // status should be "success" by default
  *res = SDLK_STATUS_SUCCESS;

  if (!strcmp(level, "debug"))
    return LOG_DEBUG;
  else if (!strcmp(level, "info"))
    return LOG_INFO;
  else if (!strcmp(level, "warn"))
    return LOG_WARN;
  else if (!strcmp(level, "error"))
    return LOG_ERROR;
  else if (!strcmp(level, "fatal"))
    return LOG_FATAL;

  // set error status code
  *res = SDLK_STATUS_ERROR;
  return LOG_WARN;
}

void sdlk_logger_set_level(sdlk_logger_t *logger, sdlk_logger_level_t level) {
  logger->level = level;
}

sdlk_status_t sdlk_logger_add_file_sink(sdlk_logger_t *logger,
                                        const char *path) {
  FILE *file = NULL;
  int index = logger->sinks_count;

  if (!(file = fopen(path, "a"))) {
    fprintf(stderr, "failed to open log file: %s", strerror(errno));

    return SDLK_STATUS_ERROR;
  }

  // insert new sink
  return _sdlk_logger_insert_sink(logger, file);
}

sdlk_status_t sdlk_logger_add_stdout_sink(sdlk_logger_t *logger) {
  return _sdlk_logger_insert_sink(logger, stdout);
}

sdlk_status_t sdlk_logger_add_stderr_sink(sdlk_logger_t *logger) {
  return _sdlk_logger_insert_sink(logger, stderr);
}

void sdlk_logger_log(sdlk_logger_t *logger, sdlk_logger_level_t level,
                     const char *fmt, ...) {
  if (level >= logger->level) {
    va_list args;
    va_start(args, fmt);

    // write logging message to all sinks
    for (int i = 0; i < logger->sinks_count; i++) {
      FILE *sink = logger->sinks[i];

      // don't write to NULLed sinks
      if (sink)
        vfprintf(sink, fmt, args);
    }

    va_end(args);
  }
}

sdlk_status_t sdlk_logger_close_file_sinks(sdlk_logger_t *logger) {
  for (int i = 0; i < logger->sinks_count; i++) {
    FILE *sink = logger->sinks[i];

    // don't close stderr, stdout and NULL sinks
    if (sink != stderr && sink != stdout && sink != NULL) {
      fclose(sink);
      sink = NULL;
    }
  }

  return SDLK_STATUS_SUCCESS;
}

static int _sdlk_logger_insert_sink(sdlk_logger_t *logger, FILE *sink) {
  int index = logger->sinks_count;

  // check if still have space for new sinks
  if (index < SDLK_LOGGER_MAX_SINKS)
    logger->sinks[logger->sinks_count++] = sink;
  else
    return SDLK_STATUS_FAILURE;

  return SDLK_STATUS_SUCCESS;
}
