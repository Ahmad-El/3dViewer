#include "openglgraphics.h"

openGLGraphics::openGLGraphics(QWidget *parent):QOpenGLWidget (parent)
{
    backgroundColor = Qt::black;
    setFileName();
    initLineDotSet();
    perpectiveMode = false;

}
void openGLGraphics::initLineDotSet(){
    lineColor = Qt::white;
    dotColor = Qt::white;
    dotObj = true;
    lineObj = true;
    squareObj = false;
    dashObj = false;
    lineWidth = 1.0f;
    dotSize = 1.0f;

}

void openGLGraphics::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
}

void openGLGraphics::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void openGLGraphics::paintGL()
{
    changeViewMode();
    changeBack();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float far = fabs(object.z_max) + fabs(object.y_max);
    if(far < 5) {
        far = 5;
    }
    glTranslatef(0,0, -far);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    drawObj();
}

void openGLGraphics::drawObj(){
    for(int i = 0; i < object.facets_count; i ++ ){
        if(dotObj || squareObj) {
            float r, g, b;
            qColorToRGB(dotColor, r, g, b);
            glColor3f(r, g, b);
            drawObjDot(i);
        }
        if(lineObj || dashObj) {
            float r, g, b;
            qColorToRGB(lineColor, r, g, b);
            glColor3f(r, g, b);
            drawObjLine(i);
        }
    }
}


void openGLGraphics::drawObjDot(int i){
    glPointSize(dotSize);
    if(dotObj) glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    for(int j = 0; j < object.facets[i].facet_vertices_count; j++){
        int coor_id = object.facets[i].vertex_IDs[j];
        double x = object.vertices[coor_id].x;
        double y = object.vertices[coor_id].y;
        double z = object.vertices[coor_id].z;
        glVertex3d(x, y, z);
    }
    glEnd();
    glDisable(GL_POINT_SMOOTH);
}

void openGLGraphics::drawObjLine(int i){
    glLineWidth(lineWidth);
    if(dashObj){
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(4, 0xAAAA);  // if 1 Pattern: 1010 1010 1010 1010
}


    glBegin(GL_LINE_LOOP);
    for(int j = 0; j < object.facets[i].facet_vertices_count; j++){
        int coor_id = object.facets[i].vertex_IDs[j];
        double x = object.vertices[coor_id].x;
        double y = object.vertices[coor_id].y;
        double z = object.vertices[coor_id].z;
        glVertex3d(x, y, z);
    }
    glEnd();
    glDisable(GL_LINE_STIPPLE);
}


void openGLGraphics::qColorToRGB(const QColor &color, float &r, float &g, float &b) const{
    int red = color.red();
    int green = color.green();
    int blue = color.blue();
    r = normalizeColorValue(red, RGB_MIN, RGB_MAX);
    g = normalizeColorValue(green, RGB_MIN, RGB_MAX);
    b = normalizeColorValue(blue, RGB_MIN, RGB_MAX);
}

float openGLGraphics::normalizeColorValue(float val, float min, float max) const{
    return (val - min ) / (max - min);
}

void openGLGraphics::changeBack()
{
        float r, g, b, a = 1;
        qColorToRGB(backgroundColor, r, g, b);
        glClearColor(r, g, b, a);
}

void openGLGraphics::changeViewMode()
{
    if(perpectiveMode == false){
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1, 1, -1, 1, 1, 999);
        float value = 0.5 / object.y_max;
        glScalef(value, value, 1.0f);
    } else {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-1, 1, -1, 1, 1, 999);
    }
}

void openGLGraphics::setFileName(){
    QByteArray ba = filename.toLocal8Bit();
    const char *fname = ba.data();
    int error = OK;
    error = getGeometryInfo(fname, &object);
    normalizeObject();
    error ++;
}
void openGLGraphics::normalizeObject(){
    double center_x = 0, center_y = 0, center_z = 0;
    for (int i = 0; i < object.vertices_count; i++){
        center_x += object.vertices[i].x;
        center_y += object.vertices[i].y;
        center_z += object.vertices[i].z;
    }
    center_x /= object.vertices_count;
    center_y /= object.vertices_count;
    center_z /= object.vertices_count;
    for (int i = 0; i < object.vertices_count; i++){
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

void openGLGraphics::mousePressEvent(QMouseEvent* mo) {
    mPos = mo->pos();
}
void openGLGraphics::mouseMoveEvent(QMouseEvent* mo) {
    xRot = 1 / M_PI * (mo->pos().y() -mPos.y());
    yRot = 1 / M_PI * (mo->pos().x() -mPos.x());
    update();

}

void openGLGraphics::toScreen(){
//    if(object.z_max > -2.0)
//    {
//        float max_dimension = fabs(object.y_max);
//        float value = 2.0 + object.z_max + max_dimension;
//        move_z(&object, -value);
//        object.z_max -= value;
//        object.z_min -= value;
//    }

}
void openGLGraphics::toScreenOrtho(){
//    float value = 0.5 / object.y_max;
//    scale_model(&object, value);
//    object.z_max *= value;
//    object.z_min *= value;
//    object.x_max *= value;
//    object.x_min *= value;
//    object.y_max *= value;
//    object.y_min *= value;
}
void openGLGraphics::toScreenFrust(){
//    float value = object.y_max / 0.5;
//    scale_model(&object, value);
//    object.z_max *= value;
//    object.z_min *= value;
//    object.x_max *= value;
//    object.x_min *= value;
//    object.y_max *= value;
//    object.y_min *= value;
}


