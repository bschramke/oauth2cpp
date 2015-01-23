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
#include "oauth2cpp/ClientConfiguration.hpp"

namespace oauth2 {

  ClientConfiguration::ClientConfiguration(const std::string& clientId, const std::string& clientSecret)
  {
    this->clientId = clientId;
    this->clientSecret = clientSecret;
  }

  ClientConfiguration::~ClientConfiguration()
  {
  }

  std::string ClientConfiguration::getClientId() const
  {
    return clientId;
  }

  void ClientConfiguration::setClientId(const std::string &value)
  {
    clientId = value;
  }
  std::string ClientConfiguration::getClientSecret() const
  {
    return clientSecret;
  }

  void ClientConfiguration::setClientSecret(const std::string &value)
  {
    clientSecret = value;
  }
  std::string ClientConfiguration::getAuthorizationEndpoint() const
  {
    return authorizationEndpoint;
  }

  void ClientConfiguration::setAuthorizationEndpoint(const std::string &value)
  {
    authorizationEndpoint = value;
  }
  std::string ClientConfiguration::getTokenEndpoint() const
  {
    return tokenEndpoint;
  }

  void ClientConfiguration::setTokenEndpoint(const std::string &value)
  {
    tokenEndpoint = value;
  }
  std::string ClientConfiguration::getRedirectUri() const
  {
    return redirectUri;
  }

  void ClientConfiguration::setRedirectUri(const std::string &value)
  {
    redirectUri = value;
  }

} // namespace oauth2
