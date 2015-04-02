/**
 * @brief
 * @file QtHttpRequest.hpp
 * @author Björn Schramke <schramke@fh-brandenburg.de>
 * @since 0.0.1
 *
 * Copyright 2015 oauth2cpp Contributors. All rights reserved.
 * See CONTRIBUTORS file for full list.
 *
 * SPDX-License-Identifier: BSL-1.0
 *
 */
#ifndef OAUTH2CPP_QT_HTTPREQUEST_HPP
#define OAUTH2CPP_QT_HTTPREQUEST_HPP

#include "oauth2cpp/OAuth2.hpp"
#include "oauth2cpp/HttpRequest.hpp"

#include <string>

class QNetworkRequest;

namespace oauth2{
  class OAUTH2CPP_API QtHttpRequest: public HttpRequest
  {
  public:
    explicit QtHttpRequest();
    explicit QtHttpRequest(QNetworkRequest* qnRequest);
    ~QtHttpRequest();

    const QNetworkRequest* getQNetworkRequest() const;

    // HttpRequest interface
  public:
    void setUri(const network::uri &uri);
    void setHeader(const std::string &key, const std::string &value);

  private:
    bool shouldDeleteRequest = false;
    QNetworkRequest* qNetworkRequest = nullptr;

  };
} // namespace oauth2

#endif // OAUTH2CPP_QT_HTTPREQUEST_HPP
