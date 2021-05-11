#!/bin/sh


gcc -shared -fPIC -o liblist.so doubll2d.c

gcc -o dynamiclist test.c -L. ./liblist.so