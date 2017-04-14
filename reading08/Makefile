CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.	
TARGETS=	duplicates

all:		$(TARGETS)

%.o:%.c		
	$(CC) $(CFLAGS) -c -o $@ $<

duplicates:	duplicates.o
	$(LD) $(LDFLAGS) -o $@ $^

test:		duplicates
	@echo Testing duplicates...
	@[ `valgrind --leak-check=full ./duplicates 2>&1 | tee test.log | grep ERROR | awk '{print $$4}'` = 0 ]

clean:
	rm -f $(TARGETS) *.o
