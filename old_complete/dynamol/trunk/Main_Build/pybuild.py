#!/usr/bin/python

import os
import sys

j=2

mode ="NONE"
install = 0
if ( len(sys.argv) == 3 and sys.argv[2] == "INSTALL" ):
	install = 1

JamDir = "Jamfiles/"
if ( len(sys.argv) == 4 and sys.argv[3] == "FC3"):
   JamDir = "Jamfiles/FC3/"
if (sys.argv[1] == "LINUX"):
	mode = "LINUX"
	os.environ['BOOST_ROOT'] = '/home/jfurr/boost_gcc'
	os.environ['QTDIR'] = '/usr/lib/qt-3.4'
        copyString = "cp " + JamDir +"/";
        print copyString
	os.system(copyString + "Jamfile_dynabase_linux dynabase/Jamfile.v2")
	os.system(copyString + "Jamfile_dynatype_linux dynatype/Jamfile.v2")
	os.system(copyString + "Jamfile_dynacomp_linux dynacomp/Jamfile.v2")
	os.system(copyString + "Jamfile_convert_linux convert/Jamfile.v2")
	os.system(copyString + "Jamfile_descriptors_linux descriptors/Jamfile.v2")
	os.system(copyString + "Jamfile_dynaprint_linux dynaprint/Jamfile.v2")
	os.system(copyString + "Jamfile_dynamol_linux dynamol/Jamfile.v2")
        os.system(copyString + "python_dynacomp_linux_Jamfile.v2 python/dynacomp/Jamfile.v2")	
        os.system(copyString + "python_dynamol_linux_Jamfile.v2 python/dynamol/Jamfile.v2")

	print "Starting Linux Build"

if (sys.argv[1] == "WINDOWS"):
	#os.environ['BOOST_ROOT'] = '/home/dynamol/boost_gcc'
	os.environ['QTDIR'] = 'D:/Qt/3.3.5'
	os.system("cp Jamfiles/Jamfile_dynabase_windows dynabase/Jamfile.v2")
	os.system("cp Jamfiles/Jamfile_dynatype_windows dynatype/Jamfile.v2")
	os.system("cp Jamfiles/Jamfile_dynacomp_windows dynacomp/Jamfile.v2")
	os.system("cp Jamfiles/Jamfile_convert_windows convert/Jamfile.v2")
	os.system("cp Jamfiles/Jamfile_descriptors_windows descriptors/Jamfile.v2")
	os.system("cp Jamfiles/Jamfile_dynaprint_windows dynaprint/Jamfile.v2")
	os.system("cp Jamfiles/Jamfile_dynamol_windows dynamol/Jamfile.v2")

	mode = "WINDOWS"

if (sys.argv[1] == "INSTALL"):
	mode = "INSTALL"


#os.system("bjam --v2 release --clean")

print "STARTING INSTALL BUILD SECTION"
os.system("rm -rf ../dynamol/bin/dynamol-linux")
os.system("rm -rf ../dynamol/PyModules/*")

#### THIS IS THE MAIN BUILD COMMND ####
os.system("bjam --v2 release -d2 -j" + str(j) + " define=" + mode)

if (mode == "WINDOWS"):
	print "Still in the windws build"
	os.system("cp hold/dynamol.exe ../dynamol/bin/dynamol.exe")
	os.system("cp dynamol/bin/msvc/release/threading-multi/dynamol.lib ./libs")

	## BUILD THE DYNAMOL.PYD MODULE
	os.system("cp Jamfiles/python_dynamol_windows_Jamfile.v2 python/dynamol/Jamfile.v2")
	os.chdir("python/dynamol")
	os.system("bjam --v2 release -j" + str(j) + " define=" + mode)
	os.system("cp bin/msvc/release/dynamol.dll ../../../dynamol/bin/dynamol.pyd")

	## BUILD THE DYNCOMP.PYD MODULE
	os.chdir("../dynacomp")
	os.system("ls")
	os.system("cp ../../Jamfiles/python_dynacomp_windows_Jamfile.v2 ./Jamfile.v2")
	os.system("bjam --v2 release -j" + str(j) + " define=" + mode)
	os.system("cp bin/msvc/release/threading-multi/dynacomp.dll ../../../dynamol/bin/dynacomp.pyd")

if (mode == "LINUX"):
	os.system("cp hold/dynamol ../dynamol/bin/dynamol-linux")
	os.system("ls")
	print "Check for Dyamol Precense"
#        i = raw_input();
#        quit
"""
	print "Bulding PyDynacompExtension"
	os.system("cp Jamfiles/pyDynacompBuilderLinux.sh python/dynacomp")
	os.system("cp Jamfiles/pyDynamolBuilderLinux.sh python/dynamol")

	print "Building PyDynacomp"
	os.chdir("python/dynacomp")
	os.system("touch *; sh ./pyDynacompBuilderLinux.sh")
	os.chdir("../../")

	print "Building PyDynamol"
	os.chdir("python/dynamol")
	os.system("touch *; sh ./pyDynamolBuilderLinux.sh")
	os.chdir("../../")
	
	os.chdir("installer/bin")
	os.system("./buildDist")
"""
print "Your shiney new build has be put up on the web server"
