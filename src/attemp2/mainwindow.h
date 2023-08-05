#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QColor widgetColor = Qt::black;
private slots:
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
/// https://youtu.be/W3-SMvMa8D4
