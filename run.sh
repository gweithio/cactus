#!/bin/sh

RED='\033[0;32m'
NC='\033[0m' # No Color


if [[ $1 == "debug" ]]; then
    ./build.sh
    lldb ./build/bin/cactus
    exit
fi


./build.sh 
echo "\n${RED}Running cactus....${NC}\n"
./build/bin/cactus
