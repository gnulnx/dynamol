#!/bin/sh

echo $1
echo $2
if [ $2 == "win_console" ];
then
	cd $1
	
	for i in dynabase convert dynatype dynacomp descriptors dynaprint dynamol
	do
		cp ../Windows_Jam_console/$i/Jam* $i/
		cp ../Windows_Jam_console/Jamroot ./
	done

	echo "Now open up cmd.exe and run bjam --v2 release -j5
	#bjam --v2 release -j5
fi

if [ $2 == "win_gui" ];
then
 	echo "Yep you are here"
	cd $1
	ls  	
	for i in dynabase convert dynatype dynacomp descriptors dynaprint dynamol
	do
		cp ../Windows_Jam_gui/$i/Jam* $i/
		cp ../Windows_Jam_gui/Jamroot ./
	done

	echo "Now Open up the cmd.exe and run bjam --v2 relaese -j5
	#bjam --v2 release -j5

fi

if [ $2 == "Linux" ];
then
	echo "You are here"
	#export BOOST_ROOT=/home/dynamol/boost_gcc
	export QTDIR=/usr/lib/qt-3.4
        cd $1

	for i in dynabase convert dynatype dynacomp descriptors dynaprint dynamol
        do
				echo "cp ../Linux_Jam/$i/Jam* $i"
                cp ../Linux_Jam/$i/Jam* $i/
                cp ../Linux_Jam/Jamroot ./
        done

     	for i in dynabase convert dynatype dynacomp descriptors dynaprint dynamol
        do
		cd $i
		rm -rf bin/gcc
		bjam --v2 release -j5
		cd ../
	done

	cp dynamol/bin/gcc/release/threading-multi/dynamol ../dynamol/bin/dynamol-linux
        cd installer/bin
        ls
        rm -rf dynamol-install dynamol-instal.gz
	./buildDist

	gzip dynamol-install
 
fi

