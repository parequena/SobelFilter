#!/bin/bash

##############################################
###############     DEBUG     ################
##############################################
out_path="build_deb"
build_type="Debug"

echo "Creating out folders: $out_path"
mkdir -p $out_path/
cd $out_path
cmake .. -DCMAKE_BUILD_TYPE=$build_type
cmake --build . -j
./SobelFilter
cd ..

##############################################
###############    RELEASE    ################
##############################################

out_path="build_rel"
build_type="Release"

echo "Creating out folders: $out_path"
mkdir -p $out_path
cd $out_path
cmake .. -DCMAKE_BUILD_TYPE=$build_type
cmake --build . -j
./SobelFilter