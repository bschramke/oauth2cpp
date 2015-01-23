#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

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
  void onClickAuthenticate();
  void onWebViewTitleChanged(QString title);

  void onNetworkRequestFinished(QNetworkReply* reply);

private:
  void initConnections();

  Ui::MainWindow *ui = nullptr;
  oauth2::ClientConfiguration *oauthConfig = nullptr;
  oauth2::Client *oauthClient = nullptr;
  QNetworkAccessManager *netAccessMgr = nullptr;
};

#endif // MAINWINDOW_HPP
