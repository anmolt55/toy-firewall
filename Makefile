# divert-loop.mk

all: divert-loop block_allICMP block_inICMP

block_inICMP: block_inICMP.o divertlib.o printip.o
	gcc -o block_inICMP block_inICMP.o divertlib.o printip.o

block_inICMP.o: block_inICMP.c divertlib.h
	gcc -c block_inICMP.c

block_allICMP: block_allICMP.o divertlib.o printip.o
	gcc -o block_allICMP block_allICMP.o divertlib.o printip.o

block_allICMP.o: block_allICMP.c divertlib.h
	gcc -c block_allICMP.c

divert-loop: divert-loop.o divertlib.o printip.o
	gcc -o divert-loop divert-loop.o divertlib.o printip.o

divert-loop.o: divert-loop.c divertlib.h
	gcc -c divert-loop.c

divertlib.o: divertlib.h divertlib.c
	gcc -c divertlib.c

printip.o: printip.h printip.c
	gcc -c printip.c
