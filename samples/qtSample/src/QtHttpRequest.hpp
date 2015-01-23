#ifndef QTHTTPREQUEST_HPP
#define QTHTTPREQUEST_HPP

#include "oauth2cpp/HttpRequest.hpp"

namespace network{
  class uri;
}

class QNetworkRequest;
class QtHttpRequest: public oauth2::HttpRequest
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

#endif // QTHTTPREQUEST_HPP
