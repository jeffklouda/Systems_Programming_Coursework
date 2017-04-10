CC= gcc
CFLAGS= -g -gdwarf-2 -std=gnu99 -Wall
LD= gcc
LDFLAGS= -L.
TARGETS= walk.o linkwalk
SHELL= bash

all:	$(TARGETS)

walk.o:	walk.c 
	@echo Compiling walk.o...
	@$(CC) $(CFLAGS) -c -o walk.o walk.c

linkwalk:	walk.o
	@echo Linking walk...
	$(LD) $(LDFLAGS) -o walk walk.o

clean:
	@echo Cleaning...
	@rm ./walk.o walk
