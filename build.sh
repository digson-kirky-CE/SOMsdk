CC=clang
CFLAGS=-Wall -O2
LIBS=-lncurses
cd $(ls | grep "OORw")
$CC $CFLAGS source.c -o incw $LIBS
cd ..
cd  $(ls | grep "OORr")
$CC $CFLAGS incr.c tui.c -o incr $LIBS
