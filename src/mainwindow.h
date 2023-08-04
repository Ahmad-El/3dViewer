#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtOpenGL>
#include <QOpenGLWidget>

//#include <stdlib.h>
//extern "C" {
//#include "viewer.h"
//}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//private slots:
//    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
//    float *arr;
};
#endif // MAINWINDOW_H