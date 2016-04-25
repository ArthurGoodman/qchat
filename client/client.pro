QT += core gui widgets network

TARGET = client
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    ../common/console.cpp \
    ../common/iconsole.cpp

HEADERS  += mainwindow.h \
    ../common/console.h \
    ../common/iconsole.h
