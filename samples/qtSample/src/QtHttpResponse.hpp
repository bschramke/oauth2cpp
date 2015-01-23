#ifndef QTHTTPRESPONSE_HPP
#define QTHTTPRESPONSE_HPP

#include "oauth2cpp/HttpResponse.hpp"

class QNetworkReply;
class QtHttpResponse: public oauth2::HttpResponse
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

#endif // QTHTTPRESPONSE_HPP
