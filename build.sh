CC=clang
CFLAGS=-Wall -O2
LIBS=-lncurses
cd OOR*
$CC $CFLAGS source.c -o incw $LIBS
