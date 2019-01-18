#-------------------------------------------------
#
# Project created by QtCreator 2016-11-07T16:06:13
#
#-------------------------------------------------

QT       += core gui sql concurrent svg xml multimedia serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cribtrak
TEMPLATE = app

#LIBS += "hidapi.lib"

#QT += testlib
#DEFINES += TRAK_TESTKEYS

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

SOURCES += main.cpp \
    mainview.cpp \
    maincontroller.cpp \
    datamanager.cpp \
    guestscreen.cpp \
    userscreen.cpp \
    selecttail.cpp \
    keypad.cpp \
    vkey.cpp \
    adminscreen.cpp \
    about.cpp \
    customersettings.cpp \
    databasesetup.cpp \
    disconnected.cpp \
    employeelist.cpp \
    setupcabinet.cpp \
    taillist.cpp \
    employeedetail.cpp \
    toolstablemodel.cpp \
    dbmaintenance.cpp \
    progressbar.cpp \
    systemsettings.cpp \
    tooloutform.cpp \
    accessdenied.cpp \
    dashboard.cpp \
    tooladmin.cpp \
    logviewer.cpp \
    openalarmmessage.cpp \
    taildetail.cpp \
    tooldetail.cpp \
    contactform.cpp \
    smtp.cpp \
    keyboard.cpp \
    cabtooldetail.cpp \
    loadingscreen.cpp \
    version.cpp \
    powerstatus.cpp \
    toolsmanager.cpp \
    scannermanager.cpp \
    barcodescanner.cpp \
    cribtooldetail.cpp \
    scanneradmin.cpp \
    toolfinder.cpp \
    multicolumnsortfilterproxymodel.cpp \
    csvreader.cpp \
    csvwriter.cpp

HEADERS  += \
    mainview.h \
    maincontroller.h \
    datamanager.h \
    guestscreen.h \
    userscreen.h \
    selecttail.h \
    keypad.h \
    vkey.h \
    adminscreen.h \
    about.h \
    customersettings.h \
    databasesetup.h \
    disconnected.h \
    employeelist.h \
    setupcabinet.h \
    taillist.h \
    employeedetail.h \
    toolstablemodel.h \
    dbmaintenance.h \
    progressbar.h \
    systemsettings.h \
    tooloutform.h \
    accessdenied.h \
    dashboard.h \
    tooladmin.h \
    logviewer.h \
    openalarmmessage.h \
    taildetail.h \
    tooldetail.h \
    contactform.h \
    smtp.h \
    trakcore.h \
    keyboard.h \
    cabtooldetail.h \
    loadingscreen.h \
    version.h \
    powerstatus.h \
    toolsmanager.h \
    scannermanager.h \
    barcodescanner.h \
    cribtooldetail.h \
    scanneradmin.h \
    toolfinder.h \
    multicolumnsortfilterproxymodel.h \
    csvreader.h \
    csvwriter.h

FORMS += \
    guestscreen.ui \
    userscreen.ui \
    selecttail.ui \
    adminscreen.ui \
    about.ui \
    customersettings.ui \
    databasesetup.ui \
    disconnected.ui \
    employeelist.ui \
    setupcabinet.ui \
    systemsettings.ui \
    taillist.ui \
    employeedetail.ui \
    dbmaintenance.ui \
    tooloutform.ui \
    accessdenied.ui \
    dashboard.ui \
    tooladmin.ui \
    logviewer.ui \
    openalarmmessage.ui \
    taildetail.ui \
    tooldetail.ui \
    contactform.ui \
    keyboard.ui \
    cabtooldetail.ui \
    loadingscreen.ui \
    toolsmanager.ui \
    cribtooldetail.ui \
    scanneradmin.ui \
    toolfinder.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    Database/qkabmaster.sql \
    trak.ini

