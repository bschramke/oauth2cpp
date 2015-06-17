/**
 * @file TokenFactory.cpp
 * @author Björn Schramke <schramke@fh-brandenburg.de>
 * @since 0.1
 *
 * Copyright 2015 oauth2cpp Contributors. All rights reserved.
 * See CONTRIBUTORS file for full list.
 *
 * SPDX-License-Identifier: BSL-1.0
 *
 */
#include "oauth2cpp/TokenFactory.hpp"
#include "oauth2cpp/BearerToken.hpp"

#include "jsonxx.h"

namespace oauth2{

  TokenInfo* TokenFactory::fromJson(const std::string jsonStr)
  {
    jsonxx::Object jsonRoot;

    assert(jsonRoot.parse(jsonStr));

    //check that json object has all needed information
    assert(jsonRoot.has<jsonxx::String>("refresh_token"));
    assert(jsonRoot.has<jsonxx::String>("access_token"));
    assert(jsonRoot.has<jsonxx::String>("token_type"));
    assert(jsonRoot.has<jsonxx::Number>("expires_in"));

    TokenInfo* tokenInfo = nullptr;
    std::string tokenType = jsonRoot.get<jsonxx::String>("token_type");
    if(tokenType == "Bearer")
      {
        tokenInfo = new BearerToken();
        tokenInfo->setAccessToken(jsonRoot.get<jsonxx::String>("access_token"));
        tokenInfo->expiresIn(jsonRoot.get<jsonxx::Number>("expires_in"));
        tokenInfo->setRefreshToken(jsonRoot.get<jsonxx::String>("refresh_token"));
      }

    return tokenInfo;

  }

  void TokenFactory::updateFromJson(const std::unique_ptr<TokenInfo> &tokenInfo, const std::string jsonStr)
  {
    if(jsonStr.empty()) return;

    jsonxx::Object jsonRoot;

    assert(jsonRoot.parse(jsonStr));

    //check that json object has all needed information
    assert(jsonRoot.has<jsonxx::String>("access_token"));
    assert(jsonRoot.has<jsonxx::String>("token_type"));
    assert(jsonRoot.has<jsonxx::Number>("expires_in"));

    std::string tokenType = jsonRoot.get<jsonxx::String>("token_type");
    assert(tokenInfo->getType() == tokenType);
    tokenInfo->setAccessToken(jsonRoot.get<jsonxx::String>("access_token"));
    tokenInfo->expiresIn(jsonRoot.get<jsonxx::Number>("expires_in"));
  }

}//namespace oauth2
