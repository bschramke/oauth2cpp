/**
 * @file Client.cpp
 * @author Björn Schramke <schramke@fh-brandenburg.de>
 * @since 0.0.1
 *
 * Copyright 2015 oauth2cpp Contributors. All rights reserved.
 * See CONTRIBUTORS file for full list.
 *
 * SPDX-License-Identifier: BSL-1.0
 *
 */
#include "oauth2cpp/Client.hpp"
#include "oauth2cpp/HttpClient.hpp"
#include "oauth2cpp/HttpRequest.hpp"

#include <memory>
#include <network/uri.hpp>
#include <network/uri/uri_builder.hpp>
#include <network/uri/detail/encode.hpp>

namespace oauth2 {

  Client::Client(const ClientConfiguration* configuration)
    :configuration(configuration)
  {
  }

  Client::~Client()
  {
  }

  const network::uri Client::getAuthorizationRequestUri() const
  {
    network::uri requestUri(configuration->getAuthorizationEndpoint());
    network::uri_builder uriBuilder(requestUri);

    uriBuilder.query("scope","https://www.googleapis.com/auth/plus.me")
        .query("redirect_uri",configuration->getRedirectUri())
        .query("response_type","code")
        .query("client_id",configuration->getClientId());

    return uriBuilder.uri();

  }

  void Client::createAccessTokenRequest(const std::string code, HttpRequest& request, std::string& data) const
  {
    network::uri requestUri(configuration->getTokenEndpoint());
    request.setUri(requestUri);
    request.setHeader("Content-Type","application/x-www-form-urlencoded");

    data.assign("code=");
    data.append(code).append("&client_id=").append(configuration->getClientId())
        .append("&client_secret=").append(configuration->getClientSecret())
        .append("&redirect_uri=").append(configuration->getRedirectUri())
        .append("&grant_type=authorization_code");

  }

  void Client::handleAccessTokenResponse(const HttpResponse &response) const
  {
  }

} // namespace oauth2
