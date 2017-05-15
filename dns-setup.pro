#------------------------------------------------------------------------
# DVE Internet Cafe Project 1.0
#
# (c) 2015-2017 Jens Kallup
#------------------------------------------------------------------------
TEMPLATE = app
TARGET   = server
CONFIG  += release

QT += core gui widgets sql help network printsupport \
      qml quick webenginewidgets

qtHaveModule(uitools):!embedded: QT += uitools
else: DEFINES += QT_NO_UITOOLS

PWD=$$system(pwd)

TOPDIR=$${PWD}
SRCDIR=$${TOPDIR}/src
HDRDIR=$${SRCDIR}/inc

GENFOLDER =$${TOPDIR}/build/

TEMPLATE_DEPTH = 516

UI_DIR =$${TOPDIR}/.uic
MOC_DIR=$${TOPDIR}/.moc
OBJECTS_DIR=$${TOPDIR}/.obj
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
    /home/jens/Qt/5.8/gcc_64/include \
    /usr/local/include \
    $${TOPDIR}/.uic \
    $${SRCDIR}/ \
    $${SRCDIR}/inc \
    /usr/include

SOURCES += \
    $${SRCDIR}/main.cc \
    $${SRCDIR}/mainwindow.cc \
    $${SRCDIR}/menu.cc \
    $${SRCDIR}/ping.cc \
    $${SRCDIR}/label.cc \
    $${SRCDIR}/data.cc \
    $${SRCDIR}/thread.cc \
    $${SRCDIR}/utils.cc \
    $${SRCDIR}/cafemessage.cc \
    $${SRCDIR}/rmiserver.cc

SOURCES += \
    $${SRCDIR}/autosaver.cc \
    $${SRCDIR}/bookmarks.cc \
    $${SRCDIR}/browserapplication.cc \
    $${SRCDIR}/browsermainwindow.cc \
    $${SRCDIR}/chasewidget.cc \
    $${SRCDIR}/downloadmanager.cc \
    $${SRCDIR}/edittableview.cc \
    $${SRCDIR}/edittreeview.cc \
    $${SRCDIR}/featurepermissionbar.cc\
    $${SRCDIR}/fullscreennotification.cc \
    $${SRCDIR}/history.cc \
    $${SRCDIR}/modelmenu.cc \
    $${SRCDIR}/printtopdfdialog.cc \
    $${SRCDIR}/savepagedialog.cc \
    $${SRCDIR}/searchlineedit.cc \
    $${SRCDIR}/settings.cc \
    $${SRCDIR}/squeezelabel.cc \
    $${SRCDIR}/tabwidget.cc \
    $${SRCDIR}/toolbarsearch.cc \
    $${SRCDIR}/urllineedit.cc \
    $${SRCDIR}/webview.cc \
    $${SRCDIR}/xbel.cc
    
HEADERS += \
    $${SRCDIR}/mainwindow.h \
    $${SRCDIR}/menu.h \
    $${SRCDIR}/label.h \
    $${SRCDIR}/data.h \
    $${SRCDIR}/thread.h \
    $${SRCDIR}/utils.h \
    $${SRCDIR}/cafemessage.h \
    $${SRCDIR}/rmiserver.h


HEADERS += \
    $${SRCDIR}/autosaver.h \
    $${SRCDIR}/bookmarks.h \
    $${SRCDIR}/browserapplication.h \
    $${SRCDIR}/browsermainwindow.h \
    $${SRCDIR}/chasewidget.h \
    $${SRCDIR}/downloadmanager.h \
    $${SRCDIR}/edittableview.h \
    $${SRCDIR}/edittreeview.h \
    $${SRCDIR}/featurepermissionbar.h\
    $${SRCDIR}/fullscreennotification.h \
    $${SRCDIR}/history.h \
    $${SRCDIR}/modelmenu.h \
    $${SRCDIR}/printtopdfdialog.h \
    $${SRCDIR}/savepagedialog.h \
    $${SRCDIR}/searchlineedit.h \
    $${SRCDIR}/settings.h \
    $${SRCDIR}/squeezelabel.h \
    $${SRCDIR}/tabwidget.h \
    $${SRCDIR}/toolbarsearch.h \
    $${SRCDIR}/urllineedit.h \
    $${SRCDIR}/webview.h \
    $${SRCDIR}/xbel.h
    
FORMS += \
    $${SRCDIR}/addbookmarkdialog.ui \
    $${SRCDIR}/bookmarks.ui \
    $${SRCDIR}/cookies.ui \
    $${SRCDIR}/cookiesexceptions.ui \
    $${SRCDIR}/downloaditem.ui \
    $${SRCDIR}/downloads.ui \
    $${SRCDIR}/history.ui \
    $${SRCDIR}/passworddialog.ui \
    $${SRCDIR}/printtopdfdialog.ui \
    $${SRCDIR}/proxy.ui \
    $${SRCDIR}/savepagedialog.ui \
    $${SRCDIR}/settings.ui

RESOURCES += src/data.qrc src/htmls.qrc

DISTFILES += \
    $${TOPDIR}/app.ini

LIBS += -L"/home/jens/Qt/5.8/gcc_64/lib" -lstdc++
