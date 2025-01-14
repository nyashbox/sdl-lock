
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

#include <string.h>

#include <core/utils.h>

void sdlk_password_clear(char *password, const size_t sz) {
  // add memory barrier to ensure that memset will be completed
  asm volatile("" ::: "memory");

  memset(password, '\0', sz);

  asm volatile("" ::: "memory");
}
