TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    main.cpp \
    TokenInfoTest.cpp \
    TokenStorageTest.cpp

HEADERS += \
    TestConstants.h \
    TokenInfoTest.hpp \
    TokenStorageTest.hpp

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += cppunit

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../release/ -loauth2cpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../debug/ -loauth2cpp
else:unix: LIBS += -L$$OUT_PWD/../ -loauth2cpp

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/..
