
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

#include <security/pam_appl.h>
#include <security/pam_misc.h>

#include <unistd.h>

#include <auth/auth.h>
#include <auth/pam/password.h>

sdlk_status_t sdlk_auth(sdlk_auth_t auth_type, void *ctx) {
  switch (auth_type) {
  case SDLK_AUTH_PASSWORD:
    return sdlk_auth_pam_password((const char *)ctx);
  default:
    // return 'unknown method' status
    return SDLK_STATUS_AUTH_METHOD;
  }
}
