/**
 * @brief
 * @file HttpResponse.hpp
 * @author Björn Schramke <schramke@fh-brandenburg.de>
 * @since 0.1
 *
 * Copyright 2015 oauth2cpp Contributors. All rights reserved.
 * See CONTRIBUTORS file for full list.
 *
 * SPDX-License-Identifier: BSL-1.0
 *
 */
#ifndef OAUTH2CPP_QT_HTTPRESPONSE_HPP
#define OAUTH2CPP_QT_HTTPRESPONSE_HPP

#include "oauth2cpp/OAuth2.hpp"
#include "oauth2cpp/HttpResponse.hpp"

class QNetworkReply;

namespace oauth2{

  class OAUTH2CPP_API QtHttpResponse: public HttpResponse
  {
  public:
    explicit QtHttpResponse(QNetworkReply *qnReply);
    ~QtHttpResponse();

    const QNetworkReply* getQNetworkReply() const;


    // HttpResponse interface
  public:
    const char* readAll() const;

  private:
    QNetworkReply* qnReply = nullptr;
  };
} // namespace oauth2

#endif // OAUTH2CPP_HTTPRESPONSE_HPP
