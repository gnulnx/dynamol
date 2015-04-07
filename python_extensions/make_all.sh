#!/usr/bin/env bash

rm -f ../Scripts/lib* ../Scripts/*so
rm -f MolView/*so MolView/lib*
rm -f Molecule/*so Molecule/lib*

cd MolView
qmake
make clean
make

cd ../Molecule
qmake 
make clean
make

cd ../

