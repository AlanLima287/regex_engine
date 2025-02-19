#!/bin/bash

if [ ! -d ".build" ]; then
   mkdir .build
fi

cd .build

libraries=("arena" "stack" "bittools")

for library in "${libraries[@]}"; do
   gcc "../lib/$library.c" -c -o "$library.o"
   if [ $? != 0 ]; then
      echo "Error compiling $library"
   fi
done