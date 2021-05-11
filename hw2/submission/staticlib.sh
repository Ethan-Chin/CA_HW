#!/bin/sh

gcc -c doubll2d.c

ar -cr liblist.a doubll2d.o

gcc -o staticlist test.c -L. liblist.a
