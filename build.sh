#!/bin/sh
mkdir -p build
cd build
cmake ..
make
cd ..
rm -rf build
cd bin
echo Liste des fichiers générés :
ls --color
