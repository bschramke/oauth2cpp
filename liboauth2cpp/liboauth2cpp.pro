QT       -= core gui

TARGET = oauth2cpp
TEMPLATE = lib

VERSION = 0.0.1

DEFINES += OAUTH2CPP_LIBRARY
QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += $$PWD/include

SOURCES += \
    src/ClientConfiguration.cpp \
    src/Client.cpp \

HEADERS += \
    include/oauth2cpp/Version.hpp \
    include/oauth2cpp/OAuth2.hpp \
    include/oauth2cpp/ClientConfiguration.hpp \
    include/oauth2cpp/Client.hpp \
    include/oauth2cpp/HttpClient.hpp \
    include/oauth2cpp/HttpRequest.hpp \
    include/oauth2cpp/HttpResponse.hpp \

unix|win32: LIBS += -L/usr/local/lib -lnetwork-uri
