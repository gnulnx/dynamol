######################################################################
# Automatically generated by qmake (2.01a) Thu Jan 24 07:31:18 2008
######################################################################

TEMPLATE = lib
TARGET = 	molview.so

QT += opengl

CONFIG += dll release x86 
DEFINES += BOOST_PYTHON_DYNAMIC_LIB
DEPENDPATH += .

###########################################
####### OS X BUILD SECTION ################
###########################################
macx {

	DYNAMOL_HOME = /Users/jfurr/Dynamol/

	INCLUDEPATH += . /Library/Frameworks/Python.framework/Versions/2.5/include/python2.5 \
		/Library/Frameworks/Python.framework/Versions/2.5/lib/python2.5/config \
		/Users/jfurr/Boost/boost/python \ 
		/Users/jfurr/Boost/boost \
		/Users/jfurr/Boost


	LIBS += -lutil -lpthread -ldl \
	/Library/Frameworks/Python.framework/Versions/2.5/Python \
	-L/Library/Frameworks/Python.framework/Versions/2.5/lib \
	-L/Library/Frameworks/Python.framework/Versions/2.5/lib/python2.5/config \
	/Users/jfurr/Boost/bin.v2/libs/python/build/darwin/debug/libboost_python-d-1_34_1.dylib \
	$$DYNAMOL_HOME/dynamol/*.o

}

############################################
######## LINUX BUILD SECTION ###############
############################################
linux-g++ {
	DYNAMOL_HOME = /home/jfurr/New_Build/
	INCLUDEPATH += . $$DYNAMOL_HOME/usr/local/include/python2.5 \
                $$DYNAMOL_HOME/usr/local/include/python2.5/config \
                $$DYNAMOL_HOME/boost_1_34_1/boost/python \
                $$DYNAMOL_HOME/boost_1_34_1/boost \
                $$DYNAMOL_HOME/boost_1_34_1

	LIBS += -lutil -lpthread -ldl \
        $$DYNAMOL_HOME/usr/local/lib/python2.5/config/libpython2.5.a \
        $$DYNAMOL_HOME/usr/local/lib/libboost_python-gcc41-d-1_34_1.so.1.34.1 \
	$$DYNAMOL_HOME/Dynamol/dynamol/*.o
}

# Input
SOURCES += 	*.cpp
