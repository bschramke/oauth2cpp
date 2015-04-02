/**
 * @file QtHttpRequest.cpp
 * @author Björn Schramke <schramke@fh-brandenburg.de>
 * @since 0.0.1
 *
 * Copyright 2015 oauth2cpp Contributors. All rights reserved.
 * See CONTRIBUTORS file for full list.
 *
 * SPDX-License-Identifier: BSL-1.0
 *
 */
#include "oauth2cpp/qt/QtHttpRequest.hpp"

#include <network/uri.hpp>
#include <QNetworkRequest>

namespace oauth2 {

  QtHttpRequest::QtHttpRequest()
  {
    this->qNetworkRequest = new QNetworkRequest();
    this->shouldDeleteRequest = true;
  }

  QtHttpRequest::QtHttpRequest(QNetworkRequest *qnRequest)
  {
    this->qNetworkRequest = qnRequest;
    this->shouldDeleteRequest = false;
  }


  QtHttpRequest::~QtHttpRequest()
  {
    if(shouldDeleteRequest)
      {
        delete this->qNetworkRequest;
      }
  }

  const QNetworkRequest* QtHttpRequest::getQNetworkRequest() const
  {
    return this->qNetworkRequest;
  }

  void QtHttpRequest::setUri(const network::uri &uri)
  {
    this->qNetworkRequest->setUrl(QUrl(uri.string().c_str()));
  }

  void QtHttpRequest::setHeader(const std::string &key, const std::string &value)
  {
    this->qNetworkRequest->setRawHeader(QByteArray(key.c_str()),QByteArray(value.c_str()));
  }

} // namespace oauth2
