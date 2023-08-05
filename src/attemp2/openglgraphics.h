#ifndef OPENGLGRAPHICS_H
#define OPENGLGRAPHICS_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class openGLGraphics : public QOpenGLWidget, public QOpenGLFunctions
{
public:
    openGLGraphics(QWidget *parent);


protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL()override;
private:
    void qColorToRGB(const QColor &color, float &r, float &g, float &b) const;
    float normalizeColorValue(float val, float min, float max) const;
    void changeBack(QColor color);

};

#endif // OPENGLGRAPHICS_H
