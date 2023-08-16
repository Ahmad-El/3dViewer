#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "openglgraphics.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initConfig();

}

MainWindow::~MainWindow()
{
    structClean(&ui->widget->object);
    delete ui;
}

void MainWindow::initConfig(){
    QString style = QString("background-color: transparent; color: #1affbc; border-style: solid; border-width: 1px; border-color: #1affbc; border-radius: 10px; ");
    ui->pushButton_3->setStyleSheet(style);
    style = QString("background-color: transparent; color: #ff55d9; border-style: solid; border-width: 1px; border-color: #ff55d9; border-radius: 10px; ");
    ui->pushButton_lineColor->setStyleSheet(style);
    ui->pushButton_dotColor->setStyleSheet(style);

    ui->scale_move->setRange(1, 10);
    ui->scale_move->setSingleStep(1);
    ui->scale_move->setValue(1);

}
void MainWindow::on_pushButton_3_clicked()
{

    QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
    if (color.isValid())
    {
        ui->widget->makeCurrent();
        ui->widget->backgroundColor = color;
        ui->widget->update();
    }
}


void MainWindow::on_pushButton_openFile_clicked()
{
    QString file =
            QFileDialog::getOpenFileName(this, "Выбрать файл для открытия",
                                         0, "Text Files (*.obj)");
    structClean(&ui->widget->object);
    ui->widget->filename = file;
    ui->widget->setFileName();
    ui->widget->update();
}

void MainWindow::on_minus_x_clicked()
{
    double value = ui->x_rotate_value->value() * (- 1);
    rotation_by_ox(&ui->widget->object, value);
    ui->widget->update();
}


void MainWindow::on_plus_x_clicked()
{
    double value = ui->x_rotate_value->value();
    rotation_by_ox(&ui->widget->object, value);
    ui->widget->update();
}


void MainWindow::on_minus_y_clicked()
{
    double value = ui->y_rotate_value->value() * (-1);
    rotation_by_oy(&ui->widget->object, value);
    ui->widget->update();
}


void MainWindow::on_plus_y_clicked()
{
    double value = ui->y_rotate_value->value();
    rotation_by_oy(&ui->widget->object, value);
    ui->widget->update();

}


void MainWindow::on_minus_z_clicked()
{
    double value = ui->z_rotate_value->value() * (-1);
    rotation_by_oz(&ui->widget->object, value);
    ui->widget->update();
}


void MainWindow::on_plus_z_clicked()
{
    double value = ui->z_rotate_value->value();
    rotation_by_oz(&ui->widget->object, value);
    ui->widget->update();
}


void MainWindow::on_move_x_minus_clicked()
{
    double value = ui->x_move_value->value() * (-1);
    move_x(&ui->widget->object, value);
    ui->widget->update();

}


void MainWindow::on_move_x_plus_clicked()
{
    double value = ui->x_move_value->value();
    move_x(&ui->widget->object, value);
    ui->widget->update();
}


void MainWindow::on_move_y_minus_clicked()
{
    double value = ui->y_move_value->value() * (-1);
    move_y(&ui->widget->object, value);
    ui->widget->update();
}


void MainWindow::on_move_y_plus_clicked()
{
    double value = ui->y_move_value->value();
    move_y(&ui->widget->object, value);
    ui->widget->update();

}


void MainWindow::on_move_z_minus_clicked()
{
    double value = ui->z_move_value->value() * (-1);
    move_z(&ui->widget->object, value);
    ui->widget->update();
}


void MainWindow::on_move_z_plus_clicked()
{
    double value = ui->z_move_value->value();
    move_z(&ui->widget->object, value);
    ui->widget->update();

}


void MainWindow::on_scale_down_clicked()
{
    double value = (10 - ui->scale_move->value()) / 10.0;
    scale_model(&ui->widget->object, value);
    ui->widget->update();
}


void MainWindow::on_scale_up_clicked()
{
    double value = (10 - ui->scale_move->value()) / 10.0;
    scale_model(&ui->widget->object, 1.0 / value);
    ui->widget->update();
}


void MainWindow::on_perpective_mode_clicked()
{
    if(ui->widget->perpectiveMode == false)
    {
        ui->widget->perpectiveMode = true;
        ui->widget->update();
    }
}


void MainWindow::on_paralel_mode_clicked()
{
    if(ui->widget->perpectiveMode == true){
        ui->widget->perpectiveMode = false;
        ui->widget->update();
    }

}


void MainWindow::on_pushButton_lineColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
    if (color.isValid())
    {
        ui->widget->lineColor = color;
        ui->widget->update();
    }

}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_move_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_rotate_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->widget->dashObj = false;
    ui->widget->lineObj = false;
    ui->widget->update();
}


void MainWindow::on_pushButton_5_clicked()
{
    if(ui->widget->lineObj == false){
        ui->widget->lineObj = true;
        ui->widget->dashObj = false;
        ui->widget->update();
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    if(ui->widget->dashObj == false){
        ui->widget->dashObj = true;
        ui->widget->lineObj = false;
        ui->widget->update();
    }
}


void MainWindow::on_line_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_pushButtonWidth_clicked()
{
    ui->widget->lineWidth = ui->lineWidthValue->value();
    ui->widget->update();

}


void MainWindow::on_pushButton_noDot_clicked()
{
    ui->widget->dotObj = false;
    ui->widget->squareObj = false;
    ui->widget->update();
}


void MainWindow::on_pushButton_dot_clicked()
{
    if(ui->widget->dotObj == false ){
        ui->widget->dotObj = true;
        ui->widget->squareObj = false;
        ui->widget->update();
    }
}


void MainWindow::on_pushButton_dotSquare_clicked()
{
    if(ui->widget->squareObj == false){
        ui->widget->squareObj = true;
        ui->widget->dotObj = false;
        ui->widget->update();
    }
}


void MainWindow::on_dot_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_dotColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
    if (color.isValid())
    {
        ui->widget->dotColor = color;
        ui->widget->update();
    }

}

void MainWindow::on_pushButton_dotSize_clicked()
{
    ui->widget->dotSize = ui->dotSize->value();
    ui->widget->update();
}
