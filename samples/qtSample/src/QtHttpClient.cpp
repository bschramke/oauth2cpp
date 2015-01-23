#include "QtHttpClient.hpp"
#include "oauth2cpp/Client.hpp"

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QtHttpClient::QtHttpClient(QObject *parent) :
  QObject(parent)
{
}

QtHttpClient::QtHttpClient(QNetworkAccessManager *accessManager, QObject *parent):
  QObject(parent), netAccessMgr(accessManager)
{
}

QtHttpRequest *QtHttpClient::createRequest() const
{
  return new QtHttpRequest();
}

void QtHttpClient::get(oauth2::HttpRequest *request)
{
  auto qtHttpRequest = dynamic_cast<QtHttpRequest*>(request);
  netAccessMgr->get(*(qtHttpRequest->getQNetworkRequest()));
}

void QtHttpClient::post(oauth2::HttpRequest *request, const std::string &data)
{
  auto qtHttpRequest = dynamic_cast<QtHttpRequest*>(request);
  QObject::connect(netAccessMgr,SIGNAL(finished(QNetworkReply*)),
              this,SLOT(onAccessTokenRequestFinished(QNetworkReply*)));

  auto qnRequest = qtHttpRequest->getQNetworkRequest();
  netAccessMgr->post(*qnRequest,QByteArray(data.c_str()));
}

void QtHttpClient::onAccessTokenRequestFinished(QNetworkReply *reply)
{
  qDebug() << "onAccessTokenRequestFinished";
  if (reply->error() > 0){
      qDebug() << reply->errorString();
      return;
  }

  QByteArray result = reply->readAll();
  qDebug() << result;
}
