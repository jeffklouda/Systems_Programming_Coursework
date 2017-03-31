CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs
TARGETS=	liblist.a lsort measure

all:		$(TARGETS)

# TODO: Add rules for liblist.a, test_node, test_list, lsort, and any intermediate objects

test:		test-node test-list test-lsort

node.o:		node.c
	@echo "Compiling $@"
	@$(CC) node.c $(CFLAGS) -c -o node.o

list.o:		list.c
	@echo "Compiling $@"
	@$(CC) list.c $(CFLAGS) -c -o list.o

test_node.o:	test_node.c
	@echo "Compiling $@"
	@$(CC) test_node.c $(CFLAGS) -c -o test_node.o

test_list.o:	test_list.c
	@echo "Compiling $@"
	@$(CC) test_list.c $(CFLAGS) -c -o test_list.o

lsort.o:	lsort.c
	@echo "Compiling $@"
	@$(CC) lsort.c $(CFLAGS) -c -o lsort.o

liblist.a:	node.o list.o
	@echo "Linking $@"
	@$(AR) $(ARFLAGS) liblist.a node.o list.o

test_node:	test_node.o liblist.a
	@echo "Linking $@"
	@$(LD) $(LDFLAGS) -o test_node test_node.o liblist.a

test_list:	test_list.o liblist.a
	@echo "Linking $@"
	@$(LD) $(LDFLAGS) -o test_list test_list.o liblist.a

lsort:		lsort.o liblist.a
	@echo "Linking $@"
	@$(LD) $(LDFLAGS) -o lsort lsort.o liblist.a

test-node:	test_node
	@echo Testing node...
	@[ `valgrind --leak-check=full ./test_node 2>&1 | tee test_node.log | grep ERROR | awk '{print $$4}'` = 0 ] || cat test_node.log

test-list:	test_list
	@echo Testing list...
	@[ `valgrind --leak-check=full ./test_list 2>&1 | tee test_list.log | grep ERROR | awk '{print $$4}'` = 0 ] || cat test_list.log

test-lsort:	lsort test_lsort.sh
	@echo Testing lsort...
	@./test_lsort.sh

measure:	measure.c
	@echo Making measure
	@$(CC) measure.c $(CFLAGS) -o measure

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) test_node test_list *.a *.o *.log *.input

.PHONY:		all test test-node test-list test-lsort clean
