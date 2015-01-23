#include "QtHttpResponse.hpp"
#include <QNetworkReply>


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
