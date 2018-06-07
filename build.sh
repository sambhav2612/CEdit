#!/bin/bash

sudo 

dpkg -s $1 $2 &> /dev/null

if [ $? -eq 0 ]; then
    echo "Package  is installed!"
else
    echo "Package  is NOT installed!"
fi

gcc editor.c -o editor
make