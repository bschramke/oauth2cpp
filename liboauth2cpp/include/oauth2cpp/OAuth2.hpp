/**
 * @brief Basic definitions for liboauth2cpp.
 * @file OAuth2.hpp
 * @author Björn Schramke <schramke@fh-brandenburg.de>
 * @since 0.1
 *
 * Copyright 2015 oauth2cpp Contributors. All rights reserved.
 * See CONTRIBUTORS file for full list.
 *
 * SPDX-License-Identifier: BSL-1.0
 *
 */
#ifndef OAUTH2CPP_OAUTH2_HPP
#define OAUTH2CPP_OAUTH2_HPP

#if (defined(_WIN32) || defined(_WIN32_WCE))
  #if defined(OAUTH2CPP_LIBRARY)
    #define OAUTH2CPP_API __declspec(dllexport)
  #else
    #define OAUTH2CPP_API __declspec(dllimport)
  #endif
#else
  #define OAUTH2CPP_API
#endif

#endif // OAUTH2CPP_OAUTH2_HPP
