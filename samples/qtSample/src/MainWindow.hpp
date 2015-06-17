#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "oauth2cpp/DefaultStorage.hpp"

#include <QMainWindow>

namespace Ui {
  class MainWindow;
}

namespace oauth2 {
  class Client;
  class ClientConfiguration;
}

class QNetworkReply;
class QNetworkAccessManager;
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

protected slots:
  void onChangeAuthEndpoint(QString value);
  void onChangeTokenEndpoint(QString value);
  void onChangeRedirectUri(QString value);
  void onClickAuthenticate();
  void onClickRefresh();
  void onClickUserInfo();
  void onWebViewTitleChanged(QString title);

  void onNetworkRequestFinished(QNetworkReply* reply);

private:
  void initConnections();
  void updateButtonStates();
  bool checkOAuthConfig();

  Ui::MainWindow *ui = nullptr;
  oauth2::ClientConfiguration *oauthConfig = nullptr;
  oauth2::Client *oauthClient = nullptr;
  oauth2::DefaultStorage tokenStorage;
  QNetworkAccessManager *netAccessMgr = nullptr;
};

#endif // MAINWINDOW_HPP
