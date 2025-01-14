
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2025 nyashbox and Contributors

#include <security/pam_appl.h>
#include <security/pam_misc.h>

#include <auth/pam/password.h>
#include <core/log.h>

static int password_conv(int num_msg, const struct pam_message **msg,
                         struct pam_response **resp, void *appdata_ptr) {
  const char *password = (const char *)appdata_ptr;

  // check data correctness
  if (num_msg <= 0 || !msg || !password)
    return PAM_CONV_ERR;

  // allocate memory for an array of responses
  if ((*resp = calloc(num_msg, sizeof(struct pam_response))) == NULL) {
    SDLK_LOGGER_FATAL(
        "Error while allocating memory for an array of PAM responses!\n");
    return PAM_CONV_ERR;
  }

  for (int c = 0; c < num_msg; c++) {
    switch (msg[c]->msg_style) {
    case PAM_PROMPT_ECHO_OFF:
      // fallthrough
    case PAM_PROMPT_ECHO_ON: {
      if ((resp[c]->resp = strdup(password)) == NULL) {
        SDLK_LOGGER_FATAL(
            "Failed to copy password to the PAM response message!");

        return PAM_CONV_ERR;
      }

      resp[c]->resp_retcode = 0;
    } break;

    // ignore all other types of messages
    case PAM_ERROR_MSG:
      // fallthrough
    case PAM_TEXT_INFO:
      resp[c]->resp = NULL;
      break;
    default:
      free(*resp);
      return PAM_CONV_ERR;
    }
  }

  return PAM_SUCCESS;
};

sdlk_status_t sdlk_auth_pam_password(const char *password) {
  const char *username = getlogin();
  int res;

  struct pam_conv conv = {password_conv, (void *)password};
  pam_handle_t *pam_handle = NULL;

  // start PAM transaction
  if ((res = pam_start("login", username, &conv, &pam_handle)) != PAM_SUCCESS) {
    SDLK_LOGGER_ERROR("Error while initializing PAM: %s\n",
                      pam_strerror(pam_handle, res));
    return SDLK_STATUS_AUTH_FAILURE;
  }

  // perform authentication
  if ((res = pam_authenticate(pam_handle, 0)) != PAM_SUCCESS) {
    SDLK_LOGGER_ERROR("Failed to authenticate with PAM: %s\n",
                      pam_strerror(pam_handle, res));

    pam_end(pam_handle, res);

    // return correct authentication code
    if (res == PAM_AUTH_ERR) {
      return SDLK_STATUS_AUTH_ERROR;
    } else {
      return SDLK_STATUS_AUTH_FAILURE;
    }
  }

  // refresh credentials
  if ((res = pam_setcred(pam_handle, PAM_REFRESH_CRED)) != PAM_SUCCESS) {
    SDLK_LOGGER_FATAL("Error while refreshing PAM credentials: %s\n",
                      pam_strerror(pam_handle, res));
    return SDLK_STATUS_AUTH_FAILURE;
  }

  // end PAM transaction
  if ((res = pam_end(pam_handle, PAM_SUCCESS)) != PAM_SUCCESS) {
    SDLK_LOGGER_FATAL("Error while terminating PAM transaction: %s\n",
                      pam_strerror(pam_handle, res));

    return SDLK_STATUS_AUTH_FAILURE;
  }

  return SDLK_STATUS_SUCCESS;
}
