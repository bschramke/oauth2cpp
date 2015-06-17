/**
 * @file Client.hpp
 * @since 0.1
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
#include "oauth2cpp/TokenStorage.hpp"

#include <set>

namespace network{
  class uri;
}

namespace oauth2{

  /**
   * @brief Simple OAuth2 client
   *
   * @author Björn Schramke <schramke@fh-brandenburg.de>
   *
   * @since 0.1
   */
  class OAUTH2CPP_API Client
  {
  public:
    /**
     * Creates a OAuth2-Client with the specified configuration.
     *
     * @param configuration
     */
    explicit Client(const ClientConfiguration* configuration);
    ~Client();

    /**
     * @param scopeSet
     * @return
     */
    const network::uri getAuthorizationRequestUri(const std::set<std::string>& scopeSet)const;

    /**
     * @param scope
     * @return
     */
    const network::uri getAuthorizationRequestUri(const std::string& scope)const;

    /**
     * @param code
     * @param request
     * @param data
     */
    void createAccessTokenRequest(const std::string &code, HttpRequest &request, std::string &data) const;

    /**
     * @param response
     */
    void handleAccessTokenResponse(const HttpResponse &response) const;

    /**
     * @param request
     * @param data
     * @return
     */
    bool createRefreshTokenRequest(HttpRequest &request, std::string &data) const;

    /**
     * @param response
     */
    void handleRefreshTokenResponse(const HttpResponse &response) const;

    /**
     * @param request
     * @return
     */
    bool authorize(HttpRequest &request) const;

    /**
     * @return true if there is an Access Token available in the linked TokenStorage
     */
    bool authorized() const;

    /**
     * Sets the storage object to use for storing the OAuth tokens.
     *
     * @param storage
     */
    void setTokenStorage(TokenStorage* storage);

    /**
     * @return the storage object which is used by this client
     */
    TokenStorage *getTokenStorage() const;

  private:
    const ClientConfiguration* configuration = nullptr;
    TokenStorage* tokenStorage = nullptr;
  };

} // namespace oauth2

#endif // OAUTH2CPP_CLIENT_HPP
