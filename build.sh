#!/bin/sh

mkdir build; 

cd build;
conan install .. --remote=conancenter --build=missing
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1;
cp compile_commands.json ..;
make 
