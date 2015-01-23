#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  initConnections();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::initConnections()
{
}
