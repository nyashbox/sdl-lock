
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _SDL_LOCK_CORE_STATUS_H_
#define _SDL_LOCK_CORE_STATUS_H_

//! @brief status codes
typedef enum {
  // common (core) status codes
  SDLK_STATUS_SUCCESS, //!< success
  SDLK_STATUS_FAILURE, //!< common failure
  SDLK_STATUS_ERROR,   //!< common error

  // authentication status codes
  SDLK_STATUS_AUTH_FAILURE, //!< authentication failed
  SDLK_STATUS_AUTH_ERROR,   //!< error while authenticating
  SDLK_STATUS_AUTH_METHOD,  //!< unknown authentication method

  // config status codes
  SDLK_STATUS_CONFIG_FAILURE, //!< configuration failure
  SDLK_STATUS_CONFIG_ERROR,   //!< configuration error

  // opts status codes
  SDLK_STATUS_OPTS_FAILURE, //!< options failure
  SDLK_STATUS_OPTS_ERROR,   //!< options error

  // audio status codes
  SDLK_STATUS_AUDIO_FAILURE, //!< audio failure
  SDLK_STATUS_AUDIO_ERROR,   //!< audio error
} sdlk_status_t;

//! @brief convert status code into error message
//!
//! @param status status code
//!
//! @return error message
inline const char *sdlk_strerror(sdlk_status_t status) {
  switch (status) {
    // common (core) status codes
  case SDLK_STATUS_SUCCESS:
    return "Operation successful";
  case SDLK_STATUS_FAILURE:
    return "Operation failed";
  case SDLK_STATUS_ERROR:
    return "Operation error";
    // authentication status codes
  case SDLK_STATUS_AUTH_ERROR:
    return "Authentication error";
  case SDLK_STATUS_AUTH_FAILURE:
    return "Authentication failure";
  case SDLK_STATUS_AUTH_METHOD:
    return "Unknown authentication method";
    // config status codes
  case SDLK_STATUS_CONFIG_ERROR:
    return "Configuration error";
  case SDLK_STATUS_CONFIG_FAILURE:
    return "Configuration failure";
    // opts status codes
  case SDLK_STATUS_OPTS_ERROR:
    return "Configuration error";
  case SDLK_STATUS_OPTS_FAILURE:
    return "Configuration failure";
    // audio status codes
  case SDLK_STATUS_AUDIO_FAILURE:
    return "Audio failure";
  case SDLK_STATUS_AUDIO_ERROR:
    return "Audio error";
    // handle incorrect input
  default:
    return "Unknown error code!";
  }
}

#endif // _SDL_LOCK_CORE_STATUS_H_
