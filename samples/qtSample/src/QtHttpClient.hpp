#ifndef QTHTTPCLIENT_HPP
#define QTHTTPCLIENT_HPP

#include "oauth2cpp/HttpClient.hpp"
#include "QtHttpRequest.hpp"

#include <QObject>
#include <QHash>
#include <QNetworkRequest>

namespace oauth2{
  class Client;
}
class QNetworkAccessManager;
class QNetworkReply;
class QtHttpClient : public QObject, public oauth2::HttpClient
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

#endif // QTHTTPCLIENT_HPP
