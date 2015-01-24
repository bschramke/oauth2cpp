#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "QtHttpRequest.hpp"
#include "QtHttpResponse.hpp"

#include "oauth2cpp/Client.hpp"
#include "oauth2cpp/ClientConfiguration.hpp"

#include <network/uri.hpp>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace {
  enum {
    REQUEST_TYPE = QNetworkRequest::User
  };

  enum{
    REQUEST_TOKEN,
    REQUEST_REFRESH,
    REQUEST_API
  };
}

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  oauthConfig = new oauth2::ClientConfiguration(GOOGLE_CLIENT_ID,GOOGLE_CLIENT_SECRET);
  oauthConfig->setAuthorizationEndpoint("https://accounts.google.com/o/oauth2/auth");
  oauthConfig->setTokenEndpoint("https://www.googleapis.com/oauth2/v3/token");
  oauthConfig->setRedirectUri("urn:ietf:wg:oauth:2.0:oob");

  this->netAccessMgr = new QNetworkAccessManager(this);
  oauthClient = new oauth2::Client(oauthConfig);
  oauthClient->setTokenStorage(&tokenStorage);

  initConnections();
}

MainWindow::~MainWindow()
{
  delete oauthClient;
  delete ui;
}

void MainWindow::initConnections()
{
  connect( ui->authButton, SIGNAL(clicked()), this, SLOT(onClickAuthenticate()) );
  connect( ui->refreshButton, SIGNAL(clicked()), this, SLOT(onClickRefresh()) );
  connect( ui->userInfoButton, SIGNAL(clicked()), this, SLOT(onClickUserInfo()) );
  connect(ui->webView, SIGNAL(titleChanged(QString)), SLOT(onWebViewTitleChanged(QString)));

  connect(netAccessMgr,SIGNAL(finished(QNetworkReply*)),
              this,SLOT(onNetworkRequestFinished(QNetworkReply*)));
}

void MainWindow::onClickAuthenticate()
{
  ui->textEdit->append("request Authentication with URI");
  auto authUri = oauthClient->getAuthorizationRequestUri();
  ui->textEdit->append((authUri.string()+")").c_str());
  ui->webView->load(QUrl(authUri.string().c_str()));

}

void MainWindow::onClickRefresh()
{
  QNetworkRequest qnRequest;
  QtHttpRequest request(&qnRequest);
  std::string requestData;
  bool success = oauthClient->createRefreshTokenRequest(request,requestData);

  if(success)
    {
      ui->textEdit->append("refresh Authentication with URI");
      ui->textEdit->append(qnRequest.url().toString());
      ui->textEdit->append("\n requestData = ");
      ui->textEdit->append(requestData.c_str());

      qnRequest.setAttribute((QNetworkRequest::Attribute)REQUEST_TYPE,REQUEST_REFRESH);
      netAccessMgr->post(qnRequest,QByteArray(requestData.c_str()));
    }
  else
    {
      ui->textEdit->append("you need to authenticate first");
    }
}

void MainWindow::onClickUserInfo()
{
  QNetworkRequest qnRequest(QUrl("https://www.googleapis.com/oauth2/v2/userinfo"));
  QtHttpRequest request(&qnRequest);
  bool authorized = oauthClient->authorize(request);
  if(!authorized)
    {
      ui->textEdit->append("you need to authenticate first");
      return;
    }

  ui->textEdit->append("call api with uri");
  ui->textEdit->append(qnRequest.url().toString());
  qnRequest.setAttribute((QNetworkRequest::Attribute)REQUEST_TYPE,REQUEST_API);
  netAccessMgr->get(qnRequest);

}

void MainWindow::onWebViewTitleChanged(QString title)
{
  if(title.startsWith("Success code="))
    {
      const QString auth_code = title.right(title.length()-13);
      ui->textEdit->append("Success! Authorization code = "+auth_code);

      QNetworkRequest qnRequest;
      QtHttpRequest request(&qnRequest);
      std::string requestData;
      oauthClient->createAccessTokenRequest(auth_code.toStdString(),request,requestData);

      ui->textEdit->append("\nrequest access token with URI");
      ui->textEdit->append(qnRequest.url().toString());
      ui->textEdit->append("\n requestData = ");
      ui->textEdit->append(requestData.c_str());

      qnRequest.setAttribute((QNetworkRequest::Attribute)REQUEST_TYPE,REQUEST_TOKEN);
      netAccessMgr->post(qnRequest,QByteArray(requestData.c_str()));
    }
}

void MainWindow::onNetworkRequestFinished(QNetworkReply *reply)
{
  qDebug() << "onNetworkRequestFinished";

  if (reply->error() > 0){
      ui->textEdit->append("\nfinished request with error: " + reply->errorString());
      ui->webView->setContent(reply->readAll());
      return;
  }

  auto request = reply->request();
  auto requestType = request.attribute((QNetworkRequest::Attribute)REQUEST_TYPE);

  QtHttpResponse response(reply);
  QByteArray result;
  switch(requestType.toInt())
    {
    case REQUEST_TOKEN:
      oauthClient->handleAccessTokenResponse(response);
      ui->refreshButton->setEnabled(true);
      ui->userInfoButton->setEnabled(true);
      break;
    case REQUEST_REFRESH:
      ui->textEdit->append("\nSuccessfully finished refresh token request\n");
      oauthClient->handleRefreshTokenResponse(response);
      break;
    case REQUEST_API:
      result = reply->readAll();
      ui->webView->setContent(result,"application/json");
      break;
    default:
      result = reply->readAll();
      ui->webView->setContent(result,"text/plain");
      break;
    }
}
