QT += core gui widgets network

TARGET = client
TEMPLATE = app

SOURCES += main.cpp \
    ../common/console.cpp \
    ../common/iconsole.cpp \
    connectdialog.cpp \
    client.cpp

HEADERS  += \
    ../common/console.h \
    ../common/iconsole.h \
    connectdialog.h \
    client.h

FORMS += \
    connectdialog.ui
