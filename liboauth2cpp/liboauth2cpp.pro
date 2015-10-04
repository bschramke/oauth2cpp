QT       -= core gui

TARGET = oauth2cpp
TEMPLATE = lib

VERSION = 0.0.1

DEFINES += OAUTH2CPP_LIBRARY
QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/../externals/jsonxx
INCLUDEPATH += $$PWD/../externals/cpp-netlib-uri

SOURCES += \
    ../externals/jsonxx/jsonxx.cc \
    src/ClientConfiguration.cpp \
    src/Client.cpp \
    src/BearerToken.cpp \
    src/DefaultStorage.cpp \
    src/TokenFactory.cpp

HEADERS += \
    ../externals/jsonxx/jsonxx.h \
    include/oauth2cpp/Version.hpp \
    include/oauth2cpp/OAuth2.hpp \
    include/oauth2cpp/ClientConfiguration.hpp \
    include/oauth2cpp/Client.hpp \
    include/oauth2cpp/TokenInfo.hpp \
    include/oauth2cpp/TokenStorage.hpp \
    include/oauth2cpp/BearerToken.hpp \
    include/oauth2cpp/DefaultStorage.hpp \
    include/oauth2cpp/HttpClient.hpp \
    include/oauth2cpp/HttpRequest.hpp \
    include/oauth2cpp/HttpResponse.hpp \
    include/oauth2cpp/TokenFactory.hpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../externals/cpp-netlib-uri/release/ -lnetwork-uri
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../externals/cpp-netlib-uri/debug/ -lnetwork-uri
else:unix: LIBS += -L$$OUT_PWD/../externals/cpp-netlib-uri/ -lnetwork-uri
