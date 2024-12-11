QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    constantcell.cpp \
    conwayCell.cpp \
    enemyCell.cpp \
    gameConway.cpp \
    gamewindow.cpp \
    guns.cpp \
    main.cpp \
    myVector.cpp \
    nukeCell.cpp \
    oscillators.cpp \
    shape.cpp \
    spaceships.cpp \
    stillFigure.cpp

HEADERS += \
	constantcell.h \
	conwayCell.h \
	enemyCell.h \
	gameConway.h \
	gamewindow.h \
	guns.h \
	myVector.h \
	nukeCell.h \
	oscillators.h \
	shape.h \
	spaceships.h \
	stillFigure.h

FORMS += \
	gamewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
