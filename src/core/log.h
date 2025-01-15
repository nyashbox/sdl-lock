
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _SDL_LOCK_CORE_LOG_H_
#define _SDL_LOCK_CORE_LOG_H_

#include <core/status.h>

#define SDLK_LOGGER_MAX_SINKS 4

//! @brief structure representing logger object
typedef struct sdlk_logger_t sdlk_logger_t;

extern sdlk_logger_t SDLK_DEFAULT_LOGGER;

//! @brief logging levels
typedef enum {
  LOG_DEBUG, //!< 'debug' level
  LOG_INFO,  //!< 'info' level
  LOG_WARN,  //!< 'warn' level
  LOG_ERROR, //!< 'error' level
  LOG_FATAL  //!< 'fatal' level
} sdlk_logger_level_t;

//! @brief log message
//!
//! This function will write log message to the sinks specified
//! in the logger object. In common cases convenient macros should
//! be used
//!
//! @param logger logger object (pointer)
//! @param level log level
//! @param fmt log message format
//!
//! @see sdlk_logger_level_t
//!
//! @return Nothing
void sdlk_logger_log(sdlk_logger_t *logger, sdlk_logger_level_t level,
                     const char *fmt, ...);

//! @brief add file sink
//!
//! This function adds new file sink to the logger object. It will
//! correctly open log file, and close it when logger object will be destroyed.
//!
//! @param logger logger object (pointer)
//! @param path path to the log file
//!
//! @return Status Code
sdlk_status_t sdlk_logger_add_file_sink(sdlk_logger_t *logger,
                                        const char *path);

//! @brief Add stdout sink
//!
//! This function adds 'stdout' sink to the logger object.
//!
//! @param logger logger object (pointer)
//!
//! @return Status Code
sdlk_status_t sdlk_logger_add_stdout_sink(sdlk_logger_t *logger);

//! @brief Add stderr sink
//!
//! This function adds 'stderr' sink to the logger object.
//!
//! @param logger logger object (pointer)
//!
//! @return Status Code
sdlk_status_t sdlk_logger_add_stderr_sink(sdlk_logger_t *logger);

//! @brief Close all file sinks
//!
//! When called, this function closes all open file sinks.
//!
//! @param logger logger object (pointer)
//!
//! @return Status Code
sdlk_status_t sdlk_logger_close_file_sinks(sdlk_logger_t *logger);

//! @brief Set logger logging level
//!
//! When called, this function will update logging level in the specified
//! logger object
//!
//! @param logger logger object (pointer)
//! @param level logger desired level
//!
//! @return Status code
void sdlk_logger_set_level(sdlk_logger_t *logger, sdlk_logger_level_t level);

//! @brief Get logger logging level
//!
//! @param logger logger object (pointer)
//!
//! @return Current logging level
sdlk_logger_level_t sdlk_logger_get_level(sdlk_logger_t *logger);

//! @brief Get logging level from string
//!
//! @param level logging level string
//! @param res result (returned status code)
//!
//! @return Logging level
sdlk_logger_level_t sdlk_logger_level_from_str(const char *level,
                                               sdlk_status_t *res);

//! @defgroup LogMacros Logger macros
//! @brief Collection of macros for simple logging
//!
//! These macros are used for convenient writing log message
//! to the standard logger object
//!
//! @{

#define SDLK_LOGGER_DEBUG(...)                                                 \
  sdlk_logger_log(&SDLK_DEFAULT_LOGGER, LOG_DEBUG, __VA_ARGS__)
#define SDLK_LOGGER_INFO(...)                                                  \
  sdlk_logger_log(&SDLK_DEFAULT_LOGGER, LOG_INFO, __VA_ARGS__)
#define SDLK_LOGGER_WARN(...)                                                  \
  sdlk_logger_log(&SDLK_DEFAULT_LOGGER, LOG_WARN, __VA_ARGS__)
#define SDLK_LOGGER_ERROR(...)                                                 \
  sdlk_logger_log(&SDLK_DEFAULT_LOGGER, LOG_ERROR, __VA_ARGS__)
#define SDLK_LOGGER_FATAL(...)                                                 \
  sdlk_logger_log(&SDLK_DEFAULT_LOGGER, LOG_FATAL, __VA_ARGS__)

//! @}

#endif // _SDL_LOCK_CORE_LOG_H_
