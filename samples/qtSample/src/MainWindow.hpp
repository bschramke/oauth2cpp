#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
  class MainWindow;
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

private:
  void initConnections();

  Ui::MainWindow *ui = nullptr;
};

#endif // MAINWINDOW_HPP
