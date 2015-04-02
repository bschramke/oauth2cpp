/**
 * @brief
 * @file QtHttpClient.hpp
 * @author Björn Schramke <schramke@fh-brandenburg.de>
 * @since 0.0.1
 *
 * Copyright 2015 oauth2cpp Contributors. All rights reserved.
 * See CONTRIBUTORS file for full list.
 *
 * SPDX-License-Identifier: BSL-1.0
 *
 */
#ifndef OAUTH2CPP_QT_HTTPCLIENT_HPP
#define OAUTH2CPP_QT_HTTPCLIENT_HPP

#include "oauth2cpp/OAuth2.hpp"
#include "oauth2cpp/HttpClient.hpp"
#include "oauth2cpp/qt/QtHttpRequest.hpp"

#include <string>
#include <QObject>
#include <QHash>
#include <QNetworkRequest>

class QNetworkAccessManager;
class QNetworkReply;

namespace oauth2{

  class OAUTH2CPP_API QtHttpClient : public QObject, public HttpClient
  {
    Q_OBJECT
  public:
    explicit QtHttpClient(QObject *parent = 0);
    explicit QtHttpClient(QNetworkAccessManager* accessManager,QObject *parent = 0);

    // oauth2::HttpClient interface
  public:
    QtHttpRequest *createRequest() const;
    virtual void get(oauth2::HttpRequest* request) override;
    virtual void post(oauth2::HttpRequest* request, const std::string& data) override;

  signals:

  public slots:
    void onAccessTokenRequestFinished(QNetworkReply* reply);

  private:
    QNetworkAccessManager* netAccessMgr = nullptr;
    QHash<QNetworkRequest,void(oauth2::Client::*)(void)> requestCallbackMap;

  };

} // namespace oauth2

#endif // OAUTH2CPP_QT_HTTPCLIENT_HPP
