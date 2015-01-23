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

  QtHttpResponse response(reply);
  QByteArray result = reply->readAll();
  ui->webView->setContent(result,"text/plain");
}
