#!/usr/bin/env bash

make -j4
cd ../python_extensions
./make_all.sh
cd dynamol

