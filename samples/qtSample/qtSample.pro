QT       += core gui webkit network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtSample
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

DEFINES += GOOGLE_CLIENT_ID=\\\"YOUR GOOGLE CLIENT ID HERE\\\"
DEFINES += GOOGLE_CLIENT_SECRET=\\\"YOUR GOOGLE CLIENT SECRET HERE\\\"

SOURCES += \
        src/main.cpp\
        src/MainWindow.cpp \
        src/QtHttpRequest.cpp \
        src/QtHttpClient.cpp \
        src/QtHttpResponse.cpp

HEADERS  += \
        src/MainWindow.hpp \
        src/QtHttpRequest.hpp \
        src/QtHttpClient.hpp \
        src/QtHttpResponse.hpp

FORMS    += \
        ui/MainWindow.ui

unix|win32: LIBS += -L/usr/local/lib -lnetwork-uri -lboost_system -lboost_filesystem

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../liboauth2cpp/release/ -loauth2cpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../liboauth2cpp/debug/ -loauth2cpp
else:unix: LIBS += -L$$OUT_PWD/../../liboauth2cpp/ -loauth2cpp

INCLUDEPATH += $$PWD/../../liboauth2cpp/include
DEPENDPATH += $$PWD/../../liboauth2cpp
