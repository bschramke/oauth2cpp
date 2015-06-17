/**
 * @file HttpResponse.hpp
 * @since 0.1
 *
 * Copyright 2015 oauth2cpp Contributors. All rights reserved.
 * See CONTRIBUTORS file for full list.
 *
 * SPDX-License-Identifier: BSL-1.0
 *
 */
#ifndef OAUTH2CPP_HTTPRESPONSE_HPP
#define OAUTH2CPP_HTTPRESPONSE_HPP

#include "oauth2cpp/OAuth2.hpp"

namespace oauth2{

  /**
   * @brief The HttpResponse class
   *
   * @author Björn Schramke <schramke@fh-brandenburg.de>
   *
   * @since 0.1
   */
  class OAUTH2CPP_API HttpResponse
  {
  public:
    virtual const char* readAll() const = 0;
  };

} // namespace oauth2

#endif // OAUTH2CPP_HTTPRESPONSE_HPP
