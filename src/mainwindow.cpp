#include "mainwindow.h"
#include "ui_mainwindow.h"

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


//void MainWindow::on_pushButton_clicked()
//{
////    ui->label->setText("Hello world");
////    v_point first;
////    f_point second;
//////    QString file =
//////            QFileDialog::getOpenFileName(this, "Выбрать файл для открытия",
//////                                         0, "Text Files (*.obj)");
//////    qDebug() << file;
////    QString filename = "/opt/goinfre/daniellm/Projects/3d_second/simple_cube.obj";
////    QByteArray ba = filename.toLocal8Bit();
////    const char *fname = ba.data();

////    int result = dot_parser(fname, &first, &second);
////    qDebug() << first.size;
////    qDebug() << second.size;
////    qDebug() << result;

//}

