QT       -= core gui

TARGET = network-uri
TEMPLATE = lib
CONFIG += staticlib

VERSION = 0.0.1

DEFINES += NETWORK_URI_LIBRARY
QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += $$PWD/src

SOURCES += \
    src/uri.cpp \
    src/uri_errors.cpp \
    src/uri_builder.cpp \
    src/detail/uri_resolve.cpp \
    src/detail/uri_percent_encode.cpp \
    src/detail/uri_parse.cpp \
    src/detail/uri_parse_authority.cpp \
    src/detail/uri_normalize.cpp

HEADERS += \
    src/network/uri.hpp \
    src/network/uri/uri.hpp \
    src/network/uri/uri_io.hpp \
    src/network/uri/uri_errors.hpp \
    src/network/uri/uri_builder.hpp \
    src/network/uri/config.hpp \
    src/network/uri/detail/translate.hpp \
    src/network/uri/detail/encode.hpp \
    src/network/uri/detail/decode.hpp \
    src/detail/uri_resolve.hpp \
    src/detail/uri_percent_encode.hpp \
    src/detail/uri_parse.hpp \
    src/detail/uri_parse_authority.hpp \
    src/detail/uri_normalize.hpp

unix|win32: LIBS += -lboost_system -l boost_filesystem
