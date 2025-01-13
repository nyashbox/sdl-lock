
# SPDX-License-Identifier: Apache-2.0
# Copyright (c) 2025 nyashbox and Contributors

# FindPAM - find PAM library
#
# This module doesn't try to be a full-blown solution for
# finding PAM library.
#
# This module defines:
#
# ::
#
# PAM::PAM         - target name
# PAM_FOUND        - do not link against if false
# PAM_INCLUDE_DIRS - header files location
# PAM_LIBRARIES    - name of the library to link against
#
# ::

# find include directories
find_path(PAM_INCLUDE_DIR 
    NAMES 
        security/pam_appl.h 
        pam/pam_appl.h
)

# find library itself
find_library(PAM_LIBRARY 
    NAMES 
        pam
)

# handle standard arguments
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PAM
    REQUIRED_VARS 
        PAM_LIBRARY PAM_INCLUDE_DIR
)


if(PAM_FOUND)
    # set variables for consistency
    set(PAM_LIBRARIES ${PAM_LIBRARY})    
    set(PAM_INCLUDE_DIRS ${PAM_INCLUDE_DIR})

    if (NOT TARGET PAM::PAM)
        add_library(PAM::PAM INTERFACE IMPORTED)
        set_target_properties(PAM::PAM 
            PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES 
                    "${PAM_INCLUDE_DIR}"
                INTERFACE_LINK_LIBRARIES 
                    "${PAM_LIBRARY}" 
        )
    endif()
endif()
