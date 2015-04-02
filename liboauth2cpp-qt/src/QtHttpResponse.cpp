/**
 * @file QtHttpResponse.cpp
 * @author Björn Schramke <schramke@fh-brandenburg.de>
 * @since 0.0.1
 *
 * Copyright 2015 oauth2cpp Contributors. All rights reserved.
 * See CONTRIBUTORS file for full list.
 *
 * SPDX-License-Identifier: BSL-1.0
 *
 */
#include "oauth2cpp/qt/QtHttpResponse.hpp"

#include <QNetworkReply>

namespace oauth2 {

  QtHttpResponse::QtHttpResponse(QNetworkReply* qnReply)
    :qnReply(qnReply)
  {
  }

  QtHttpResponse::~QtHttpResponse()
  {
  }

  const QNetworkReply* QtHttpResponse::getQNetworkReply() const
  {
    return this->qnReply;
  }

  const char* QtHttpResponse::readAll() const
  {
    return this->qnReply->readAll().constData();
  }

} // namespace oauth2
