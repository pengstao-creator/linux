#!/bin/bash

rm -rf ./lib/*
rm -rf ./*.o

gcc -c ./src/sub.c -o ./sub.o -I./include

ar rcs ./lib/libsubstatic.a ./sub.o
rm -rf ./*.o