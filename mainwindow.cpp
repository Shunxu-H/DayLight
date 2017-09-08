#include <QOpenGLWidget>
#include <QDesktopWidget>
#include <QDockWidget>
#include <QGridLayout>
#include <QProgressBar>
#include <QPushButton>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CVM.h"

_MainWindow::_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);


    QDockWidget *dock = new QDockWidget(tr("Canvas"), this);
    //dock->setWidget(new CVM(dock));
    addDockWidget(Qt::LeftDockWidgetArea, dock);


    QDockWidget *dw = new QDockWidget (this);
    QWidget *widgetContainer = new QWidget;
    QGridLayout *gLayout = new QGridLayout ();

    QProgressBar *pb = new QProgressBar ();
    QPushButton *abortButton = new QPushButton ("abort");
    QPushButton *abortButton2 = new QPushButton ("abort2");


    gLayout->addWidget (pb, 0, 0, Qt::AlignLeft);
    gLayout->addWidget (abortButton, 0,1, Qt::AlignRight);

    widgetContainer->setLayout (gLayout);
    dw->setWidget (widgetContainer);
    //gLayout->setSizeConstraint (QLayout::SetFixedSize);
    gLayout->addWidget (pb, 0, 0/*, Qt::AlignLeft*/);
    dw->setTitleBarWidget( new QWidget (this));

    //add the dock widget to the bottom area of the main window, under
    //the central widget (the subview window)
    addDockWidget (Qt::BottomDockWidgetArea, dw);


}

_MainWindow::~_MainWindow()
{
    delete ui;
}
