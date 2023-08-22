#include "openglgraphics.h"

#include <QCoreApplication>
openGLGraphics::openGLGraphics(QWidget *parent) : QOpenGLWidget(parent) {
  QString projectPath = QCoreApplication::applicationDirPath();
  if (QFile::exists(projectPath + "/config.json")) {
    qDebug() << "file is working";
    readFromJsonFile();
    loadConfigSettings();
  } else {
    initialSettings();
  }
  setFileName();
}

void openGLGraphics::writeToJsonFile() {
  QJsonDocument jsonDoc(configObject);
  QString projectPath = QCoreApplication::applicationDirPath();
  QFile file(projectPath + "/config.json");
  file.open(QIODevice::WriteOnly | QIODevice::Truncate);
  file.write(jsonDoc.toJson());
  file.close();
}

void openGLGraphics::readFromJsonFile() {
  QString projectPath = QCoreApplication::applicationDirPath();
  QFile configFile(projectPath + "/config.json");
  configFile.open(QIODevice::ReadOnly);
  QByteArray configData = configFile.readAll();
  QJsonParseError parseError;
  QJsonDocument jsonDoc = QJsonDocument::fromJson(configData, &parseError);
  qDebug().noquote() << jsonDoc.toJson(QJsonDocument::Indented);
  configObject = jsonDoc.object();
  configFile.close();
}

void openGLGraphics::loadConfigSettings() {
  backgroundColor = configObject["backgroundColor"].toString();
  filename = configObject["filename"].toString();
  perpectiveMode = configObject["perpectiveMode"].toBool();
  lineColor = configObject["lineColor"].toString();
  dotColor = configObject["dotColor"].toString();
  dotObj = configObject["dotObj"].toBool();
  lineObj = configObject["lineObj"].toBool();
  squareObj = configObject["squareObj"].toBool();
  dashObj = configObject["dashObj"].toBool();
  lineWidth = static_cast<float>(configObject["lineWidth"].toDouble());
  dotSize = static_cast<float>(configObject["dotSize"].toDouble());
  gapSize = static_cast<float>(configObject["gapSize"].toDouble());
}
void openGLGraphics::saveConfigSettings() {
  configObject["backgroundColor"] = backgroundColor.name(QColor::HexArgb);
  configObject["filename"] = filename;
  configObject["perpectiveMode"] = perpectiveMode;
  configObject["lineColor"] = lineColor.name(QColor::HexArgb);
  configObject["dotColor"] = dotColor.name(QColor::HexArgb);
  configObject["dotObj"] = dotObj;
  configObject["lineObj"] = lineObj;
  configObject["squareObj"] = squareObj;
  configObject["dashObj"] = dashObj;
  configObject["lineWidth"] = lineWidth;
  configObject["dotSize"] = dotSize;
  configObject["gapSize"] = gapSize;
}

void openGLGraphics::initialSettings() {
  backgroundColor = Qt::black;
  filename = "";
  perpectiveMode = false;
  lineColor = Qt::white;
  dotColor = Qt::white;
  dotObj = true;
  lineObj = true;
  squareObj = false;
  dashObj = false;
  lineWidth = 1.0f;
  dotSize = 1.0f;
  gapSize = 1.0f;
}
openGLGraphics::~openGLGraphics() {
  saveConfigSettings();
  writeToJsonFile();
}

void openGLGraphics::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void openGLGraphics::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void openGLGraphics::paintGL() {
  changeViewMode();
  changeBack();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  float far = fmax(fabs(object.z_max), fabs(object.z_min)) +
              fmax(fabs(object.y_max), fabs(object.y_min));
  //    float far = fabs(object.z_max) + fabs(object.y_max);
  // qDebug() << far;
  if (far < 5) {
    far = 5;
  }
  glTranslated(0, 0, -far);
  glRotated(xRot, 1, 0, 0);
  glRotated(yRot, 0, 1, 0);
  drawObj();
}

void openGLGraphics::drawObj() {
  if (dotObj || squareObj) {
    float r, g, b;
    qColorToRGB(dotColor, r, g, b);
    glColor3f(r, g, b);
    drawObjDot(0);
  }
  if (lineObj || dashObj) {
    float r, g, b;
    qColorToRGB(lineColor, r, g, b);
    glColor3f(r, g, b);
    drawObjLine(0);
  }
}

void openGLGraphics::drawObjDot(int ii) {
  glPointSize(dotSize);
  if (dotObj) glEnable(GL_POINT_SMOOTH);
  glBegin(GL_POINTS);
  for (int j = 0; j < object.vertices_count; j++) {
    double x = object.vertices[j].x;
    double y = object.vertices[j].y;
    double z = object.vertices[j].z;
    glVertex3d(x, y, z);
  }
  glEnd();
  glDisable(GL_POINT_SMOOTH);
}

void openGLGraphics::drawObjLine(int ii) {
  glLineWidth(lineWidth);
  if (dashObj) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(gapSize, 0xAAAA);  // if 1 Pattern: 1010 1010 1010 1010
  }

  for (int i = 0; i < object.facets_count; i++) {
    glBegin(GL_LINE_LOOP);
    for (int j = 0; j < object.facets[i].facet_vertices_count; j++) {
      int coor_id = object.facets[i].vertex_IDs[j];
      double x = object.vertices[coor_id].x;
      double y = object.vertices[coor_id].y;
      double z = object.vertices[coor_id].z;
      glVertex3d(x, y, z);
    }

    glEnd();
  }
  glDisable(GL_LINE_STIPPLE);
}

void openGLGraphics::qColorToRGB(const QColor &color, float &r, float &g,
                                 float &b) const {
  int red = color.red();
  int green = color.green();
  int blue = color.blue();
  r = normalizeColorValue(red, RGB_MIN, RGB_MAX);
  g = normalizeColorValue(green, RGB_MIN, RGB_MAX);
  b = normalizeColorValue(blue, RGB_MIN, RGB_MAX);
}

float openGLGraphics::normalizeColorValue(float val, float min,
                                          float max) const {
  return (val - min) / (max - min);
}

void openGLGraphics::changeBack() {
  float r, g, b, a = 1;
  qColorToRGB(backgroundColor, r, g, b);
  glClearColor(r, g, b, a);
}

void openGLGraphics::changeViewMode() {
  if (perpectiveMode == false) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, 1, 9999999);
    float value = 0.5 / object.y_max;
    glScalef(value, value, 1.0f);
  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 9999999);
  }
}

void openGLGraphics::setFileName() {
  qDebug() << filename;
  QByteArray ba = filename.toLocal8Bit();
  const char *fname = ba.data();
  int error = getGeometryInfo(fname, &object);
  if (error != OK) {
    structClean(&object);
  } else {
    normalizeObject();
  }
}
void openGLGraphics::normalizeObject() {
  double center_x = 0, center_y = 0, center_z = 0;
  for (int i = 0; i < object.vertices_count; i++) {
    center_x += object.vertices[i].x;
    center_y += object.vertices[i].y;
    center_z += object.vertices[i].z;
  }
  center_x /= object.vertices_count;
  center_y /= object.vertices_count;
  center_z /= object.vertices_count;
  for (int i = 0; i < object.vertices_count; i++) {
    object.vertices[i].x -= center_x;
    object.vertices[i].y -= center_y;
    object.vertices[i].z -= center_z;
  }
  object.x_max -= center_x;
  object.x_min -= center_x;
  object.z_max -= center_z;
  object.z_min -= center_z;
  object.y_max -= center_y;
  object.y_min -= center_y;
}

void openGLGraphics::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }
void openGLGraphics::mouseMoveEvent(QMouseEvent *mo) {
  xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}

void openGLGraphics::toScreen() {
  //    if(object.z_max > -2.0)
  //    {
  //        float max_dimension = fabs(object.y_max);
  //        float value = 2.0 + object.z_max + max_dimension;
  //        move_z(&object, -value);
  //        object.z_max -= value;
  //        object.z_min -= value;
  //    }
}
void openGLGraphics::toScreenOrtho() {
  //    float value = 0.5 / object.y_max;
  //    scale_model(&object, value);
  //    object.z_max *= value;
  //    object.z_min *= value;
  //    object.x_max *= value;
  //    object.x_min *= value;
  //    object.y_max *= value;
  //    object.y_min *= value;
}
void openGLGraphics::toScreenFrust() {
  //    float value = object.y_max / 0.5;
  //    scale_model(&object, value);
  //    object.z_max *= value;
  //    object.z_min *= value;
  //    object.x_max *= value;
  //    object.x_min *= value;
  //    object.y_max *= value;
  //    object.y_min *= value;
}
