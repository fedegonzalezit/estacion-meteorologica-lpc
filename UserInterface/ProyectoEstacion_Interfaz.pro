#-------------------------------------------------
#
# Project created by QtCreator 2016-10-20T15:22:58
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProyectoEstacion_Interfaz
TEMPLATE = app

//RC_FILE = myappico.ico
SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    historial.cpp \
    memoria.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    historial.h \
    memoria.h

FORMS    += \
    dialog.ui \
    mainwindow.ui \
    historial.ui \
    memoria.ui

RESOURCES += \
    imagenes.qrc
