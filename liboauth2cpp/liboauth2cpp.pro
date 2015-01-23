QT       -= core gui

TARGET = oauth2cpp
TEMPLATE = lib

VERSION = 0.0.1

DEFINES += OAUTH2CPP_LIBRARY
QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += $$PWD/include

SOURCES += \

HEADERS += \
    include/oauth2cpp/Version.hpp \
    include/oauth2cpp/OAuth2.hpp
