TEMPLATE = subdirs

SUBDIRS += \
    externals/cpp-netlib-uri \
    liboauth2cpp \
    liboauth2cpp-qt \
    samples \
    tests.pro

liboauth2cpp-qt.depends = liboauth2cpp
