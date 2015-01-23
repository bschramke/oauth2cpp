/**
 * @brief
 * @file HttpRequest.hpp
 * @author Björn Schramke <schramke@fh-brandenburg.de>
 * @since 0.0.1
 *
 * Copyright 2015 oauth2cpp Contributors. All rights reserved.
 * See CONTRIBUTORS file for full list.
 *
 * SPDX-License-Identifier: BSL-1.0
 *
 */
#ifndef OAUTH2CPP_HTTPREQUEST_HPP
#define OAUTH2CPP_HTTPREQUEST_HPP

#include "oauth2cpp/OAuth2.hpp"

#include <string>

namespace network{
  class uri;
}

namespace oauth2{

  class OAUTH2CPP_API HttpRequest
  {
  public:
    virtual void setUri(const network::uri& uri) = 0;
    virtual void setHeader(const std::string& key,const std::string& value) = 0;
  };

} // namespace oauth2

#endif // OAUTH2CPP_HTTPREQUEST_HPP
