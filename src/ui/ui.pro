QT       += core gui
QT += openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../c_code/sources/01_getGeometryInfo.c \
    ../c_code/sources/02_getComponentsCount.c \
    ../c_code/sources/03_getComponents.c \
    ../c_code/sources/04_getVertex.c \
    ../c_code/sources/05_getFacet.c \
    ../c_code/sources/06_getRange.c \
    ../c_code/sources/07_structClean.c \
    ../c_code/sources/affine.c \
    main.cpp \
    mainwindow.cpp \
    openglgraphics.cpp

HEADERS += \
    ../c_code/3D_viewer.h \
    ../c_code/sources/model_loading.h \
    mainwindow.h \
    openglgraphics.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../icons/home.png \
    ../models/Energy_rocket.obj \
    ../models/Skull_v3.obj \
    ../models/simple_cube.obj \
    ../models/skull.obj \
    ../models/teapot.obj \
    ../models/teddy.obj \
    ../models/woman.obj \

RESOURCES += \
    resources.qrc
