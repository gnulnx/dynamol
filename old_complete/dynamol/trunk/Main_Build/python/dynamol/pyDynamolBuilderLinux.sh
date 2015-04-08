#!/bin/sh

touch *
bjam --v2 release -j5
cp bin/gcc/release/threading-multi/libdynamol.so ./dynamol.so
cp dynamol.so ../../../dynamol/PyModules
