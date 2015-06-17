/**
 * @file BearerToken.hpp
 * @since 0.1
 *
 * Copyright 2015 oauth2cpp Contributors. All rights reserved.
 * See CONTRIBUTORS file for full list.
 *
 * SPDX-License-Identifier: BSL-1.0
 *
 */
#ifndef OAUTH2CPP_BEARERTOKEN_HPP
#define OAUTH2CPP_BEARERTOKEN_HPP

#include "oauth2cpp/OAuth2.hpp"
#include "oauth2cpp/TokenInfo.hpp"

#include <string>

namespace oauth2{
  
  /**
   * @brief The BearerToken class
   *
   * @author Björn Schramke <schramke@fh-brandenburg.de>
   *
   * @since 0.1
   */
  class OAUTH2CPP_API BearerToken : public TokenInfo
  {
  public:
    BearerToken();
    ~BearerToken();

    // TokenInfo interface
    std::string getAccessToken() const override;
    std::string getRefreshToken() const override;
    std::string getType() const override;
    uint32_t expiresIn() const override;
    void setAccessToken(const std::string &value) override;
    void setRefreshToken(const std::string &value) override;
    void setType(const std::string &value) override {}
    void expiresIn(uint32_t value) override;
    bool hasAccessToken() override;
    bool hasRefreshToken() override;

  private:
    std::string accessToken;
    std::string refreshToken;
    uint32_t expireValue;
  };

}//namespace oauth2

#endif // OAUTH2CPP_BEARERTOKEN_HPP
