QT += core gui multimedia multimediawidgets
greaterThan(QT_MAJOR_VERSION, 5): QT += multimediawidgets
CONFIG += c++17

SOURCES += main.cpp \
           mainwindow.cpp \
           motiondetector.cpp \
           cameramanager.cpp

HEADERS += \
    mainwindow.h \
    motiondetector.h \
    cameramanager.h

FORMS += \
    mainwindow.ui

RESOURCES += resources.qrc

DISTFILES += \
    README.md
