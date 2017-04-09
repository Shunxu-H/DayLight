#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QOpenGLWidget>
#include <QDesktopWidget>
#include <QDockWidget>
#include <oglwidget.h>

_MainWindow::_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    QDockWidget *dock = new QDockWidget(tr("Canvas"), this);
    dock->setWidget(new OGLWidget());
    addDockWidget(Qt::LeftDockWidgetArea, dock);


}

_MainWindow::~_MainWindow()
{
    delete ui;
}
