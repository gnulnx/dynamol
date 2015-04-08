#!/bin/sh

touch *
bjam --v2 release -j4
cp bin/gcc/release/threading-multi/libdynacomp.so ./dynacomp.so
cp dynacomp.so ../../../dynamol/PyModules                               
