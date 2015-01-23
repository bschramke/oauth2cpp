/**
 * @brief
 * @file Client.hpp
 * @author Björn Schramke <schramke@fh-brandenburg.de>
 * @since 0.0.1
 *
 * Copyright 2015 oauth2cpp Contributors. All rights reserved.
 * See CONTRIBUTORS file for full list.
 *
 * SPDX-License-Identifier: BSL-1.0
 *
 */
#ifndef OAUTH2CPP_CLIENT_HPP
#define OAUTH2CPP_CLIENT_HPP

#include "oauth2cpp/OAuth2.hpp"
#include "oauth2cpp/ClientConfiguration.hpp"
#include "oauth2cpp/HttpRequest.hpp"
#include "oauth2cpp/HttpResponse.hpp"

namespace network{
  class uri;
}

namespace oauth2{
  class OAUTH2CPP_API Client
  {
  public:
    explicit Client(const ClientConfiguration* configuration);
    ~Client();

    const network::uri getAuthorizationRequestUri()const;
    void createAccessTokenRequest(const std::string code, HttpRequest &request, std::string &data) const;
    void handleAccessTokenResponse(const HttpResponse &response) const;

    bool authorize(HttpRequest &request) const;

  private:
    const ClientConfiguration* configuration = nullptr;
  };

} // namespace oauth2

#endif // OAUTH2CPP_CLIENT_HPP
