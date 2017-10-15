#-------------------------------------------------
#
# Project created by QtCreator 2016-12-05T15:10:52
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    datalevel.cpp \
    linkandtest.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    datalevel.h \
    linkandtest.h

FORMS    += mainwindow.ui \
    dialog.ui \
    linkandtest.ui

RESOURCES +=

addFiles.sources =p.db
addFiles.path = .
DEPLOYMENT += addFiles

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/assets/qqq.txt

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
