#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "openglgraphics.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_3_clicked()
{
    QColorDialog colorPick;
    if(colorPick.exec() == QDialog::Accepted)
    {
        QColor selectedColor = colorPick.selectedColor();
        widgetColor = selectedColor;

    }
}

