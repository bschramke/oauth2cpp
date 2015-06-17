/**
 * @file TokenInfo.hpp
 * @since 0.1
 *
 * Copyright 2015 oauth2cpp Contributors. All rights reserved.
 * See CONTRIBUTORS file for full list.
 *
 * SPDX-License-Identifier: BSL-1.0
 *
 */
#ifndef OAUTH2CPP_TOKENFACTORY_HPP
#define OAUTH2CPP_TOKENFACTORY_HPP

#include "oauth2cpp/OAuth2.hpp"
#include "oauth2cpp/TokenInfo.hpp"

#include <string>
#include <memory>

namespace oauth2{
  /**
   * @brief The TokenFactory class
   *
   * @author Björn Schramke <schramke@fh-brandenburg.de>
   *
   * @since 0.1
   */
  class OAUTH2CPP_API TokenFactory
  {
  public:
    static TokenInfo* fromJson(const std::string jsonStr);
    static void updateFromJson(std::unique_ptr<TokenInfo> const& tokenInfo, const std::string jsonStr);
  };

}//namespace oauth2

#endif // OAUTH2CPP_TOKENFACTORY_HPP
