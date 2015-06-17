/**
 * @file HttpClient.hpp
 * @since 0.1
 *
 * Copyright 2015 oauth2cpp Contributors. All rights reserved.
 * See CONTRIBUTORS file for full list.
 *
 * SPDX-License-Identifier: BSL-1.0
 *
 */
#ifndef OAUTH2CPP_HTTPCLIENT_HPP
#define OAUTH2CPP_HTTPCLIENT_HPP

#include "oauth2cpp/OAuth2.hpp"
#include "oauth2cpp/HttpRequest.hpp"

#include <string>

namespace network{
  class uri;
}

namespace oauth2{

  class Client;

  /**
   * @brief The HttpClient class
   *
   * @author Björn Schramke <schramke@fh-brandenburg.de>
   *
   * @since 0.1
   */
  class OAUTH2CPP_API HttpClient
  {
  public:
    virtual HttpRequest* createRequest() const = 0;
    virtual void get(HttpRequest* request) = 0;
    virtual void post(HttpRequest* request, const std::string& data) = 0;

  };

} // namespace oauth2

#endif // OAUTH2CPP_HTTPCLIENT_HPP
