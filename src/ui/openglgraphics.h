#ifndef OPENGLGRAPHICS_H
#define OPENGLGRAPHICS_H

#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

extern "C" {
#include <../c_code/3D_viewer.h>
#include <../c_code/sources/model_loading.h>
}

#define RGB_MIN 1
#define RGB_MAX 255

class openGLGraphics : public QOpenGLWidget, public QOpenGLFunctions {
 public:
  openGLGraphics(QWidget *parent);
  ~openGLGraphics();

  QColor backgroundColor;
  QString filename;
  bool perpectiveMode;
  QColor lineColor, dotColor;
  bool dotObj, squareObj;
  bool lineObj, dashObj;
  float lineWidth;
  float dotSize;
  float gapSize;

  QJsonObject configObject;
  geometry_info object = {0};
  float xRot, yRot, zRot;
  QPoint mPos;

 public slots:
  void setFileName();
  void normalizeObject();
  void toScreen();
  void changeBack();
  void changeViewMode();
  void toScreenOrtho();
  void toScreenFrust();
  void writeToJsonFile();
  void readFromJsonFile();
  void initialSettings();
  void loadConfigSettings();
  void saveConfigSettings();

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private slots:
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void qColorToRGB(const QColor &color, float &r, float &g, float &b) const;
  float normalizeColorValue(float val, float min, float max) const;
  void drawObj();
  void drawObjDot(int i);
  void drawObjLine(int i);
};

#endif  // OPENGLGRAPHICS_H
