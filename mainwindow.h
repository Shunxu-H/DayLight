#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class _MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit _MainWindow(QWidget *parent = 0);
    ~_MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
