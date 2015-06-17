/**
 * @file ClientConfiguration.hpp
 * @since 0.1
 *
 * Copyright 2015 oauth2cpp Contributors. All rights reserved.
 * See CONTRIBUTORS file for full list.
 *
 * SPDX-License-Identifier: BSL-1.0
 *
 */
#ifndef OAUTH2CPP_CLIENTCONFIGURATION_HPP
#define OAUTH2CPP_CLIENTCONFIGURATION_HPP

#include "oauth2cpp/OAuth2.hpp"

#include <string>

namespace oauth2{
  
  /**
   * @brief The ClientConfiguration class
   *
   * @author Björn Schramke <schramke@fh-brandenburg.de>
   *
   * @since 0.1
   */
  class OAUTH2CPP_API ClientConfiguration
  {
  public:
    ClientConfiguration(const std::string& clientId, const std::string& clientSecret);
    ~ClientConfiguration();

    std::string getClientId() const;
    void setClientId(const std::string &value);

    std::string getClientSecret() const;
    void setClientSecret(const std::string &value);

    std::string getAuthorizationEndpoint() const;
    void setAuthorizationEndpoint(const std::string &value);

    std::string getTokenEndpoint() const;
    void setTokenEndpoint(const std::string &value);

    std::string getRedirectUri() const;
    void setRedirectUri(const std::string &value);

  private:
    std::string clientId;
    std::string clientSecret;
    std::string authorizationEndpoint;
    std::string tokenEndpoint;
    std::string redirectUri;
  };

}//namespace oauth2

#endif // OAUTH2CPP_CLIENTCONFIGURATION_HPP
