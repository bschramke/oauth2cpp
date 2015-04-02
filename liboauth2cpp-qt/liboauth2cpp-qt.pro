QT       += core gui webkit network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = oauth2cpp-qt
TEMPLATE = lib

VERSION = 0.0.1

DEFINES += OAUTH2CPP_QT_LIBRARY
QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += $$PWD/include

SOURCES += \
    src/QtHttpResponse.cpp \
    src/QtHttpRequest.cpp \
    src/QtHttpClient.cpp

HEADERS += \
    include/oauth2cpp/qt/QtHttpResponse.hpp \
    include/oauth2cpp/qt/QtHttpRequest.hpp \
    include/oauth2cpp/qt/QtHttpClient.hpp


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../liboauth2cpp/release/ -loauth2cpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../liboauth2cpp/debug/ -loauth2cpp
else:unix: LIBS += -L$$OUT_PWD/../liboauth2cpp/ -loauth2cpp

INCLUDEPATH += $$PWD/../liboauth2cpp/include
DEPENDPATH += $$PWD/../liboauth2cpp
