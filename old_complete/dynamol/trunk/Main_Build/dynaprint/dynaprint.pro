######################################################################
# Automatically generated by qmake (2.01a) Thu Oct 11 08:24:43 2007
######################################################################

TEMPLATE = app
TARGET = /home/jfurr/dynamol/bin/dynaprint-linux 
DEPENDPATH += .
INCLUDEPATH += . ../dynabase ../dynatype ../dynacomp
LIBS    = -L../dynabase -ldynabase -L../dynatype -ldynatype -L../convert -lconvert -L../dynacomp -ldynacomp
DEFINES += LINUX
# Input
HEADERS += gaffsig.h 
SOURCES += dynaprint.cpp \
           gaffsig.cpp 
