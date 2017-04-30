CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs
TARGETS=	ncat

all:		$(TARGETS)

ncat:	ncat.o
	@echo Linking ncat...
	@$(LD) $(LDFLAGS) ncat.o -o ncat

ncat.o:	ncat.c
	@echo Compiling ncat.o...
	@$(CC) $(CFLAGS) ncat.c -c -o ncat.o

clean:
	@echo Cleaning...
	@rm -f *.o $(TARGETS)
