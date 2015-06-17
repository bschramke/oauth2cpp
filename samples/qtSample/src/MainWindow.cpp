#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "oauth2cpp/Client.hpp"
#include "oauth2cpp/ClientConfiguration.hpp"
#include "oauth2cpp/qt/QtHttpRequest.hpp"
#include "oauth2cpp/qt/QtHttpResponse.hpp"

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

  oauthConfig = new oauth2::ClientConfiguration(OAUTH_CLIENT_ID,OAUTH_CLIENT_SECRET);
  oauthConfig->setAuthorizationEndpoint(ui->edit_auth_endpoint->text().toStdString());
  oauthConfig->setTokenEndpoint(ui->edit_redirect_uri->text().toStdString());
  oauthConfig->setRedirectUri(ui->edit_token_endpoint->text().toStdString());

  this->netAccessMgr = new QNetworkAccessManager(this);
  oauthClient = new oauth2::Client(oauthConfig);
  oauthClient->setTokenStorage(&tokenStorage);

  updateButtonStates();
  initConnections();
}

MainWindow::~MainWindow()
{
  delete oauthClient;
  delete ui;
}

void MainWindow::onChangeAuthEndpoint(QString value)
{
  oauthConfig->setAuthorizationEndpoint(value.toStdString());
  updateButtonStates();
}

void MainWindow::onChangeTokenEndpoint(QString value)
{
  oauthConfig->setTokenEndpoint(value.toStdString());
  updateButtonStates();
}

void MainWindow::onChangeRedirectUri(QString value)
{
  oauthConfig->setRedirectUri(value.toStdString());
  updateButtonStates();
}

void MainWindow::initConnections()
{
  connect( ui->authButton, SIGNAL(clicked()), this, SLOT(onClickAuthenticate()) );
  connect( ui->refreshButton, SIGNAL(clicked()), this, SLOT(onClickRefresh()) );
  connect( ui->userInfoButton, SIGNAL(clicked()), this, SLOT(onClickUserInfo()) );
  connect(ui->webView, SIGNAL(titleChanged(QString)), SLOT(onWebViewTitleChanged(QString)));

  connect( ui->edit_auth_endpoint, SIGNAL(textChanged(QString)), this, SLOT(onChangeAuthEndpoint(QString)) );
  connect( ui->edit_token_endpoint, SIGNAL(textChanged(QString)), this, SLOT(onChangeTokenEndpoint(QString)) );
  connect( ui->edit_redirect_uri, SIGNAL(textChanged(QString)), this, SLOT(onChangeRedirectUri(QString)) );

  connect(netAccessMgr,SIGNAL(finished(QNetworkReply*)),
          this,SLOT(onNetworkRequestFinished(QNetworkReply*)));
}

bool MainWindow::checkOAuthConfig()
{
  bool authEndpointOk = false;
  bool tokenEndpointOk = false;
  bool redirectUriOk = false;

  QString value = ui->edit_auth_endpoint->text();
  authEndpointOk = (!value.isNull() && !value.isEmpty());

  value = ui->edit_token_endpoint->text();
  tokenEndpointOk = (!value.isNull() && !value.isEmpty());

  value = ui->edit_redirect_uri->text();
  redirectUriOk = (!value.isNull() && !value.isEmpty());

  return (authEndpointOk && tokenEndpointOk && redirectUriOk);
}

void MainWindow::updateButtonStates()
{
  bool oauthConfigOk = checkOAuthConfig();

  ui->authButton->setEnabled(oauthConfigOk);

}

void MainWindow::onClickAuthenticate()
{
  ui->textEdit->append("request Authentication with URI");
  auto authUri = oauthClient->getAuthorizationRequestUri((std::set<std::string>){"https://www.googleapis.com/auth/plus.me","https://www.googleapis.com/auth/userinfo.profile"});
  ui->textEdit->append((authUri.string()+")").c_str());
  ui->webView->load(QUrl(authUri.string().c_str()));

}

void MainWindow::onClickRefresh()
{
  QNetworkRequest qnRequest;
  oauth2::QtHttpRequest request(&qnRequest);
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
  oauth2::QtHttpRequest request(&qnRequest);
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
      oauth2::QtHttpRequest request(&qnRequest);
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

  oauth2::QtHttpResponse response(reply);
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
