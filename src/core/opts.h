
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _SDL_LOCK_CORE_OPTS_H_
#define _SDL_LOCK_CORE_OPTS_H_

#include <core/conf.h>

//! @brief Parse command line options
//!
//! This function will parse command line arguments and populate
//! configuration structure
//!
//! @param conf configuration structure
//! @param argc argument count
//! @param argv arguments
//!
//! @return Nothing
void sdlk_opts_parse(sdlk_config_t *conf, int argc, char **argv);

#endif // _SDL_LOCK_CORE_OPTS_H_
