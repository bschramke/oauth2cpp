/**
 * @brief
 * @file TokenInfo.hpp
 * @author Björn Schramke <schramke@fh-brandenburg.de>
 * @since 0.0.1
 *
 * Copyright 2015 oauth2cpp Contributors. All rights reserved.
 * See CONTRIBUTORS file for full list.
 *
 * SPDX-License-Identifier: BSL-1.0
 *
 */
#ifndef OAUTH2CPP_TOKENINFO_HPP
#define OAUTH2CPP_TOKENINFO_HPP

#include "oauth2cpp/OAuth2.hpp"

#include <string>

namespace oauth2{
  
  class OAUTH2CPP_API TokenInfo
  {
  public:
    virtual std::string getAccessToken() const = 0;
    virtual std::string getRefreshToken() const = 0;
    virtual std::string getType() const = 0;
    virtual uint32_t expiresIn() const = 0;

    virtual void setAccessToken(const std::string& value) = 0;
    virtual void setRefreshToken(const std::string& value) = 0;
    virtual void setType(const std::string& value) = 0;
    virtual void expiresIn(uint32_t value) = 0;

    virtual bool hasAccessToken() = 0;
    virtual bool hasRefreshToken() = 0;

    virtual ~TokenInfo() = default;
  };

}//namespace oauth2

#endif // OAUTH2CPP_TOKENINFO_HPP
