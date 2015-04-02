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
#include "oauth2cpp/TokenFactory.hpp"

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

  const network::uri Client::getAuthorizationRequestUri(const std::set<std::string> &scopeSet) const
  {
    std::string scopeValue;
    for(auto scope:scopeSet)
      {
        if(!scopeValue.empty()) scopeValue += ' ';
        scopeValue += scope;
      }

    return getAuthorizationRequestUri(scopeValue);
  }

  const network::uri Client::getAuthorizationRequestUri(const std::string& scope) const
  {
    network::uri requestUri(configuration->getAuthorizationEndpoint());
    network::uri_builder uriBuilder(requestUri);

    uriBuilder.query("scope",scope)
        .query("redirect_uri",configuration->getRedirectUri())
        .query("response_type","code")
        .query("client_id",configuration->getClientId());

    return uriBuilder.uri();

  }

  void Client::createAccessTokenRequest(const std::string& code, HttpRequest& request, std::string& data) const
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
    TokenInfo* tokenInfo = TokenFactory::fromJson(response.readAll());
    this->tokenStorage->writeTokenInfo(configuration->getClientId(),std::unique_ptr<TokenInfo>(tokenInfo));
  }

  bool Client::createRefreshTokenRequest(HttpRequest& request, std::string& data) const
  {
    auto clientId = configuration->getClientId();
    if(tokenStorage->hasRefreshToken(clientId))
      {
        network::uri requestUri(configuration->getTokenEndpoint());
        request.setUri(requestUri);
        request.setHeader("Content-Type","application/x-www-form-urlencoded");

        data.assign("client_id=");
        data.append(clientId)
            .append("&client_secret=").append(configuration->getClientSecret())
            .append("&refresh_token=").append(tokenStorage->getRefreshToken(clientId))
            .append("&grant_type=refresh_token");

        return true;
      }

    return false;

  }

  void Client::handleRefreshTokenResponse(const HttpResponse &response) const
  {
    std::unique_ptr<TokenInfo> const& tokenInfo = this->tokenStorage->getTokenInfo(configuration->getClientId());
    TokenFactory::updateFromJson(tokenInfo,response.readAll());
  }

  bool Client::authorize(HttpRequest &request) const
  {
    auto clientId = configuration->getClientId();
    if(tokenStorage->hasAccessToken(clientId))
      {
        request.setHeader("Authorization","Bearer "+tokenStorage->getAccessToken(clientId));
        return true;
      }

    return false;
  }

  void Client::setTokenStorage(TokenStorage *storage)
  {
    this->tokenStorage = storage;
  }

  TokenStorage *Client::getTokenStorage() const
  {
    return this->tokenStorage;
  }

} // namespace oauth2
