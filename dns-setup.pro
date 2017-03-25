#------------------------------------------------------------------------
# dBase-Project 1.0
# RDP - Rapid Database Programming
#
# (c) 2015-2017 Jens Kallup
#------------------------------------------------------------------------
TEMPLATE = app
TARGET   = dns-setup
CONFIG  += release

QT = core gui widgets help network

PWD=$$system(pwd)

TOPDIR=$$PWD
SRCDIR=$${TOPDIR}/src
HDRDIR=$${SRCDIR}/inc

GENFOLDER =$${TOPDIR}/build/

TEMPLATE_DEPTH = 516

UI_DIR =$${TOPDIR}/.uic
MOC_DIR=$${TOPDIR}/.moc
OBJ_DIR=$${TOPDIR}/.obj
RCC_DIR=$${TOPDIR}/.res

DEFINES += BUILDTIME=\\\"$$system(date '+%H:%M:%S')\\\"
DEFINES += BUILDDATE=\\\"$$system(date '+%Y-%m-%d')\\\"

#----------------------------------------------------------------------
# if you would not use pch - pre-compiled-header, just remove -H block
#----------------------------------------------------------------------
QMAKE_CXXFLAGS += \
    -std=c++1y  \
    -Wno-unused-parameter \
    -Wno-unused-variable \
    -Wno-unused-local-typedefs \
    -Wno-unused-but-set-variable \
    -Wno-write-strings \
    -Wno-switch \
    -Wno-extra \
    -Wno-reorder \
    -Wno-multichar \
    -Wno-sign-compare \
    -Wunused-function \
    -Woverloaded-virtual -fpermissive \
    -ftemplate-depth=$${TEMPLATE_DEPTH} \
    -frtti -fexceptions \
    -I/usr/local/include \
    -I/usr/local/include/boost \
    -I$${TOPDIR}. -I$${SRCDIR} -I$${SRCDIR}/inc \
    -D__BYTE_ORDER=__LITTLE_ENDIAN \
    -DQT_DEPRECATED \
    -DQT_DISABLE_DEPRECATED_BEFORE

#dBaseHelp.target     = all
#dBaseHelp.commands   = @./source/tools/html2qch.sh
#dBaseHelp.depends    = FORCE

#QMAKE_EXTRA_TARGETS += dBaseHelp

INCLUDEPATH += \
    /usr/local/include \
    $${TOPDIR}/.uic \
    $${SRCDIR}/ \
    $${SRCDIR}/inc \
    /usr/include

SOURCES += \
    $${SRCDIR}/main.cc \
    $${SRCDIR}/mainwindow.cc \
    $${SRCDIR}/label.cc \
    $${SRCDIR}/thread.cc \
    $${SRCDIR}/rmiserver.cc

HEADERS += \
    $${SRCDIR}/mainwindow.h \
    $${SRCDIR}/label.h \
    $${SRCDIR}/thread.h \
    $${SRCDIR}/rmiserver.h

#FORMS   += \

#RESOURCES += \
#    $${SRCDIR}/dbase/icons.qrc \
#    source/dbase/icons.qrc

DISTFILES +=

LIBS += -L"/usr/local/lib64" -lstdc++
