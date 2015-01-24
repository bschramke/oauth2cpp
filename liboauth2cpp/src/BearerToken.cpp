/**
 * @file BearerToken.cpp
 * @author Björn Schramke <schramke@fh-brandenburg.de>
 * @since 0.0.1
 *
 * Copyright 2015 oauth2cpp Contributors. All rights reserved.
 * See CONTRIBUTORS file for full list.
 *
 * SPDX-License-Identifier: BSL-1.0
 *
 */
#include "oauth2cpp/BearerToken.hpp"

namespace oauth2 {

  BearerToken::BearerToken()
  {
  }

  BearerToken::~BearerToken()
  {

  }

  std::string BearerToken::getAccessToken() const
  {
    return this->accessToken;
  }

  std::string BearerToken::getRefreshToken() const
  {
    return this->refreshToken;
  }

  std::string BearerToken::getType() const
  {
    return "Bearer";
  }

  uint32_t BearerToken::expiresIn() const
  {
    return this->expireValue;
  }

  void BearerToken::setAccessToken(const std::string &value)
  {
    this->accessToken = value;
  }

  void BearerToken::setRefreshToken(const std::string &value)
  {
    this->refreshToken = value;
  }

  void BearerToken::expiresIn(uint32_t value)
  {
    this->expireValue = value;
  }

  bool BearerToken::hasAccessToken()
  {
    return !this->accessToken.empty();
  }

  bool BearerToken::hasRefreshToken()
  {
    return !this->refreshToken.empty();
  }
} // namespace oauth2
