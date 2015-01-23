QT       += core gui webkit network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtSample
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
        src/main.cpp\
        src/MainWindow.cpp \

HEADERS  += \
        src/MainWindow.hpp \

FORMS    += \
        ui/MainWindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../liboauth2cpp/release/ -loauth2cpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../liboauth2cpp/debug/ -loauth2cpp
else:unix: LIBS += -L$$OUT_PWD/../../liboauth2cpp/ -loauth2cpp

INCLUDEPATH += $$PWD/../../liboauth2cpp/include
DEPENDPATH += $$PWD/../../liboauth2cpp
