/**
 * @file DefaultStorage.cpp
 * @author Björn Schramke <schramke@fh-brandenburg.de>
 * @since 0.1
 *
 * Copyright 2015 oauth2cpp Contributors. All rights reserved.
 * See CONTRIBUTORS file for full list.
 *
 * SPDX-License-Identifier: BSL-1.0
 *
 */
#include "oauth2cpp/DefaultStorage.hpp"

#include <stdexcept>

namespace oauth2 {

  DefaultStorage::DefaultStorage()
  {
  }

  DefaultStorage::~DefaultStorage()
  {
  }

  bool DefaultStorage::hasTokenInfo(const std::string clientId)
  {
    auto search = tokenInfoMap.find(clientId);
    return search != tokenInfoMap.end();
  }

  std::unique_ptr<TokenInfo> const& DefaultStorage::getTokenInfo(const std::string clientId)
  {
    auto search = tokenInfoMap.find(clientId);
    if (search == tokenInfoMap.end()) throw std::invalid_argument("entry not found");
    return search->second;
  }

  void DefaultStorage::writeTokenInfo(const std::string clientId, std::unique_ptr<TokenInfo> tokenInfo)
  {
    tokenInfoMap.insert(std::make_pair(clientId,std::move(tokenInfo)));
  }

  bool DefaultStorage::hasAccessToken(const std::string clientId)
  {
    bool retVal = false;
    try{
      std::unique_ptr<TokenInfo> const& tokenInfo = getTokenInfo(clientId);
      retVal = tokenInfo->hasAccessToken();
    }catch(std::invalid_argument &e){
      //nothing to do
    }

    return retVal;
  }

  std::string DefaultStorage::getAccessToken(const std::string clientId)
  {
    std::string retVal;
    try{
      std::unique_ptr<TokenInfo> const& tokenInfo = getTokenInfo(clientId);
      retVal = tokenInfo->getAccessToken();
    }catch(std::invalid_argument &e){
      //nothing to do
    }

    return retVal;
  }

  bool DefaultStorage::hasRefreshToken(const std::string clientId)
  {
    bool retVal = false;
    try{
      std::unique_ptr<TokenInfo> const& tokenInfo = getTokenInfo(clientId);
      retVal = tokenInfo->hasRefreshToken();
    }catch(std::invalid_argument &e){
      //nothing to do
    }

    return retVal;
  }

  std::string DefaultStorage::getRefreshToken(const std::string clientId)
  {
    std::string retVal;
    try{
      std::unique_ptr<TokenInfo> const& tokenInfo = getTokenInfo(clientId);
      retVal = tokenInfo->getRefreshToken();
    }catch(std::invalid_argument &e){
      //nothing to do
    }

    return retVal;
  }

} // namespace oauth2


