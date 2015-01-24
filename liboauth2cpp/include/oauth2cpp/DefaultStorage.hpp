/**
 * @brief
 * @file DefaultStorage.hpp
 * @author Björn Schramke <schramke@fh-brandenburg.de>
 * @since 0.0.1
 *
 * Copyright 2015 oauth2cpp Contributors. All rights reserved.
 * See CONTRIBUTORS file for full list.
 *
 * SPDX-License-Identifier: BSL-1.0
 *
 */
#ifndef OAUTH2CPP_DEFAULTSTORAGE_HPP
#define OAUTH2CPP_DEFAULTSTORAGE_HPP

#include "oauth2cpp/OAuth2.hpp"
#include "oauth2cpp/TokenStorage.hpp"

#include <string>
#include <map>

namespace oauth2{
  
  class OAUTH2CPP_API DefaultStorage : public TokenStorage
  {
  public:
    DefaultStorage();
    ~DefaultStorage();

    // TokenStorage interface
    bool hasTokenInfo(const std::string clientId);
    std::unique_ptr<TokenInfo> const& getTokenInfo(const std::string clientId);
    void writeTokenInfo(const std::string clientId, std::unique_ptr<TokenInfo> tokenInfo);

    bool hasAccessToken(const std::string clientId);
    std::string getAccessToken(const std::string clientId);

    bool hasRefreshToken(const std::string clientId);
    std::string getRefreshToken(const std::string clientId);

  private:
    std::map<std::string, std::unique_ptr<TokenInfo>> tokenInfoMap;
  };

}//namespace oauth2

#endif // OAUTH2CPP_DEFAULTSTORAGE_HPP
