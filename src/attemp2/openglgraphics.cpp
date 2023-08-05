#include "openglgraphics.h"

openGLGraphics::openGLGraphics(QWidget *parent):QOpenGLWidget {parent}
{

    
}

void openGLGraphics::initializeGL()
{
//    float r, g, b, a = 1;
    initializeOpenGLFunctions();
//    qColorToRGB(Qt::black, r, g, b);
//    glClearColor(r, g, b, a);
    changeBack(Qt::black);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);


}

void openGLGraphics::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
}

void openGLGraphics::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
}

void openGLGraphics::qColorToRGB(const QColor &color, float &r, float &g, float &b) const{
    int red = color.red();
    int green = color.green();
    int blue = color.blue();
    r = normalizeColorValue(red, 1.f, 255.f);
    g = normalizeColorValue(green, 1.f, 255.f);
    b = normalizeColorValue(blue, 1.f, 255.f);
}
float openGLGraphics::normalizeColorValue(float val, float min, float max) const{
    return (val - min ) / (max - min);
}

void openGLGraphics::changeBack(QColor color)
{
        float r, g, b, a = 1;
        qColorToRGB(color, r, g, b);
        glClearColor(r, g, b, a);
}
