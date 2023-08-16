#ifndef OPENGLGRAPHICS_H
#define OPENGLGRAPHICS_H


#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QMouseEvent>

//#include "mainwindow.h"

#include <QFileDialog>

extern "C" {
#include <../c_code/sources/model_loading.h>
#include <../c_code/3D_viewer.h>
}

#define RGB_MIN 1
#define RGB_MAX 255
class openGLGraphics : public QOpenGLWidget, public QOpenGLFunctions
{
public:
    openGLGraphics(QWidget *parent);
    QColor backgroundColor;
    QString filename = "/opt/goinfre/daniellm/school/projects/gitlab/C8_3DViewer_v1.0/C8_3DViewer_v1.0-1/src/frontend/ahmad/models/teddy.obj";
    geometry_info object = {0};
    bool perpectiveMode;
    float rotationAngle = 1.0f;
    float xRot, yRot, zRot;
    float centerByX, centerByY, centerByZ;
    QPoint mPos;
    QColor lineColor, dotColor;
    bool dotObj, squareObj, noDot;
    bool lineObj, dashObj, noLine;
    float lineWidth;
    float dotSize;

public slots:
    void setFileName();
    void normalizeObject();
    void toScreen();
    void changeBack();
    void changeViewMode();
    void toScreenOrtho();
    void toScreenFrust();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL()override;

private slots:
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void qColorToRGB(const QColor &color, float &r, float &g, float &b) const;
    float normalizeColorValue(float val, float min, float max) const;
    void drawObj();
    void drawObjDot(int i);
    void drawObjLine(int i);
    void initLineDotSet();
};

#endif // OPENGLGRAPHICS_H
