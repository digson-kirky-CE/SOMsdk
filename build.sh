CC=clang
CFLAGS=-Wall -O2
LIBS=-lncurses
cd $(ls | grep "OOR")
$CC $CFLAGS source.c -o incw $LIBS
