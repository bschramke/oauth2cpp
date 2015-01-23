#include "QtHttpRequest.hpp"
#include <network/uri.hpp>
#include <QNetworkRequest>

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


