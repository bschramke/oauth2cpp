QT       += core gui webkit network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtSample
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

DEFINES += OAUTH_CLIENT_ID=\\\"YOUR_OAUTH_CLIENT_ID\\\"
DEFINES += OAUTH_CLIENT_SECRET=\\\"YOUR_OAUTH_CLIENT_SECRET\\\"

SOURCES += \
        src/main.cpp\
        src/MainWindow.cpp \

HEADERS  += \
        src/MainWindow.hpp \

FORMS    += \
        ui/MainWindow.ui

unix|win32: LIBS += -L/usr/local/lib -lboost_system -lboost_filesystem

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../liboauth2cpp/release/ -loauth2cpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../liboauth2cpp/debug/ -loauth2cpp
else:unix: LIBS += -L$$OUT_PWD/../../liboauth2cpp/ -loauth2cpp

INCLUDEPATH += $$PWD/../../liboauth2cpp/include
DEPENDPATH += $$PWD/../../liboauth2cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../liboauth2cpp-qt/release/ -loauth2cpp-qt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../liboauth2cpp-qt/debug/ -loauth2cpp-qt
else:unix: LIBS += -L$$OUT_PWD/../../liboauth2cpp-qt/ -loauth2cpp-qt

INCLUDEPATH += $$PWD/../../liboauth2cpp-qt/include
DEPENDPATH += $$PWD/../../liboauth2cpp-qt

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../externals/cpp-netlib-uri/release/ -lnetwork-uri
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../externals/cpp-netlib-uri/debug/ -lnetwork-uri
else:unix: LIBS += -L$$OUT_PWD/../../externals/cpp-netlib-uri/ -lnetwork-uri

INCLUDEPATH += $$PWD/../../externals/cpp-netlib-uri
DEPENDPATH += $$PWD/../../externals/cpp-netlib-uri

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../externals/cpp-netlib-uri/release/network-uri.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../externals/cpp-netlib-uri/debug/network-uri.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../externals/cpp-netlib-uri/libnetwork-uri.a
