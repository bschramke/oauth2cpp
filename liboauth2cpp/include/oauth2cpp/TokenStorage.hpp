/**
 * @brief
 * @file TokenStorage.hpp
 * @author Björn Schramke <schramke@fh-brandenburg.de>
 * @since 0.0.1
 *
 * Copyright 2015 oauth2cpp Contributors. All rights reserved.
 * See CONTRIBUTORS file for full list.
 *
 * SPDX-License-Identifier: BSL-1.0
 *
 */
#ifndef OAUTH2CPP_TOKENSTORAGE_HPP
#define OAUTH2CPP_TOKENSTORAGE_HPP

#include "oauth2cpp/OAuth2.hpp"
#include "oauth2cpp/TokenInfo.hpp"

#include <string>
#include <memory>

namespace oauth2{
  
  class OAUTH2CPP_API TokenStorage
  {
  public:
    virtual bool hasTokenInfo(const std::string clientId) = 0;
    virtual std::unique_ptr<TokenInfo> const& getTokenInfo(const std::string clientId) = 0;
    virtual void writeTokenInfo(const std::string clientId, std::unique_ptr<TokenInfo> tokenInfo) = 0;

    virtual bool hasAccessToken(const std::string clientId) = 0;
    virtual std::string getAccessToken(const std::string clientId) = 0;

    virtual bool hasRefreshToken(const std::string clientId) = 0;
    virtual std::string getRefreshToken(const std::string clientId) = 0;

    virtual ~TokenStorage() = default;
  };

}//namespace oauth2

#endif // OAUTH2CPP_TOKENSTORAGE_HPP
